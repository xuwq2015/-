#ifndef LINK_LAYER_H
#define LINK_LAYER_H

#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <arpa/inet.h>
#include "./my_types.h"
#include "./network_layer.h" 

#define ETHERNET_II 0x05DC				//如果值大于0x05DC则为Ethernet II帧
#define NOVELL_ETHER 0xFFFF				//如果等于此值，则为Novell Ether帧
#define ETHERNET_SNAP 0xAAAA			//如果等于此值，则为Ethernet SNAP帧,否则为Ethernet 802.3/802.2格式的帧

#define MAC_MAX_LEN 1500			//mac数据段最大长度

#define ETHERNET_TYPES 0X10
#define NOVELL_TYPES 0x20
#define SNAP_TYPES 0x30
#define IEEE_TYPES 0x40

struct frame_types {
	uint8_t link_types;									//帧格式类型
	unsigned char daddr[6];							//MAC目的地址
	unsigned char saddr[6];							//MAC源地址
	uint16_t network_types;							//网络层协议类型
	uint16_t network_len;								//链路层数据段长度
	unsigned char data[MAC_MAX_LEN];		//链路层数据段内容
/*
	union {
		struct ethernet eth_eth;
		struct novell_ether n_eth;
		struct ethernet_snap snap_eth;
		struct IEEE ieee_eth;
	}
*/
};

struct ethernet {		//ethernet II帧格式
  uint16_t types;   //帧类型                                                                              
};

struct novell_ether {		//Novell Ether帧格式
	uint16_t len;
	uint8_t dsap;
	uint8_t ssap;
};

struct ethernet_snap {	//ethrnet SNAP帧格式
	uint16_t len;
  uint8_t dsap;
  uint8_t ssap;
  uint8_t cntl;
	unsigned char org_code[3];
	uint16_t types;
};

struct IEEE {	//Ethrnet 802.3/802.2帧格式
	uint16_t len;
	uint8_t dsap;
	uint8_t ssap;
	uint8_t cntl;
};

void jiexi_mac(u_char *data, int len, struct frame_types *mac_r);

#endif	//LINK_LAYER_H
