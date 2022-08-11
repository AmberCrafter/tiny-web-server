#include <arpa/inet.h> /* inet_ntoa */
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* Simplifies calls to bind(), connect(), and accept() */
typedef struct sockaddr SA;

typedef struct {
	char filename[512];
	off_t offset;              /* for support Range */
	size_t end;
} http_request;


char *process(int fd, struct sockaddr_in *clientaddr);
void serve_static(int out_fd, int in_fd, http_request *req,size_t total_size);
void client_error(int fd, int status, char *msg, char *longmsg);
void parse_request(int fd, http_request *req);
#ifdef LOG_ACCESS
void log_access(int status, struct sockaddr_in *c_addr, http_request *req);
#endif

void parse_request(int fd, http_request *req);
void url_decode(char* src, char* dest, int max);
int open_listenfd(int port);
void handle_directory_request(int out_fd, int dir_fd, char *filename);
void format_size(char* buf, struct stat *stat);
ssize_t writen(int fd, void *usrbuf, size_t n);
