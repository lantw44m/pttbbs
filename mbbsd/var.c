/* $Id$ */
#define INCLUDE_VAR_H
#include "bbs.h"

int           str_permid[] = {
    2572,			/* PERM_BASIC */
    2573,		/* PERM_CHAT */
    2574,			/* PERM_PAGE */
    2575,			/* PERM_POST */
    2576,		/* PERM_LOGINOK */
    2577,		/* PERM_MAILLIMIT */
    2578,			/* PERM_CLOAK */
    2579,			/* PERM_SEECLOAK */
    2580,		/* PERM_XEMPT */
    2581,		/* PERM_DENYPOST */
    2582,			/* PERM_BM */
    2583,			/* PERM_ACCOUNTS */
    2584,		/* PERM_CHATCLOAK */
    2585,			/* PERM_BOARD */
    2586,			/* PERM_SYSOP */
    3440,			/* PERM_POSTMARK */
    2587,		/* PERM_NOTOP */
    2588,		/* PERM_VIOLATELAW */
    2589,		/* PERM_ */
    2590,	/* PERM_NOREGCODE */
    2591,			/* PERM_VIEWSYSOP */
    2592,		/* PERM_LOGUSER */
    2593,		/* PERM_Announce */
    2594,			/* PERM_RELATION */
    2595,			/* PERM_SMG */
    2596,			/* PERM_PRG */
    2597,			/* PERM_ACTION */
    2598,			/* PERM_PAINT */
    2599,			/* PERM_LAW */
    2600,			/* PERM_SYSSUBOP */
    2601,			/* PERM_LSYSOP */
    2602			/* PERM_PTT */
};

int           str_permboard[] = {
    2603,			/* BRD_NOZAP */
    2604,		/* BRD_NOCOUNT */
    2605,			/* BRD_NOTRAN */
    2606,			/* BRD_GROUPBOARD */
    2607,			/* BRD_HIDE */
    2608,		/* BRD_POSTMASK */
    2609,			/* BRD_ANONYMOUS */
    2610,		/* BRD_DEFAULTANONYMOUS */
    2611,		/* BRD_BAD */
    2612,		/* BRD_VOTEBOARD */
    2613,		/* BRD_WARNEL */
    2614,		/* BRD_TOP */
    2615,                 /* BRD_NORECOMMEND */
    2616,			/* BRD_BLOG */
    2617,		/* BRD_BMCOUNT */
    2618,
    2619,
    2620,
    2621,
    2622,
    2623,
    2624,
    2625,
    2626,
    2627,
    2628,
    2629,
    2630,
    2631,
    2632,
    2633,
    2634,
};

int             usernum;
int             currmode = 0;
int             curredit = 0;
int             showansi = 1;
int             paste_level;
int             currbid;
char            quote_file[80] = "\0";
char            quote_user[80] = "\0";
char            paste_title[STRLEN];
char            paste_path[256];
char            currtitle[TTLEN + 1] = "\0";
char            vetitle[TTLEN + 1] = "\0";
char            currauthor[IDLEN + 2] = "\0";
char           *currboard = "\0";
char            currBM[IDLEN * 3 + 10];
char            reset_color[4] = "\033[m";
char            margs[64] = "\0";	/* main argv list */
pid_t           currpid;	/* current process ID */
time_t          login_start_time;
time_t          start_time;
time_t          paste_time;
userec_t        cuser;		/* current user structure */
userec_t        xuser;		/* lookup user structure */
crosspost_t     postrecord;	/* anti cross post */
unsigned int    currbrdattr;
unsigned int    currstat;
unsigned char   currfmode;	/* current file mode */

/* global string variables */
/* filename */

char           *fn_passwd = FN_PASSWD;
char           *fn_board = FN_BOARD;
char           *fn_note_ans = FN_NOTE_ANS;
char           *fn_register = "register.new";
char           *fn_plans = "plans";
char           *fn_writelog = "writelog";
char           *fn_talklog = "talklog";
char           *fn_overrides = FN_OVERRIDES;
char           *fn_reject = FN_REJECT;
char           *fn_canvote = FN_CANVOTE;
char           *fn_notes = "notes";
char           *fn_water = FN_WATER;
char           *fn_visable = FN_VISABLE;
char           *fn_mandex = "/.Names";
char           *fn_proverb = "proverb";

/* are descript in userec.loginview */

loginview_file_t	loginview_file[] = {
    {FN_NOTE_ANS, 2635},
    {FN_TOPSONG, 2636},
    {"etc/topusr", 2637},
    {"etc/topusr100", 2638},
    {"etc/birth.today", 2639},
    {"etc/weather.tmp", 2640},
    {"etc/stock.tmp", 2641},
    {"etc/day", 2642},
    {"etc/week", 2643},
    {"etc/today", 2644},
    {"etc/yesterday", 2645},
    {"etc/history", 2646},
    {"etc/topboardman", 2647},
    {"etc/topboard.tmp", 2648}
};

/* message */
char           *msg_seperator = MSG_SEPERATOR;
char           *msg_mailer = MSG_MAILER;
char           *msg_shortulist = MSG_SHORTULIST;

char           *msg_cancel = MSG_CANCEL;
char           *msg_usr_left = MSG_USR_LEFT;
char           *msg_nobody = MSG_NOBODY;

char           *msg_sure_ny = MSG_SURE_NY;
char           *msg_sure_yn = MSG_SURE_YN;

char           *msg_bid = MSG_BID;
char           *msg_uid = MSG_UID;

char           *msg_del_ok = MSG_DEL_OK;
char           *msg_del_ny = MSG_DEL_NY;

char           *msg_fwd_ok = MSG_FWD_OK;
char           *msg_fwd_err1 = MSG_FWD_ERR1;
char           *msg_fwd_err2 = MSG_FWD_ERR2;

char           *err_board_update = ERR_BOARD_UPDATE;
char           *err_bid = ERR_BID;
char           *err_uid = ERR_UID;
char           *err_filename = ERR_FILENAME;

char           *str_mail_address = "." BBSUSER "@" MYHOSTNAME;
char           *str_new = "new";
char           *str_reply = "Re: ";
char           *str_space = " \t\n\r";
char           *str_sysop = "SYSOP";
char           *str_author1 = STR_AUTHOR1;
char           *str_author2 = STR_AUTHOR2;
char           *str_post1 = STR_POST1;
char           *str_post2 = STR_POST2;
char           *BBSName = BBSNAME;

/* #define MAX_MODES 78 */
/* MAX_MODES is defined in common.h */

int           ModeTypeTable[MAX_MODES] = {
    2649,			/* IDLE */
    2650,			/* MMENU */
    2651,			/* ADMIN */
    2652,			/* MAIL */
    2653,			/* TMENU */
    2654,		/* UMENU */
    2655,			/* XMENU */
    2656,			/* CLASS */
    2657,			/* PMENU */
    2658,		/* NMENU */
    2659,		/* PSALE */
    2660,			/* POSTING */
    2661,			/* READBRD */
    2662,		/* READING */
    2663,		/* READNEW */
    2664,			/* SELECT */
    2665,			/* RMAIL */
    2666,			/* SMAIL */
    2667,			/* CHATING */
    2668,			/* XMODE */
    2669,			/* FRIEND */
    2670,		/* LAUSERS */
    2671,		/* LUSERS */
    2672,			/* MONITOR */
    2673,			/* PAGE */
    2674,			/* TQUERY */
    2675,			/* TALK  */
    2676,			/* EDITPLAN */
    2677,			/* EDITSIG */
    2678,			/* VOTING */
    2679,			/* XINFO */
    2680,			/* MSYSOP */
    2681,			/* WWW */
    2682,			/* BIG2 */
    2683,			/* REPLY */
    2684,		/* HIT */
    2685,		/* DBACK */
    2686,			/* NOTE */
    2687,			/* EDITING */
    2688,		/* MAILALL */
    2689,			/* MJ */
    2690,			/* P_FRIEND */
    2691,			/* LOGIN */
    2692,			/* DICT */
    2693,			/* BRIDGE */
    2694,			/* ARCHIE */
    2695,			/* GOPHER */
    2696,			/* NEWS */
    2697,		/* LOVE */
    2698,		/* EDITEXP */
    2699,		/* IPREG */
    2700,		/* NetAdm */
    2701,		/* DRINK */
    2702,			/* CAL */
    2703,		/* PROVERB */
    2704,			/* ANNOUNCE */
    2705,			/* EDNOTE */
    2706,		/* CDICT */
    2707,		/* LOBJ */
    2708,			/* OSONG */
    2709,		/* CHICKEN */
    2710,			/* TICKET */
    2711,			/* GUESSNUM */
    2712,			/* AMUSE */
    2713,			/* OTHELLO */
    2714,			/* DICE */
    2715,			/* VICE */
    2716,		/* BBCALL */
    2717,			/* CROSSPOST */
    2718,			/* M_FIVE */
    2719,			/* JACK_CARD */
    2720,		/* TENHALF */
    2721,		/* CARD_99 */
    2722,			/* RAIL_WAY */
    2723,			/* SREG */
    2724,			/* CHC */
    2725,			/* DARK */
    2726,			/* TMPJACK */
    2727,		/* JCEE */
    2728,			/* REEDIT */
    2729,                   /* BLOGGING */
    0, /* for future usage */
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

/* term.c */
int             b_lines = 23; // bottom line of screen
int             t_lines = 24; // term lines
int             p_lines = 20;
int             t_columns = 80;
char           *strtstandout = "\33[7m";
int             strtstandoutlen = 4;
char           *endstandout = "\33[m";
int             endstandoutlen = 3;
char           *clearbuf = "\33[H\33[J";
int             clearbuflen = 6;
char           *cleolbuf = "\33[K";
int             cleolbuflen = 3;
char           *scrollrev = "\33M";
int             scrollrevlen = 2;
int             automargins = 1;

/* io.c */
time_t          now;
int             KEY_ESC_arg;
int             watermode = -1;
int             wmofo = -1;
/*
 * WATERMODE(WATER_ORIG) | WATERMODE(WATER_NEW):
 * ????????????????????
 * Ptt 水球回顧 e = -1
 * 沒在回水球 = 0   在回上一顆水球  (Ctrl-R) > 0   在回前 n 顆水球 (Ctrl-R
 * Ctrl-R)
 * 
 * WATERMODE(WATER_OFO)  by in2
 * wmofo     = NOTREPLYING     沒在回水球
 *           = REPLYING        正在回水球
 *           = RECVINREPLYING  回水球間又接到水球
 *
 * wmofo     >=0  時收到水球將只顯示, 不會到water[]裡,
 *                待回完水球的時候一次寫入.
 */


/* cache.c */
int             numboards = -1;
int            *GLOBALVAR;
SHM_t          *SHM;
boardheader_t  *bcache;
userinfo_t     *currutmp;

/* board.c */
int             class_bid = 0;

/* brc.c */
int             brc_num;
time_t          brc_list[BRC_MAXNUM];

/* read.c */
int             TagNum;			/* tag's number */
TagItem         TagList[MAXTAGS];	/* ascending list */
int		TagBoard = -1;		/* TagBoard = 0 : user's mailbox
					   TagBoard > 0 : bid where last taged*/
char            currdirect[64];

/* edit.c */
char            save_title[STRLEN];

/* bbs.c */
time_t          board_visit_time;
char            real_name[IDLEN + 1];
int             local_article;

/* mbbsd.c */
char            fromhost[STRLEN] = "\0";
char            water_usies = 0;
FILE           *fp_writelog = NULL;
water_t         water[6], *swater[6], *water_which = &water[0];

/* announce.c */
char            trans_buffer[256];

/* chc_play.c */
rc_t            chc_from, chc_to, chc_select, chc_cursor;
int             chc_lefttime;
int             chc_my, chc_turn, chc_selected, chc_firststep;
char            chc_warnmsg[64], *chc_mateid;

/* screen.c */
screenline_t   *big_picture = NULL;
unsigned char   scr_lns;
unsigned short  scr_cols;
char            roll;

/* gomo.c */
char            ku[BRDSIZ][BRDSIZ];
unsigned char  *pat, *adv;
unsigned char  *pat_gomoku /* [1954] */ =
 /* 0 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 16 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x44\x55\xcc\x00\x00\x00\x00"
 /* 32 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x33\x00\x44\x00\x33\x00\x00\x00"
 /* 48 */ "\x00\x22\x00\x55\x00\x22\x00\x00\x00\x44\x33\x66\x55\xcc\x33\x66"
 /* 64 */ "\x55\xcc\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00"
 /* 80 */ "\x55\x00\x55\x00\x05\x00\x55\x02\x46\x00\xaa\x00\x00\x55\x00\x55"
 /* 96 */ "\x00\x05\x00\x55\x00\x05\x00\x55\x00\x00\x44\xcc\x44\xcc\x05\xbb"
 /* 112 */ "\x44\xcc\x05\xbb\x44\xcc\x05\xbb\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 128 */ "\x00\x00\x33\x00\x00\x00\x44\x00\x00\x00\x00\x00\x33\x00\x44\x00"
 /* 144 */ "\x33\x22\x66\x00\x55\x55\xcc\x00\x33\x00\x00\x00\x00\x22\x00\x55"
 /* 160 */ "\x00\x22\x00\x55\x00\x02\x00\x05\x00\x22\x00\x00\x33\x44\x33\x66"
 /* 176 */ "\x55\xcc\x33\x66\x55\xcc\x33\x46\x05\xbb\x33\x66\x55\xcc\x00\x00"
 /* 192 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x44\x00\x00\x00"
 /* 208 */ "\x33\x00\x00\x22\x55\x22\x55\x02\x05\x22\x55\x02\x46\x22\xaa\x55"
 /* 224 */ "\xcc\x22\x55\x02\x46\x22\xaa\x00\x22\x55\x22\x55\x02\x05\x22\x55"
 /* 240 */ "\x02\x05\x22\x55\x02\x05\x22\x55\x02\x05\x22\x55\x02\x44\x66\xcc"
 /* 256 */ "\x66\xcc\x46\xbb\x66\xcc\x46\xbb\x66\xcc\x46\xbb\x66\xcc\x46\xbb"
 /* 272 */ "\x66\xcc\x46\xbb\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x33\x00"
 /* 288 */ "\x00\x00\x44\x00\x00\x00\x33\x00\x22\x22\x66\x00\x00\x00\x00\x00"
 /* 304 */ "\x03\x00\x44\x00\x33\x22\x66\x00\x55\x55\xcc\x00\x33\x22\x66\x00"
 /* 320 */ "\x55\x55\xcc\x00\x03\x00\x00\x00\x00\x02\x00\x55\x00\x02\x00\x55"
 /* 336 */ "\x00\x02\x00\x05\x00\x02\x00\x55\x00\x02\x02\x46\x00\x02\x00\x55"
 /* 352 */ "\x55\x05\x55\x46\xaa\xcc\x55\x46\xaa\xcc\x55\x06\x5a\xbb\x55\x46"
 /* 368 */ "\xaa\xcc\x55\x06\x5a\xbb\x55\x46\xaa\xcc\x00\x00\x00\x00\x00\x00"
 /* 384 */ "\x00\x00\x00\x00\x03\x00\x00\x00\x44\x00\x00\x00\x33\x00\x22\x22"
 /* 400 */ "\x66\x00\x00\x00\x55\x00\x55\x55\x05\x55\x05\x55\x05\x55\x05\x55"
 /* 416 */ "\x46\x55\x5a\xaa\xcc\x55\x05\x55\x46\x55\x5a\xaa\xcc\x55\x05\x55"
 /* 432 */ "\x06\x55\x0a\x55\x55\x05\x55\x05\x55\x05\x55\x05\x55\x05\x55\x05"
 /* 448 */ "\x55\x05\x55\x05\x55\x05\x55\x05\x55\x46\x55\x05\x55\x5a\x55\x5a"
 /* 464 */ "\xaa\xcc\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb"
 /* 480 */ "\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb"
 /* 496 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x33\x00\x00\x00\x44\x00"
 /* 512 */ "\x00\x00\x33\x00\x22\x22\x66\x00\x00\x00\x55\x00\x55\x55\xcc\x00"
 /* 528 */ "\x00\x00\x00\x00\x33\x00\x44\x00\x33\x22\x66\x00\x55\x55\xcc\x00"
 /* 544 */ "\x33\x22\x66\x00\x55\x55\xcc\x00\x33\x02\x46\x00\x05\x05\xbb\x00"
 /* 560 */ "\x33\x00\x00\x00\x00\x22\x00\x55\x00\x22\x00\x55\x00\x02\x00\x05"
 /* 576 */ "\x00\x22\x00\x55\x00\x02\x02\x46\x00\x22\x00\xaa\x00\x55\x55\xcc"
 /* 592 */ "\x00\x22\x00\x00\x33\x44\x33\x66\x55\xcc\x33\x66\x55\xcc\x33\x46"
 /* 608 */ "\x05\xbb\x33\x66\x55\xcc\x33\x46\x05\xbb\x33\x66\x55\xcc\x33\x46"
 /* 624 */ "\x05\xbb\x33\x66\x55\xcc\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 640 */ "\x03\x00\x00\x00\x44\x00\x00\x00\x33\x00\x22\x22\x66\x00\x00\x00"
 /* 656 */ "\x55\x00\x55\x55\xcc\x00\x00\x00\x33\x00\x00\x22\x55\x22\x55\x02"
 /* 672 */ "\x05\x22\x55\x02\x46\x22\xaa\x55\xcc\x22\x55\x02\x46\x22\xaa\x55"
 /* 688 */ "\xcc\x22\x55\x02\x06\x22\x5a\x05\xbb\x22\x55\x02\x46\x22\xaa\x00"
 /* 704 */ "\x22\x55\x22\x55\x02\x05\x22\x55\x02\x05\x22\x55\x02\x05\x22\x55"
 /* 720 */ "\x02\x05\x22\x55\x02\x46\x22\x55\x02\x5a\x22\xaa\x55\xcc\x22\x55"
 /* 736 */ "\x02\x05\x22\x55\x02\x44\x66\xcc\x66\xcc\x46\xbb\x66\xcc\x46\xbb"
 /* 752 */ "\x66\xcc\x46\xbb\x66\xcc\x46\xbb\x66\xcc\x46\xbb\x66\xcc\x46\xbb"
 /* 768 */ "\x66\xcc\x46\xbb\x66\xcc\x46\xbb\x66\xcc\x46\xbb\x00\x00\x00\x00"
 /* 784 */ "\x00\x00\x00\x00\x00\x00\x33\x00\x00\x00\x44\x00\x00\x00\x33\x00"
 /* 800 */ "\x22\x22\x66\x00\x00\x00\x55\x00\x55\x55\xcc\x00\x00\x00\x33\x00"
 /* 816 */ "\x22\x22\x66\x00\x00\x00\x00\x00\x03\x00\x44\x00\x33\x22\x66\x00"
 /* 832 */ "\x55\x55\xcc\x00\x33\x22\x66\x00\x55\x55\xcc\x00\x03\x02\x46\x00"
 /* 848 */ "\x05\x05\xbb\x00\x33\x22\x66\x00\x55\x55\xcc\x00\x03\x00\x00\x00"
 /* 864 */ "\x00\x02\x00\x55\x00\x02\x00\x55\x00\x02\x00\x05\x00\x02\x00\x55"
 /* 880 */ "\x00\x02\x02\x46\x00\x02\x00\xaa\x00\x55\x55\xcc\x00\x02\x00\x55"
 /* 896 */ "\x00\x02\x02\x46\x00\x02\x00\x55\x55\x05\x55\x46\xaa\xcc\x55\x46"
 /* 912 */ "\xaa\xcc\x55\x06\x5a\xbb\x55\x46\xaa\xcc\x55\x06\x5a\xbb\x55\x46"
 /* 928 */ "\xaa\xcc\x55\x06\x5a\xbb\x55\x46\xaa\xcc\x55\x06\x5a\xbb\x55\x46"
 /* 944 */ "\xaa\xcc\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00"
 /* 960 */ "\x44\x00\x00\x00\x33\x00\x22\x22\x66\x00\x00\x00\x55\x00\x55\x55"
 /* 976 */ "\xcc\x00\x00\x00\x33\x00\x22\x22\x66\x00\x00\x00\x55\x00\x55\x55"
 /* 992 */ "\x05\x55\x05\x55\x05\x55\x05\x55\x46\x55\x5a\xaa\xcc\x55\x05\x55"
 /* 1008 */ "\x46\x55\x5a\xaa\xcc\x55\x05\x55\x06\x55\x0a\x5a\xbb\x55\x05\x55"
 /* 1024 */ "\x46\x55\x5a\xaa\xcc\x55\x05\x55\x06\x55\x0a\x55\x55\x05\x55\x05"
 /* 1040 */ "\x55\x05\x55\x05\x55\x05\x55\x05\x55\x05\x55\x05\x55\x05\x55\x05"
 /* 1056 */ "\x55\x46\x55\x05\x55\x5a\x55\x5a\xaa\xcc\x55\x05\x55\x05\x55\x05"
 /* 1072 */ "\x55\x46\x55\x05\x55\x5a\x55\x5a\xaa\xcc\xcc\xbb\xcc\xbb\xcc\xbb"
 /* 1088 */ "\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb"
 /* 1104 */ "\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb"
 /* 1120 */ "\xcc\xbb\xcc\xbb\xcc\xbb\xcc\xbb\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 1136 */ "\x00\x00\x33\x00\x00\x00\x44\x00\x00\x00\x33\x00\x22\x22\x66\x00"
 /* 1152 */ "\x00\x00\x55\x00\x55\x55\xcc\x00\x00\x00\x33\x00\x22\x22\x66\x00"
 /* 1168 */ "\x00\x00\x55\x00\x55\x55\xcc\x00\x00\x00\x00\x00\x33\x00\x44\x00"
 /* 1184 */ "\x33\x22\x66\x00\x55\x55\xcc\x00\x33\x22\x66\x00\x55\x55\xcc\x00"
 /* 1200 */ "\x33\x02\x46\x00\x05\x05\xbb\x00\x33\x22\x66\x00\x55\x55\xcc\x00"
 /* 1216 */ "\x33\x02\x46\x00\x05\x05\xbb\x00\x33\x00\x00\x00\x00\x22\x00\x55"
 /* 1232 */ "\x00\x22\x00\x55\x00\x02\x00\x05\x00\x22\x00\x55\x00\x02\x02\x46"
 /* 1248 */ "\x00\x22\x00\xaa\x00\x55\x55\xcc\x00\x22\x00\x55\x00\x02\x02\x46"
 /* 1264 */ "\x00\x22\x00\xaa\x00\x55\x55\xcc\x00\x22\x00\x00\x03\x44\x33\x66"
 /* 1280 */ "\x55\xcc\x33\x66\x55\xcc\x03\x46\x05\xbb\x33\x66\x55\xcc\x03\x46"
 /* 1296 */ "\x05\xbb\x33\x66\x55\xcc\x03\x46\x05\xbb\x33\x66\x55\xcc\x03\x46"
 /* 1312 */ "\x05\xbb\x33\x66\x55\xcc\x03\x46\x05\xbb\x33\x66\x55\xcc\x00\x00"
 /* 1328 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x44\x00\x00\x00"
 /* 1344 */ "\x33\x00\x22\x22\x66\x00\x00\x00\x55\x00\x55\x55\xcc\x00\x00\x00"
 /* 1360 */ "\x33\x00\x22\x22\x66\x00\x00\x00\x55\x00\x55\x55\xcc\x00\x00\x00"
 /* 1376 */ "\x03\x00\x00\x02\x55\x02\x55\x02\x05\x02\x55\x02\x46\x02\xaa\x55"
 /* 1392 */ "\xcc\x02\x55\x02\x46\x02\xaa\x55\xcc\x02\x55\x02\x06\x02\x5a\x05"
 /* 1408 */ "\xbb\x02\x55\x02\x46\x02\xaa\x55\xcc\x02\x55\x02\x06\x02\x5a\x05"
 /* 1424 */ "\xbb\x02\x55\x02\x46\x02\xaa\x00\x02\x55\x02\x55\x02\x05\x02\x55"
 /* 1440 */ "\x02\x05\x02\x55\x02\x05\x02\x55\x02\x05\x02\x55\x02\x46\x02\x55"
 /* 1456 */ "\x02\x5a\x02\xaa\x55\xcc\x02\x55\x02\x05\x02\x55\x02\x46\x02\x55"
 /* 1472 */ "\x02\x5a\x02\xaa\x55\xcc\x02\x55\x02\x05\x02\x55\x02\x05\x46\xcc"
 /* 1488 */ "\x46\xcc\x06\xbb\x46\xcc\x06\xbb\x46\xcc\x06\xbb\x46\xcc\x06\xbb"
 /* 1504 */ "\x46\xcc\x06\xbb\x46\xcc\x06\xbb\x46\xcc\x06\xbb\x46\xcc\x06\xbb"
 /* 1520 */ "\x46\xcc\x06\xbb\x46\xcc\x06\xbb\x46\xcc\x06\xbb\x46\xcc\x06\xbb"
 /* 1536 */ "\x46\xcc\x06\xbb\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x33\x00"
 /* 1552 */ "\x00\x00\x44\x00\x00\x00\x33\x00\x22\x22\x66\x00\x00\x00\x55\x00"
 /* 1568 */ "\x55\x55\xcc\x00\x00\x00\x33\x00\x22\x22\x66\x00\x00\x00\x55\x00"
 /* 1584 */ "\x55\x55\xcc\x00\x00\x00\x33\x00\x02\x02\x46\x00\x00\x00\x00\x00"
 /* 1600 */ "\x03\x00\x44\x00\x33\x22\x66\x00\x55\x55\xcc\x00\x33\x22\x66\x00"
 /* 1616 */ "\x55\x55\xcc\x00\x03\x02\x46\x00\x05\x05\xbb\x00\x33\x22\x66\x00"
 /* 1632 */ "\x55\x55\xcc\x00\x03\x02\x46\x00\x05\x05\xbb\x00\x33\x22\x66\x00"
 /* 1648 */ "\x55\x55\xcc\x00\x03\x00\x00\x00\x00\x02\x00\x55\x00\x02\x00\x55"
 /* 1664 */ "\x00\x02\x00\x05\x00\x02\x00\x55\x00\x02\x02\x46\x00\x02\x00\xaa"
 /* 1680 */ "\x00\x55\x55\xcc\x00\x02\x00\x55\x00\x02\x02\x46\x00\x02\x00\xaa"
 /* 1696 */ "\x00\x55\x55\xcc\x00\x02\x00\x55\x00\x02\x02\x06\x00\x02\x00\x05"
 /* 1712 */ "\x05\x05\x05\x46\x5a\xcc\x05\x46\x5a\xcc\x05\x06\x0a\xbb\x05\x46"
 /* 1728 */ "\x5a\xcc\x05\x06\x0a\xbb\x05\x46\x5a\xcc\x05\x06\x0a\xbb\x05\x46"
 /* 1744 */ "\x5a\xcc\x05\x06\x0a\xbb\x05\x46\x5a\xcc\x05\x06\x0a\xbb\x05\x46"
 /* 1760 */ "\x5a\xcc\x05\x06\x0a\xbb\x05\x46\x5a\xcc\x00\x00\x00\x00\x00\x00"
 /* 1776 */ "\x00\x00\x00\x00\x03\x00\x00\x00\x44\x00\x00\x00\x33\x00\x22\x22"
 /* 1792 */ "\x66\x00\x00\x00\x55\x00\x55\x55\xcc\x00\x00\x00\x33\x00\x22\x22"
 /* 1808 */ "\x66\x00\x00\x00\x55\x00\x55\x55\xcc\x00\x00\x00\x03\x00\x02\x02"
 /* 1824 */ "\x46\x00\x00\x00\x05\x00\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05"
 /* 1840 */ "\x46\x05\x5a\x5a\xcc\x05\x05\x05\x46\x05\x5a\x5a\xcc\x05\x05\x05"
 /* 1856 */ "\x06\x05\x0a\x0a\xbb\x05\x05\x05\x46\x05\x5a\x5a\xcc\x05\x05\x05"
 /* 1872 */ "\x06\x05\x0a\x0a\xbb\x05\x05\x05\x46\x05\x5a\x5a\xcc\x05\x05\x05"
 /* 1888 */ "\x06\x05\x0a\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05\x05"
 /* 1904 */ "\x05\x05\x05\x05\x05\x05\x05\x05\x05\x46\x05\x05\x05\x5a\x05\x5a"
 /* 1920 */ "\x5a\xcc\x05\x05\x05\x05\x05\x05\x05\x46\x05\x05\x05\x5a\x05\x5a"
 /* 1936 */ "\x5a\xcc\x05\x05\x05\x05\x05\x05\x05\x06\x05\x05\x05\x0a\x05\x0a"
 /* 1952 */ "\x0a";

unsigned char  *adv_gomoku /* [978] */ =
 /* 0 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 16 */ "\x00\x00\x00\x00\xa0\x00\xa0\x00\x04\x00\x04\x00\x00\xd0\x00\xd0"
 /* 32 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 48 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 64 */ "\x00\x70\x00\x00\x00\x00\xa0\x00\xa1\x00\x00\x00\xa0\x00\x04\x00"
 /* 80 */ "\x04\x00\x00\x00\x04\x00\xd0\xd0\x00\xd0\x00\xd0\x00\xd0\x00\x00"
 /* 96 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x70\x08\x08\x00\x08\x00\x08\x00"
 /* 112 */ "\x08\x00\x08\x00\x40\x40\x00\x40\x00\x40\x00\x40\x00\x40\x00\x00"
 /* 128 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x70"
 /* 144 */ "\x00\x00\x00\x70\x21\x00\x00\x00\x00\x00\xa1\x00\x00\x00\xa1\x00"
 /* 160 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 176 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 192 */ "\x00\x00\x00\x00\x00\x00\x70\x21\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 208 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 224 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 240 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00\x00"
 /* 256 */ "\x00\x70\x21\x00\x00\x00\x00\x00\x00\x00\xa0\x00\xa1\x00\x00\x00"
 /* 272 */ "\xa1\x00\x00\x00\xa0\x00\x00\x00\xa0\x00\x04\x00\x04\x00\x00\x00"
 /* 288 */ "\x04\x00\x00\x00\x04\x00\x00\x00\x04\x00\xd0\xd0\x00\xd0\x00\xd0"
 /* 304 */ "\x00\xd0\x00\xd0\x00\xd0\x00\xd0\x00\xd0\x00\x00\x00\x00\x00\x00"
 /* 320 */ "\x00\x00\x00\x00\x70\x21\x00\x00\x00\x00\x00\x00\x70\x08\x08\x00"
 /* 336 */ "\x08\x00\x08\x00\x08\x00\x08\x00\x08\x00\x08\x00\x08\x00\x08\x00"
 /* 352 */ "\x40\x40\x00\x40\x00\x40\x00\x40\x00\x40\x00\x40\x00\x40\x00\x40"
 /* 368 */ "\x00\x40\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 384 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00\x00\x00\x70"
 /* 400 */ "\x21\x00\x00\x00\x00\x00\x00\x70\x21\x00\x00\x00\x00\x00\xa1\x00"
 /* 416 */ "\x00\x00\xa1\x00\x00\x00\x00\x00\x00\x00\xa1\x00\x00\x00\x00\x00"
 /* 432 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 448 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 464 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 480 */ "\x00\x00\x70\x21\x00\x00\x00\x00\x00\x00\x70\x21\x00\x00\x00\x00"
 /* 496 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 512 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 528 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 544 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 560 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00\x00\x00\x70\x21\x00"
 /* 576 */ "\x00\x00\x00\x00\x00\x70\x21\x00\x00\x00\x00\x00\x00\x00\xa0\x00"
 /* 592 */ "\xa1\x00\x00\x00\xa1\x00\x00\x00\xa0\x00\x00\x00\xa1\x00\x00\x00"
 /* 608 */ "\xa0\x00\x00\x00\xa0\x00\x04\x00\x04\x00\x00\x00\x04\x00\x00\x00"
 /* 624 */ "\x04\x00\x00\x00\x04\x00\x00\x00\x04\x00\x00\x00\x04\x00\x00\xd0"
 /* 640 */ "\x00\xd0\x00\x00\x00\xd0\x00\x00\x00\xd0\x00\x00\x00\xd0\x00\x00"
 /* 656 */ "\x00\xd0\x00\x00\x00\xd0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 672 */ "\x70\x21\x00\x00\x00\x00\x00\x00\x70\x21\x00\x00\x00\x00\x00\x00"
 /* 688 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 704 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 720 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 736 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 752 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 768 */ "\x00\x00\x00\x00\x00\x00\x00\x70\x00\x00\x00\x70\x21\x00\x00\x00"
 /* 784 */ "\x00\x00\x00\x70\x21\x00\x00\x00\x00\x00\x00\x70\x00\x00\x00\x00"
 /* 800 */ "\x00\x00\xa1\x00\x00\x00\xa1\x00\x00\x00\x00\x00\x00\x00\xa1\x00"
 /* 816 */ "\x00\x00\x00\x00\x00\x00\xa1\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 832 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 848 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 864 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 880 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x70\x21"
 /* 896 */ "\x00\x00\x00\x00\x00\x00\x70\x21\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 912 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 928 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 944 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 960 */ "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
 /* 976 */ "\x00";

/* name.c */
word_t         *toplev;

#ifndef _BBS_UTIL_C_
/* menu.c */
commands_t      cmdlist[] = {
    {admin, PERM_SYSOP | PERM_VIEWSYSOP, 2730},
    {Announce, 0, 2731},
    {Boards, 0, 2732},
    {root_board, 0, 2733},
    {Mail, PERM_BASIC, 2734},
    {Talk, 0, 2735},
    {User, 0, 2736},
    {Xyz, 0, 2737},
    {Play_Play, PERM_BASIC, 2738},
    {Name_Menu, PERM_LOGINOK, 2739},
    {Goodbye, 0, 2740},
    {NULL, 0, 0}
};
#endif

/* friend.c */
/* Ptt 各種特別名單的檔名 */
char           *friend_file[8] = {
    FN_OVERRIDES,
    FN_REJECT,
    "alohaed",
    "postlist",
    "",
    FN_CANVOTE,
    FN_WATER,
    FN_VISABLE
};

#ifdef NOKILLWATERBALL
char    reentrant_write_request = 0;
#endif

#ifdef PTTBBS_UTIL
    #ifdef OUTTA_TIMER
	#define COMMON_TIME (SHM->GV2.e.now)
    #else
	#define COMMON_TIME (time(0))
    #endif
#else
    #define COMMON_TIME (now)
#endif
