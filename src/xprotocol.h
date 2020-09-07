#ifndef __XPROTOCOL_H
#define __XPROTOCOL_H

#include "public.h"
#include <sys/types.h>
/*
	size_t
*/

#include "md5.h"
#include <assert.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/if_ether.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netpacket/packet.h>
/*
For struct sockaddr_ll:
		struct sockaddr_ll
		{
		unsigned short int sll_family; // һ��ΪAF_PACKET
		unsigned short int sll_protocol; //  �ϲ�Э��
		int sll_ifindex; //  �ӿ�����
		unsigned short int sll_hatype; //  ��ͷ����
		unsigned char sll_pkttype; //  ������
		unsigned char sll_halen; //  ��ַ����
		unsigned char sll_addr[8]; //  MAC��ַ
		};
*/

#include <sys/ioctl.h>
/*
	int ioctl(int d,int request,....);
*/


#include <net/if.h>
/*
	unsigned int if_nametoindex(const char *ifname);
	struct ifreq {
	 union {
	  char ifrn_name[IFNAMESIZ]; //����ӿ���
	 } ifr_ifrn;

	 union {
	  struct sockaddr ifru_addr; //����IP��ַ
	  struct sockaddr ifru_dstaddr; //Ŀ��IP��ַ
	  struct sockaddr ifru_broadaddr; //�㲥IP��ַ
	  struct sockaddr ifru_netmask; //�������������ַ
	  struct sockaddr ifru_hwaddr; //����MAC��ַ
	  short ifru_flags; //����ӿڱ��
	  int ifru_ivalue; //��ͬ�������岻ͬ
	  struct ifmap ifru_map; //������ַӳ��
	  int ifru_mtu; //����䵥Ԫ
	  char ifru_slave[IFNAMSIZ]; //ռλ��
	  char ifru_newname[IFNAMSIZE]; //������
	  void __user* ifru_data; //�û�����
	  struct if_settings ifru_settings; //�豸Э������
	 } ifr_ifru;

	};
*/


#define AUTH_VERSION 0x01

/** eap package type */
#define AUTH_TYPE_EAP 0X00
#define AUTH_TYPE_EAPOL 0X01
#define AUTH_TYPE_LOGOFF 0X02

/** code scope */
#define EAP_CODE_REQUEST 0x01
#define EAP_CODE_RESPONSE 0x02
#define EAP_CODE_SUCCESS 0x03
#define EAP_CODE_FAILURE 0x04

/* response type */
#define EAP_EXT_IDENTIFIER 0x01
#define EAP_EXT_NOTIFICATION 0x02
#define EAP_EXT_NAK 0x03
#define EAP_EXT_MD5_CHALLENGE 0x04
#define EAP_EXT_OTP 0x05
#define EAP_EXT_GTC 0x06


/* mk_pkt control cmd, for make different packet*/
#define START 0
#define RESPONSE_ID 1
#define RESPONSE_MD5 2
#define LOGOFF 3
#define HEARTBEAT 4

#define XONLINE 1
#define XOFFLINE 0


/* global value *********************************/
enum LOGFLAG { ON = 1, OFF = 0 };

extern enum LOGFLAG log_flag;
extern struct sockaddr_ll sa_ll;
extern struct ethhdr eth_header;
extern struct ethhdr broadcast_eth_header;
extern int xstatus;
extern int x_is_resp_fail;
extern int x_is_broadcast;
extern char x_resp_md5[16];
extern char nodifyMsg[256];
extern char xUpdateAt[64];


/* pack format ***********************************/
struct _md5_data {
	uint8_t size;
	uint8_t data[48]; // usually 16
};

typedef struct _ext_data {
	uint8_t code; // 2: response, it's always 2 in dial route, but in the
		      // request pkt, it's maybe 4(failure), 3(success)
	uint8_t id;   // ??? 2,4: account identity,  3: md5 response
	uint16_t len; // same as the auth_len, is the total length of eap header
	uint8_t eap_rspn_type; // 4: MD5-Chanllenge, 1: Identity
	union {
		struct _md5_data md5_data; // passwd value after md5 change
		uint8_t id_data[49];	   // Identity num
	} data; // store information, such as Identity num, passwd value
} eap_header;

typedef struct authen_8021x_header {
	uint8_t version;   //  always 1 in the dial route, but it's maybe
			   //  2(switch)
	uint8_t auth_type; // 0: eap packet, 1: start,  2: logoff
	uint16_t auth_len; // 0 means no body, otherwise, is the total length of
			   // eap packet
	struct _ext_data ext_data; // eap header
} authhdr;


void init_dial_env(void);
void logon(void);
void logoff(void);
void *serve_forever_x(void *args);


int crt_sock(struct ifreq *);
int create_ethhdr_sock(struct ethhdr *);
void recv_eap_pkt(const int, struct sockaddr_ll *, struct ethhdr *);
int mk_response_md5(authhdr *, uint8_t *);
size_t mk_pkt(uint8_t *, int, uint8_t *, struct ethhdr *);
void parse_pkt(uint8_t *, struct ethhdr *, int);
void send_pkt(int, uint8_t *, size_t);

#endif
