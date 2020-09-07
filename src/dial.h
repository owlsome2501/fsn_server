#ifndef __DIAL_H
#define __DIAL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <net/if.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>

#define HTTP_TIMEOUT 10

void sig_action(int signo);
void *http_server(void *args);

#endif
