#ifndef __PUBLIC_H_
#define __PUBLIC_H_

#include <stdint.h>
#include <stdio.h>
#include <linux/if_ether.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netpacket/packet.h>
#include <time.h>
#include <sys/time.h>


#define PASSWDFILE "/etc/fsn.conf"


extern char user_id[32];
extern char passwd[32];
extern char interface_name[32];
extern char listen_ip[32];
extern int listen_port;
extern int is_login;
extern int is_stop_auth;

extern struct sockaddr_in my_ip;
extern char my_mac[ETH_ALEN];


void get_from_file(char *);
void save_to_file(char *);

void print_mac(char *src);
void print_hex(char *hex, int len);

int checkCPULittleEndian();
uint32_t big2little_32(uint32_t A);

void get_ctime(char *buf, int len);
int is_forbid_time();
char *mac_ntoa(char src[ETH_ALEN]);

#endif
