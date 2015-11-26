#ifndef NETWORK_LAYER_H
#define NETWORK_LAYER_H

#include <string.h>
#include "./my_types.h"
#include "./link_layer.h"

#define IP_DATA_LEN 1500

#define IP_PROTOCOL 0x10
#define ARP_PROTOCOL 0x20
#define RARP_PROTOCOL 0x30
#define ICMP_PROTOCOL 0x40
#define IGMP_PROTOCOL 0x50

struct network_data {
	uint8_t types;
	union {
		struct ip_v4;
		struct ip_v6;
	}
	unsigned char data[IP_DATA_LEN];
};

struct ip_v4 {
  uint8_t version;          //版本号                                                                    
  u_char ihl;               //ip首部                                                                     
  u_char tos;               //服务类型                                                                   
  u_short len;              //总长度                                                                       
  u_short id;               //标识                                                                         
  u_short frag;             //3位分段标志+13位分段偏移数                                                   
  u_char ttl;               //数据报生存时间                                                             
  u_char protocol;          //协议字段                                                                   
  u_short check;            //校验和                                                                       
  uint32_t saddr;               //源地址                                                                              
  uint32_t daddr;               //目的地址                                                                            
};

struct ip_v6 {                                                                                          
  uint8_t version;                //版本                                                                
  uint8_t traffic_class;                    //                                                          
  uint32_t flow_label;                                                                                  
  uint16_t payload_length;                                                                              
  uint8_t next_header;                                                                                  
  uint8_t hop_limit;                                                                                    
  u_char source_addr[16];                                                                               
  u_char destination_addr[16];                                                                          
};

u_char *jiexi_ipv4(u_char *data, struct ip_v4 *ip_r);

void jiexi_ipv6(u_char *data, struct ip_v6 *ip_r);

#endif	//NETWORK_LAYER_H
