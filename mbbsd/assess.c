#include "bbs.h"

#ifdef ASSESS

/* do (*num) + n, n is integer. */
inline static void inc(unsigned char *num, int n)
{
    if (n >= 0 && SALE_MAXVALUE - *num <= n)
	(*num) = SALE_MAXVALUE;
    else if (n < 0 && *num < -n)
	(*num) = 0;
    else
	(*num) += n;
}

int inc_goodpost(int uid, int num)
{
    passwd_query(uid, &xuser);
    inc(&xuser.goodpost, num);
    passwd_update(uid, &xuser);
    return xuser.goodpost;
}

int inc_badpost(int uid, int num)
{
    passwd_query(uid, &xuser);
    inc(&xuser.badpost, num);
    passwd_update(uid, &xuser);
    return xuser.badpost;
}

int inc_goodsale(int uid, int num)
{
    passwd_query(uid, &xuser);
    inc(&xuser.goodsale, num);
    passwd_update(uid, &xuser);
    return xuser.goodsale;
}

int inc_badsale(int uid, int num)
{
    passwd_query(uid, &xuser);
    inc(&xuser.badsale, num);
    passwd_update(uid, &xuser);
    return xuser.badsale;
}

void set_assess(int uid, unsigned char num, int type)
{
    passwd_query(uid, &xuser);
    switch (type){
	case GOODPOST:
	    xuser.goodpost = num;
	    break;
	case BADPOST:
	    xuser.badpost = num;
	    break;
	case GOODSALE:
	    xuser.goodsale = num;
	    break;
	case BADSALE:
	    xuser.badsale = num;
	    break;
    }
    passwd_update(uid, &xuser);
}
#endif
