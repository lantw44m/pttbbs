/* $Id: outmail.c,v 1.3 2002/06/28 14:20:12 in2 Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "config.h"
#include "pttstruct.h"


#ifdef HAVE_SETPROCTITLE

#include <sys/types.h>
#include <libutil.h>

void initsetproctitle(int argc, char **argv, char **envp) {
}

#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

char **Argv = NULL;          /* pointer to argument vector */
char *LastArgv = NULL;       /* end of argv */
extern char **environ;

void initsetproctitle(int argc, char **argv, char **envp) {
    register int i;
    
    /* Move the environment so setproctitle can use the space at
       the top of memory. */
    for(i = 0; envp[i]; i++);
    environ = malloc(sizeof(char *) * (i + 1));
    for(i = 0; envp[i]; i++)
	environ[i] = strdup(envp[i]);
    environ[i] = NULL;
    
    /* Save start and extent of argv for setproctitle. */
    Argv = argv;
    if(i > 0)
	LastArgv = envp[i - 1] + strlen(envp[i - 1]);
    else
	LastArgv = argv[argc - 1] + strlen(argv[argc - 1]);
}

static void do_setproctitle(const char *cmdline) {
    char buf[256], *p;
    int i;
    
    strncpy(buf, cmdline, 256);
    buf[255] = '\0';
    i = strlen(buf);
    if(i > LastArgv - Argv[0] - 2) {
	i = LastArgv - Argv[0] - 2;
    }
    strcpy(Argv[0], buf);
    p = &Argv[0][i];
    while(p < LastArgv)
	*p++='\0';
    Argv[1] = NULL;
}

void setproctitle(const char* format, ...) {
    char buf[256];
    
    va_list args;
    va_start(args, format);
    vsprintf(buf, format,args);
    do_setproctitle(buf);
    va_end(args);
}
#endif





#define SPOOL BBSHOME "/out"
#define INDEX SPOOL "/.DIR"
#define NEWINDEX SPOOL "/.DIR.sending"
#define FROM ".bbs@" MYHOSTNAME
#define SMTPPORT 25
char    *smtpname, *hiname;
int     smtpport, hiport;


int waitReply(int sock) {
    char buf[256];
    
    if(read(sock, buf, sizeof(buf)) <= 0)
	return -1;
    else
	return buf[0] - '0';
}

int sendRequest(int sock, char *request) {
    return write(sock, request, strlen(request)) < 0 ? -1 : 0;
}

int connectMailServer(char *servername, int serverport)
{
    int sock;
    struct sockaddr_in addr;
    
    if((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
	perror("socket");
	return -1;
    }
    
    memset(&addr, 0, sizeof(addr));
#ifdef FreeBSD
    addr.sin_len = sizeof(addr);
#endif
    addr.sin_family = AF_INET;
    addr.sin_port = htons(serverport);
    addr.sin_addr.s_addr = inet_addr(servername);
    
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
	printf("servername: %s\n", servername);
	perror(servername);
	close(sock);
	return -1;
    }
    
    if(waitReply(sock) != 2) {
	close(sock);
	return -1;
    }
    
    if(sendRequest(sock, "helo " MYHOSTNAME "\n") || waitReply(sock) != 2) {
	close(sock);
	return -1;
    } else
	return sock;
}

void disconnectMailServer(int sock) {
    sendRequest(sock, "quit\n");
    /* drop the reply :p */
    close(sock);
}

void doSendBody(int sock, FILE *fp, char *from, char *to, char *subject) {
    int n;
    char buf[2048];
    
    n = snprintf(buf, sizeof(buf), "From: %s\nTo: %s\nSubject: %s\n\n",
		 from, to, subject);
    write(sock, buf, n);
    
    while(fgets(buf, sizeof(buf), fp)) {
	if(buf[0] == '.' && buf[1] == '\n')
	    strcpy(buf, "..\n");
	write(sock, buf, strlen(buf));
    }
}

void doSendMail(int sock, FILE *fp, char *from, char *to, char *subject) {
    char buf[256];
    
    snprintf(buf, sizeof(buf), "mail from: %s\n", from);
    if(sendRequest(sock, buf) || waitReply(sock) != 2)
	return;
    
    snprintf(buf, sizeof(buf), "rcpt to: %s\n", to);
    if(sendRequest(sock, buf) || waitReply(sock) != 2)
	return;
    
    if(sendRequest(sock, "data\n") || waitReply(sock) != 3)
	return;
    
    doSendBody(sock, fp, from, to, subject);

    if(sendRequest(sock, "\n.\n") || waitReply(sock) != 2)
	return;
}

void sendMail() {
    int fd, smtpsock, hisock;
    MailQueue mq;
    
    if(access(NEWINDEX, R_OK | W_OK)) {
	if(link(INDEX, NEWINDEX) || unlink(INDEX))
	    /* nothing to do */
	    return;
    }

    smtpsock = connectMailServer(smtpname, smtpport);
    hisock = (hiname != NULL) ? connectMailServer(hiname, hiport) : -1;

    if( smtpsock < 0 && hisock >= 0 ){
	smtpsock = hisock;
	hisock = -1;
    }
    if( smtpsock < 0 && hisock < 0 ){
	fprintf(stderr, "connecting to relay server failure...\n");
	return;
    }
    
    fd = open(NEWINDEX, O_RDONLY);
    flock(fd, LOCK_EX);
    while(read(fd, &mq, sizeof(mq)) > 0) {
	FILE *fp;
	char buf[256];
	
	snprintf(buf, sizeof(buf), "%s%s", mq.sender, FROM);
	if((fp = fopen(mq.filepath, "r"))) {
	    setproctitle("outmail: sending %s", mq.filepath);
	    if( hisock >= 0 &&
		!strstr(mq.rcpt, ".edu.tw")    &&
		!strstr(mq.rcpt, ".twbbs.org") &&
		!strstr(mq.rcpt, "ptt.cc")     &&
		!strstr(mq.rcpt, "ptt2.cc")       ){
		printf("mailto: %s, relay server: %s:%d\n",
		       mq.rcpt, hiname, hiport);
		doSendMail(hisock, fp, buf, mq.rcpt, mq.subject);
	    }
	    else{
		printf("mailto: %s, relay server: %s:%d\n",
		       mq.rcpt, smtpname, smtpport);
		doSendMail(smtpsock, fp, buf, mq.rcpt, mq.subject);
	    }
	    fclose(fp);
	    unlink(mq.filepath);
	} else {
	    perror(mq.filepath);
	}
    }
    flock(fd, LOCK_UN);
    close(fd);
    unlink(NEWINDEX);
    
    disconnectMailServer(smtpsock);
    if( hisock >= 0 )
	disconnectMailServer(hisock);
}

void listQueue() {
    int fd;
    
    if((fd = open(INDEX, O_RDONLY)) >= 0) {
	int counter = 0;
	MailQueue mq;
	
	flock(fd, LOCK_EX);
	while(read(fd, &mq, sizeof(mq)) > 0) {
	    printf("%s:%s -> %s:%s\n", mq.filepath, mq.username, mq.rcpt,
		   mq.subject);
	    counter++;
	}
	flock(fd, LOCK_UN);
	close(fd);
	printf("\nTotal: %d mails in queue\n", counter);
    } else {
	perror(INDEX);
    }
}

void wakeup(int s) {
}

void parseserver(char *sx, char **name, int *port)
{
    char    *save = strdup(sx);
    char    *ptr;
    if( (ptr = strstr(save, ":")) == NULL ){
	*name = strdup(save);
	*port = 25;
    }
    else{
	*ptr = 0;
	*name = strdup(save);
	*port = atoi(ptr + 1);
    }
    free(save);
}

int main(int argc, char **argv, char **envp) {
    int ch;
 
    signal(SIGHUP, wakeup);
    initsetproctitle(argc, argv, envp);
    
    if(chdir(BBSHOME))
	return 1;
    while((ch = getopt(argc, argv, "qhs:o:")) != -1) {
	switch(ch) {
	case 's':
	    parseserver(optarg, &smtpname, &smtpport);
	    break;
	case 'o':
	    parseserver(optarg, &hiname, &hiport);
	    break;
	case 'q':
	    listQueue();
	    return 0;
	default:
	    printf("usage:\toutmail [-qh] -s host[:port] [-o host[:port]]\n"
		   "\t-q\tlistqueue\n"
		   "\t-h\thelp\n"
		   "\t-s\tset default smtp server to host[:port]\n"
		   "\t-o\tset non-Tanet smtp server to host[:port]\n");
	    return 0;
	}
    }

    if( smtpname == NULL ){
#ifdef RELAY_SERVER_IP
	smtpname = RELAY_SERVER_IP;
#else
	smtpname = "127.0.0.1";
#endif
	smtpport = 25;
    }

    for(;;) {
	sendMail();
	setproctitle("outmail: sleeping");
	sleep(60 * 3); /* send mail every 3 minute */
    }
    return 0;
}
