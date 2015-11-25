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

struct mac_tou {
  u_char daddr[6];  //MAC目的地址                                                                       
  u_char saddr[6];  //MAC源地址                                                                         
  uint16_t types;   //帧类型                                                                              
};

u_char *jiexi_mac(u_char *data, int len, struct mac_tou *mac_r);

#endif	//LINK_LAYER_H
