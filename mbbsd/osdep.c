/* $Id$ */
#include "bbs.h"

#if defined(__linux__)
#include <sys/types.h>
#include <string.h>

/*   size_t
 *   strlcat(char *dst, const char *src, size_t size);
 */
/*
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Appends src to string dst of size siz (unlike strncat, siz is the
 * full size of dst, not space left).  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz <= strlen(dst)).
 * Returns strlen(src) + MIN(siz, strlen(initial dst)).
 * If retval >= siz, truncation occurred.
 */
size_t
strlcat(dst, src, siz)
	char *dst;
	const char *src;
	size_t siz;
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;
	size_t dlen;

	/* Find the end of dst and adjust bytes left but don't go past end */
	while (n-- != 0 && *d != '\0')
		d++;
	dlen = d - dst;
	n = siz - dlen;

	if (n == 0)
		return(dlen + strlen(s));
	while (*s != '\0') {
		if (n != 1) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';

	return(dlen + (s - src));	/* count does not include NUL */
}

/* ------------------------------------------------------------------------ */

/*   size_t
 *   strlcpy(char *dst, const char *src, size_t size);
 */

/*
 * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns strlen(src); if retval >= siz, truncation occurred.
 */
size_t strlcpy(dst, src, siz)
	char *dst;
	const char *src;
	size_t siz;
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;

	/* Copy as many bytes as will fit */
	if (n != 0 && --n != 0) {
		do {
			if ((*d++ = *s++) == 0)
				break;
		} while (--n != 0);
	}

	/* Not enough room in dst, add NUL and traverse rest of src */
	if (n == 0) {
		if (siz != 0)
			*d = '\0';		/* NUL-terminate dst */
		while (*s++)
			;
	}

	return(s - src - 1);	/* count does not include NUL */
}

#endif

#if defined(linux) || defined(Solaris)
char           *
strcasestr(const char *big, const char *little)
{
    char           *ans = (char *)big;
    int             len = strlen(little);
    char           *endptr = (char *)big + strlen(big) - len;

    while (ans <= endptr)
	if (!strncasecmp(ans, little, len))
	    return ans;
	else
	    ans++;
    return 0;
}

#endif

#ifdef Solaris

/*
 * Scan the directory dirname calling select to make a list of
selected
 * directory entries then sort using qsort and compare routine
dcomp.
 * Returns the number of entries and a pointer to a list of
pointers to
 * struct dirent (through namelist). Returns -1 if there were any
errors.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

/*
 * The DIRSIZ macro is the minimum record length which will hold
the directory
 * entry. This requires the amount of space in struct dirent
without the
 * d_name field, plus enough space for the name and a terminating
nul byte
 * (dp->d_namlen + 1), rounded up to a 4 byte boundary.
 */
#undef DIRSIZ
#define DIRSIZ(dp) \
         ((sizeof(struct dirent) - sizeof(dp)->d_name) + \
         ((strlen((dp)->d_name) + 1 + 3) &~ 3))
#if 0
         ((sizeof(struct dirent) - sizeof(dp)->d_name) + \
         (((dp)->d_namlen + 1 + 3) &~ 3))
#endif

int
scandir(dirname, namelist, select, dcomp)
        const char *dirname;
        struct dirent ***namelist;
        int (*select) (struct dirent *);
        int (*dcomp) (const void *, const void *);
{
        register struct dirent *d, *p, **names;
        register size_t nitems;
        struct stat stb;
        long arraysz;
        DIR *dirp;

        if ((dirp = opendir(dirname)) == NULL)
                return(-1);
        if (fstat(dirp->dd_fd, &stb) < 0)
                return(-1);

        /*
         * estimate the array size by taking the size of thedirectory file
         * and dividing it by a multiple of the minimum sizeentry.
         */
        arraysz = (stb.st_size / 24);
     names = (struct dirent **)malloc(arraysz * sizeof(struct dirent *));
        if (names == NULL)
                return(-1);

        nitems = 0;
        while ((d = readdir(dirp)) != NULL) {
                if (select != NULL && !(*select)(d))
                        continue; /* just selected names */
                /*
                 * Make a minimum size copy of the data
                 */
                p = (struct dirent *)malloc(DIRSIZ(d));
                if (p == NULL)
                        return(-1);
                p->d_ino = d->d_ino;
                p->d_off = d->d_off;
                p->d_reclen = d->d_reclen;
                memcpy(p->d_name, d->d_name, strlen(d->d_name) +1);
#if 0
                p->d_fileno = d->d_fileno;
                p->d_type = d->d_type;
                p->d_reclen = d->d_reclen;
                p->d_namlen = d->d_namlen;
                bcopy(d->d_name, p->d_name, p->d_namlen + 1);
#endif
                /*
                 * Check to make sure the array has space left and
                 * realloc the maximum size.
                 */
                if (++nitems >= arraysz) {
                        if (fstat(dirp->dd_fd, &stb) < 0)
                                return(-1); /* just might have grown */
                        arraysz = stb.st_size / 12;
                        names = (struct dirent **)realloc((char*)names,
                            arraysz * sizeof(struct dirent*));
                        if (names == NULL)
                                return(-1);
                }
                names[nitems-1] = p;
        }
        closedir(dirp);
        if (nitems && dcomp != NULL)
                qsort(names, nitems, sizeof(struct dirent *),dcomp);
        *namelist = names;
        return(nitems);
}

/*
 * Alphabetic order comparison routine for those who want it.
 */
int
alphasort(d1, d2)
        const void *d1;
        const void *d2;
{
        return(strcmp((*(struct dirent **)d1)->d_name,
            (*(struct dirent **)d2)->d_name));
} 
int
flock (int fd, int f)
{
    if( f == LOCK_EX )
        return lockf(fd, F_LOCK, 0L);

    if( f == LOCK_UN )
        return lockf(fd, F_ULOCK, 0L);

    return -1;
}

void
unsetenv(name)
        char *name;
{
        extern char **environ;
        register char **pp;
        int len = strlen(name);

        for (pp = environ; *pp != NULL; pp++)
        {
                if (strncmp(name, *pp, len) == 0 &&
                    ((*pp)[len] == '=' || (*pp)[len] == '\0'))
                        break;
        }

        for (; *pp != NULL; pp++)
                *pp = pp[1];
}





#include <sys/stat.h>
#include <sys/swap.h>
#include <sys/loadavg.h>


double swapused(int *total, int *used)
{
    double          percent = -1;
    register int cnt, i;
    register int free;
    struct swaptable *swt;
    struct swapent *ste;
    static char path[256];
    cnt = swapctl(SC_GETNSWP, 0);
    swt = (struct swaptable *)malloc(sizeof(int) +
                                     cnt * sizeof(struct swapent));
    if (swt == NULL)
    {
        return 0;
    }
    swt->swt_n = cnt;

    /* fill in ste_path pointers: we don't care about the paths, so we point
       them all to the same buffer */
    ste = &(swt->swt_ent[0]);
    i = cnt;
    while (--i >= 0)
    {
        ste++->ste_path = path;
    }
    /* grab all swap info */
    swapctl(SC_LIST, swt);

    /* walk thru the structs and sum up the fields */
    *total = free = 0;
    ste = &(swt->swt_ent[0]);
    i = cnt;
    while (--i >= 0)
    {
        /* dont count slots being deleted */
        if (!(ste->ste_flags & ST_INDEL) &&
            !(ste->ste_flags & ST_DOINGDEL))
        {
            *total += ste->ste_pages;
            free += ste->ste_free;
        }
        ste++;
    }

    *used = *total - free;
    if( total != 0)
        percent = (double)*used / (double)*total;
    else
        percent = 0;

    return percent;
}
#endif

#if __FreeBSD__

#include <kvm.h>


double
swapused(int *total, int *used)
{
    double          percent = -1;
    kvm_t          *kd;
    struct kvm_swap swapinfo;
    int             pagesize;

    kd = kvm_open(NULL, NULL, NULL, O_RDONLY, NULL);
    if (kd) {
	if (kvm_getswapinfo(kd, &swapinfo, 1, 0) == 0) {
	    pagesize = getpagesize();
	    *total = swapinfo.ksw_total * pagesize;
	    *used = swapinfo.ksw_used * pagesize;
	    if (*total != 0)
		percent = (double)*used / (double)*total;
	}
	kvm_close(kd);
    }
    return percent;
}

#endif

#if _freebsd_ || defined(Solaris)

int
cpuload(char *str)
{
    double          l[3] = {-1, -1, -1};
    if (getloadavg(l, 3) != 3)
	l[0] = -1;

    if (str) {
	if (l[0] != -1)
	    sprintf(str, " %.2f %.2f %.2f", l[0], l[1], l[2]);
	else
	    strcpy(str, " (unknown) ");
    }
    return (int)l[0];
}
#endif

#ifdef linux
int
cpuload(char *str)
{
    double          l[3] = {-1, -1, -1};
    FILE           *fp;

    if ((fp = fopen("/proc/loadavg", "r"))) {
	if (fscanf(fp, "%lf %lf %lf", &l[0], &l[1], &l[2]) != 3)
	    l[0] = -1;
	fclose(fp);
    }
    if (str) {
	if (l[0] != -1)
	    snprintf(str, sizeof(str), " %.2f %.2f %.2f", l[0], l[1], l[2]);
	else
	    strcpy(str, " (unknown) ");
    }
    return (int)l[0];
}

double
swapused(int *total, int *used)
{
    double          percent = -1;
    char            buf[101];
    FILE           *fp;

    if ((fp = fopen("/proc/meminfo", "r"))) {
	while (fgets(buf, 100, fp) && strstr(buf, "SwapTotal:") == NULL);
	sscanf(buf, "%*s %d", total);
	fgets(buf, 100, fp);
	sscanf(buf, "%*s %d", used);
	*used = *total - *used;
	if (*total != 0)
	    percent = (double)*used / (double)*total;
	fclose(fp);
    }
    return percent;
}

#endif
