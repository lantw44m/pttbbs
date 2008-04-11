#ifndef _LIBBBS_H_
#define _LIBBBS_H_

#include "config.h"
#include "common.h"
#include "cmsys.h"
#include "pttstruct.h"

/* name.c */
extern int is_validuserid(const char *id);

/* path.c */
/* XXX set*() all assume buffer size = PATHLEN */
extern void setdirpath(char *buf, const char *direct, const char *fname);
extern void setbpath (char *buf, const char *boardname);
extern void setbfile (char *buf, const char *boardname, const char *fname);
extern void setbnfile(char *buf, const char *boardname, const char *fname, int n);
extern void setapath(char *buf, const char *boardname);
extern void setadir (char *buf, const char *path);
extern void sethomepath(char *buf, const char *userid);
extern void sethomedir (char *buf, const char *userid);
extern void sethomeman (char *buf, const char *userid);
extern void sethomefile(char *buf, const char *userid, const char *fname);
// setbdir
// setuserfile

/* file.c */
extern int belong(const char *filelist, const char *key);

/* money.c */
extern int give_tax(int money);
extern const char* money_level(int money);

/* string.c */  
extern void obfuscate_ipstr(char *s);

/* time.c */
extern const char *Now();	// m3 flavor time string

#endif
