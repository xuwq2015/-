#ifndef MY_TYPES_H
#define MY_TYPES_H

#include <inttypes.h>

#define CHAR_IP_LEN 17				//点分十进制ipv4地址大小

#define  ETH_P_IP 0x0800 		//IP协议
#define  ETH_P_ARP 0x0806  	//地址解析协议(Address Resolution Protocol)
#define  ETH_P_RARP 0x8035  //返向地址解析协议(Reverse Address Resolution Protocol)
#define  ETH_P_IPV6 0x86DD  //IPV6协议

typedef unsigned char u_char;
typedef unsigned short int u_short;
typedef unsigned int u_int;
typedef unsigned long int l_int;

struct protocol_type {
	uint8_t link_layer;					//链路层协议
	uint8_t network_layer;			//网络层协议
	uint8_t transport_layer;		//传输层协议
	uint8_t application_layer;	//应用层协议
};

struct ip_v4 {                                                                                          
  uint8_t version;          //版本号                                                                    
  u_char ihl;              	//ip首部                                                                     
  u_char tos;              	//服务类型                                                                   
  u_short len;           		//总长度                                                                       
  u_short id;            		//标识                                                                         
  u_short frag;          		//3位分段标志+13位分段偏移数                                                   
  u_char ttl;              	//数据报生存时间                                                             
  u_char protocol;         	//协议字段                                                                   
  u_short check;         		//校验和                                                                       
  uint32_t saddr;         			//源地址                                                                         
  uint32_t daddr;         			//目的地址                                                                       
};

struct ip_v6 {
	uint8_t version;								//版本
	uint8_t traffic_class;										//
	uint32_t flow_label;
	uint16_t payload_length;
	uint8_t next_header;
	uint8_t hop_limit;
	u_char source_addr[16];
	u_char destination_addr[16];
};

#endif	//MY_TYPES_H
