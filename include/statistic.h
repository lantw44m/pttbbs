#ifndef _STATISTIC_H_
#define _STATISTIC_H_
#define STAT(X, OP) do { \
    if(SHM && SHM->version==SHM_VERSION && 0<=(X) && (X)<STAT_MAX) \
      SHM->statistic[X] OP; \
} while(0)
#define STATINC(X) STAT(X, ++)

enum { // XXX description in shmctl.c
    STAT_LOGIN,
    STAT_SHELLLOGIN,
    STAT_VEDIT,
    STAT_TALKREQUEST,
    STAT_WRITEREQUEST,
    STAT_MORE,
    STAT_SYSWRITESOCKET,
    STAT_SYSSELECT,
    STAT_SYSREADSOCKET,
    STAT_DOSEND,
    STAT_SEARCHUSER,
    STAT_THREAD,
    STAT_SELECTREAD,
    STAT_QUERY,
    STAT_DOTALK,
    STAT_FRIENDDESC,
    STAT_FRIENDDESC_FILE,
    STAT_PICKMYFRIEND,
    STAT_PICKBFRIEND,
    STAT_GAMBLE,
    STAT_DOPOST,
    STAT_READPOST,
    STAT_RECOMMEND,
    STAT_TODAYLOGIN_MIN,
    STAT_TODAYLOGIN_MAX,
    /* insert here. don't forget update shmctl.c */
    STAT_NUM,
    STAT_MAX=512
};
#endif
