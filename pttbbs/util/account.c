/* $Id$ */
#include "bbs.h"

// test
#define ACCOUNT_MAX_LINE        16
#define ADJUST_M        6	/* adjust back 5 minutes */

void
reset_garbage(void)
{
    if (SHM == NULL) {
	attach_SHM();
	if (SHM->Ptouchtime == 0)
	    SHM->Ptouchtime = 1;
    }
    /*
     * 不整個reload? for(n=0;n<=SHM->last_film;n++) printf("\n**%d**\n %s
     * \n",n,SHM->notes[n]);
     */
    SHM->Puptime = 0;
    reload_pttcache();

    printf("\n動態看板數[%d]\n", SHM->last_film);
    /*
     * for(n=0; n<MAX_MOVIE_SECTION; n++) printf("sec%d=> 起點:%d
     * 下次要換的:%d\n ",n,SHM->n_notes[n], SHM->next_refresh[n]);
     * printf("\n");
     */
}

static void
keeplog(const char *fpath, const char *board, const char *title, const char *sym)
{
    fileheader_t    fhdr;
    int             bid;
    char            genbuf[PATHLEN], buf[256];

    if (!board)
	board = BN_RECORD;

    setbpath(genbuf, board);
    stampfile(genbuf, &fhdr);
    Rename(fpath, genbuf);

    if (sym) {
        sprintf(buf, "log/%s", sym);
        unlink(buf);
        symlink(genbuf, buf);
    }
    /*
     * printf("keep record:[%s][%s][%s][%s]\n",fpath, board, title,genbuf);
     */
    strlcpy(fhdr.title, title, sizeof(fhdr.title));
    strlcpy(fhdr.owner, "[歷史老師]", sizeof(fhdr.owner));
    setbfile(genbuf, board, FN_DIR);
    append_record(genbuf, &fhdr, sizeof(fhdr));
    /* XXX: bid of cache.c's getbnum starts from 1 */
    if ((bid = getbnum(board)) > 0)
	touchbtotal(bid);
}


static void
my_outs(FILE *fp, char *buf, char mode)
{
    static char     state = '0';

    if (state != mode)
	fprintf(fp, "[3%cm", state = mode);
    if (buf[0]) {
	fputs(buf, fp);
	buf[0] = 0;
    }
}

// moves "source" to "target""suffix", then gzips it
static void 
gzip(const char *source, const char *target, const char *suffix)
{
    char buf[PATHLEN];
    snprintf(buf, sizeof(buf), "gzip -f9n adm/%s%s", target, suffix);
    Rename(source, &buf[14]);
    system(buf);
}

static int
parse_usies(const char *fn, struct tm *ptime, int act[27])
{
    const char const act_file[] = ".act";
    char buf[256], *p;
    FILE *fp;

    // load parsed result
    if ((ptime->tm_hour != 0) && (fp = fopen(act_file, "r"))) {
	fread(act, sizeof(act), 1, fp);
	fclose(fp);
    }

    // parse "usies"
    if ((fp = fopen(fn, "r")) == NULL) {
	printf("cann't open usies\n");
	return 1;
    }

    if (act[26])
	fseek(fp, act[26], 0);

    while (fgets(buf, sizeof(buf), fp)) {
	int hour;
	buf[11 + 2] = 0;
	hour = atoi(buf + 11);
	if (hour < 0 || hour > 23) {
	    continue;
	}
	//"09/06/1999 17:44:58 Mon "
	// 012345678901234567890123
	if (strstr(buf + 20, "ENTER")) {
	    act[hour]++;
	    continue;
	}
	if ((p = strstr(buf + 40, "Stay:"))) {
	    if ((hour = atoi(p + 5))) {
		act[24] += hour;
		act[25]++;
	    }
	    continue;
	}
    }
    act[26] = ftell(fp);
    fclose(fp);

    // write parsed result
    if ((fp = fopen(act_file, "w"))) {
	fwrite(act, sizeof(act), 1, fp);
	fclose(fp);
    }

    return 0;
}

static int
output_today(struct tm *ptime, int act[27], int peak_hour_login, int day_login)
{
    char buf[256];
    int item = peak_hour_login / ACCOUNT_MAX_LINE + 1;
    int per_hour_unit = 100;
    int i, j;
    FILE *fp;

    if ((fp = fopen("etc/today", "w")) == NULL) {
	printf("can't open etc/today\n");
	return 1;
    }

    fprintf(fp, "\t\t\t" ANSI_COLOR(1;33;46) "每小時上站人次統計 [%02d/%02d/%02d] " ANSI_COLOR(40) "\n\n", 
	    ptime->tm_year % 100, ptime->tm_mon + 1, ptime->tm_mday);

    for (i = ACCOUNT_MAX_LINE + 1; i > 0; i--) {
	strcpy(buf, "   ");

	for (j = 0; j < 24; j++) {
	    int hour_count = act[j];
	    int max = item * i;
	    if (hour_count && (hour_count < max) && (max <= hour_count + item)) {
		my_outs(fp, buf, '3');
		fprintf(fp, "%-3d", hour_count / per_hour_unit);
	    } else if (max <= hour_count) {
		my_outs(fp, buf, '4');
		fprintf(fp, "█ ");
	    } else
		strcat(buf, "   ");
	}

	fprintf(fp, "\n");
    }

    fprintf(fp, "   " ANSI_COLOR(32)
	    "0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23\n\n"
	    "\t      " ANSI_COLOR(34) "單位: " ANSI_COLOR(37) "%d" ANSI_COLOR(34) " 人", per_hour_unit);
    fprintf(fp, "  總共上站人次：" ANSI_COLOR(37) "%-7d" ANSI_COLOR(34) "平均使用人數：" ANSI_COLOR(37) "%d\n",
	    day_login, day_login / 24);
    fclose(fp);

    return 0;
}

static int
update_history(struct tm *ptime, int peak_hour, int peak_hour_login, int day_login)
{
    int max_hour_login = 0, max_day_login = 0, max_reg = 0, max_online = 0;
    int peak_online;
    FILE *fp, *fp1;
    time_t t;
    struct tm tm;

    if ((fp = fopen("etc/history.data", "r+")) == NULL)
	return 1;

    /* 最多同時上線 */
    if (fscanf(fp, "%d %d %d %d", &max_day_login, &max_hour_login, &max_reg, &max_online) != 4)
	goto out;

    if ((fp1 = fopen("etc/history", "a")) == NULL)
	goto out;

    resolve_fcache();
    peak_online = SHM->max_user;
    printf("此時段最多同時上線:%d 過去:%d\n", peak_online, max_online);

    if (peak_online > max_online) {
	localtime4_r(&SHM->max_time, &tm);
	fprintf(fp1, "◎ 【%02d/%02d/%02d %02d:%02d】"
		ANSI_COLOR(32) "同時在坊內人數" ANSI_RESET "首次達到 " ANSI_COLOR(1;36) "%d" ANSI_RESET " 人次\n",
		tm.tm_mon + 1, tm.tm_mday, tm.tm_year % 100, tm.tm_hour, tm.tm_min, peak_online);
	max_online = peak_online;
    }

    t = mktime(ptime) + ADJUST_M * 60;
    localtime_r(&t, &tm);

    if (tm.tm_hour == 0) {
	if (peak_hour_login > max_hour_login) {
	    fprintf(fp1, "◇ 【%02d/%02d/%02d %02d】   "
		    ANSI_COLOR(1;32) "單一小時上線人次" ANSI_RESET "首次達到 " ANSI_COLOR(1;35) "%d" ANSI_RESET " 人次\n",
		    ptime->tm_mon + 1, ptime->tm_mday, ptime->tm_year % 100, peak_hour, peak_hour_login);
	    max_hour_login = peak_hour_login;
	}
	if (day_login > max_day_login) {
	    fprintf(fp1, "◆ 【%02d/%02d/%02d】      "
		    ANSI_COLOR(1;32) "單日上線人次" ANSI_RESET "首次達到 " ANSI_COLOR(1;33) "%d" ANSI_RESET " 人次\n",
		    ptime->tm_mon + 1, ptime->tm_mday, ptime->tm_year % 100, day_login);
	    max_day_login = day_login;
	}
	if (SHM->number > max_reg + max_reg / 10) {
	    fprintf(fp1, "★ 【%02d/%02d/%02d】      "
		    ANSI_COLOR(1;32) "總註冊人數" ANSI_RESET "提升到 " ANSI_COLOR(1;31) "%d" ANSI_RESET " 人\n",
		    ptime->tm_mon + 1, ptime->tm_mday, ptime->tm_year % 100, SHM->number);
	    max_reg = SHM->number;
	}
    }

    fclose(fp1);

out:
    rewind(fp);
    fprintf(fp, "%d %d %d %d", max_day_login, max_hour_login, max_reg, peak_online);
    fclose(fp);

    return 0;
}

int 
main(int argc, char **argv)
{
    int             i, j;
    int             mo, da;
    int             peak_hour_login, peak_hour, day_login;
    const char const log_file[] = "usies";
    const char const wday_str[] = "UMTWRFS";
    char            buf[256], buf1[256];
    FILE           *fp, *fp1;
    int             act[27];	/* 次數/累計時間/pointer */
    time4_t         now;
    struct tm      *ptime;

    attach_SHM();
    nice(10);
    chdir(BBSHOME);
    now = time(NULL) - ADJUST_M * 60;	/* back to ancent */
    ptime = localtime4(&now);

    memset(act, 0, sizeof(act));

    printf("次數/累計時間\n");
    parse_usies(log_file, ptime, act);

    peak_hour_login = peak_hour = 0;
    day_login = 0;
    for (i = 0; i < 24; i++) {
	day_login += act[i];
	if (act[i] > peak_hour_login) {
	    peak_hour_login = act[i];
	    peak_hour = i;
	}
    }

    if (!ptime->tm_hour) {
	keeplog("etc/today", BN_RECORD, "上站人次統計", NULL);
	keeplog(FN_MONEY, BN_SECURITY, "本日金錢往來記錄", NULL);
	keeplog("etc/illegal_money", BN_SECURITY, "本日違法賺錢記錄", NULL);
	keeplog("etc/osong.log", BN_SECURITY, "本日點歌記錄", NULL);
	keeplog("etc/chicken", BN_RECORD, "雞場報告", NULL);
    }

    /* -------------------------------------------------------------- */
    printf("上站人次統計\n");
    output_today(ptime, act, peak_hour_login, day_login);
    /* -------------------------------------------------------------- */

    printf("歷史事件處理\n");
    /* Ptt 歷史事件處理 */
    update_history(ptime, peak_hour, peak_hour_login, day_login);

    now += ADJUST_M * 60;	/* back to future */
    ptime = localtime4(&now);

    if (ptime->tm_hour) {
	/* rotate one line in today_is */
	/* XXX totally meaningless, it is only relative sequence since rotate, not mapping to real time */
	puts("多個節日處理");
	if ((fp1 = fopen("etc/today_is", "r"))) {
	    char            tod[100][20];

	    i = 0;
	    while (i < 100 && fgets(tod[i], sizeof(tod[0]), fp1))
		i++;
	    fclose(fp1);

	    fp1 = fopen("etc/today_is", "w");
	    for (j = 0; j < i; j++)
		fputs(tod[j + 1 < i ? j + 1 : 0], fp1);
	    fclose(fp1);
	}
    }

    if (ptime->tm_hour == 0) {
	system("/bin/cp etc/today etc/yesterday");
	/* system("rm -f note.dat"); */

	/* Ptt */
	snprintf(buf, sizeof(buf), "[公安報告] 使用者上線監控 [%02d/%02d:%02d]",
		ptime->tm_mon + 1, ptime->tm_mday, ptime->tm_hour);
	keeplog("usies", "Security", buf, "usies");
	printf("[公安報告] 使用者上線監控\n");

	/* Ptt 歷史事件處理 */
	now -= ADJUST_M * 60;	/* back to ancent */
	ptime = localtime4(&now);

	sprintf(buf, "-%02d%02d%02d",
		ptime->tm_year % 100, ptime->tm_mon + 1, ptime->tm_mday);
	gzip(log_file, "usies", buf);
	printf("壓縮使用者上線監控\n");

	now += ADJUST_M * 60;	/* back to future */
	ptime = localtime4(&now);

	/* Ptt 節日處理 */
	printf("節日處理\n");
	if ((fp1 = fopen("etc/today_is", "w"))) {
	    i = 0;
	    if ((fp = fopen("etc/feast", "r"))) {
		while (fgets(buf1, sizeof(buf1), fp)) {
		    if (buf1[0] != '#' &&
			sscanf(buf1, "%d %c%c", &mo, buf, buf + 1) == 3) {
			if (isdigit(buf[0])) {
			    if (isdigit(buf[1])) {
				da = 10 * (buf[0] - '0') + (buf[1] - '0');
				if (ptime->tm_mday == da && ptime->tm_mon + 1 == mo) {
				    i = 1;
				    fprintf(fp1, "%-14.14s", &buf1[6]);
				}
			    } else {
				if (buf[0] - '0' <= 4) {
				    int wday = 0;
				    buf[1] = toupper(buf[1]);
				    while (wday < 7 && buf[1] != *(wday_str + wday))
					wday++;
				    if (ptime->tm_mon + 1 == mo && ptime->tm_wday == wday &&
					(ptime->tm_mday - 1) / 7 + 1 == (buf[0] - '0')) {
					i = 1;
					fprintf(fp1, "%-14.14s", &buf1[6]);
				    }
				}
			    }
			}
		    }
		}
		fclose(fp);
	    }
	    printf("節日處理1\n");
	    if (i == 0) {
		if ((fp = fopen("etc/today_boring", "r"))) {
		    while (fgets(buf1, sizeof(buf1), fp))
			if (strlen(buf1) > 3)
			    fprintf(fp1, "%s", buf1);
		    fclose(fp);
		} else
		    fprintf(fp1, "本日節日徵求中");
	    }
	    fclose(fp1);
	}

	/* Ptt 歡迎畫面處理 */
	printf("歡迎畫面處理\n");

	if ((fp = fopen("etc/Welcome.date", "r"))) {
	    char            temp[50];
	    while (fscanf(fp, "%d %d %s\n", &mo, &da, buf1) == 3) {
		if (ptime->tm_mday == da && ptime->tm_mon + 1 == mo) {
		    strcpy(temp, buf1);
		    sprintf(buf1, "cp -f etc/Welcomes/%s etc/Welcome", temp);
		    system(buf1);
		    break;
		}
	    }
	    fclose(fp);
	}
	printf("歡迎畫面處理\n");
	if (ptime->tm_wday == 0) {
	    keeplog("etc/week", BN_RECORD, "本週熱門話題", NULL);

	    gzip("bbslog", "bntplink", buf);
	    gzip("innd/bbslog", "innbbsd", buf);
	    gzip("etc/mailog", "mailog", buf);
	}
	if (ptime->tm_mday == 1)
	    keeplog("etc/month", BN_RECORD, "本月熱門話題", NULL);

	if (ptime->tm_yday == 1)
	    keeplog("etc/year", BN_RECORD, "年度熱門話題", NULL);
    } else if (ptime->tm_hour == 3 && ptime->tm_wday == 6) {
	char           *fn1 = "tmp";
	char           *fn2 = "suicide";
	rename(fn1, fn2);
	mkdir(fn1, 0755);
	sprintf(buf, "tar cfz adm/%s-%02d%02d%02d.tgz %s",
	 fn2, ptime->tm_year % 100, ptime->tm_mon + 1, ptime->tm_mday, fn2);
	system(buf);
	sprintf(buf, "/bin/rm -fr %s", fn2);
	system(buf);
    }
    /* Ptt reset Ptt's share memory */
    printf("重設cache 與fcache\n");

    SHM->Puptime = 0;
    resolve_fcache();
    reset_garbage();
    printf("動態看板資訊: last_usong=%d, last_film=%d\n", 
	    SHM->last_usong, SHM->last_film);

    printf("計算進站畫面數: ");
    for (i = 0; i < 5; ++i) {
	sprintf(buf, "etc/Welcome_login.%d", i);
	if (access(buf, 0) < 0)
	    break;
    }
    printf("%d\n", SHM->GV2.e.nWelcomes = i);
    return 0;
}
