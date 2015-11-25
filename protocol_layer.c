#include "./protocol_layer.h"

int get_tou(unsigned char data[], int data_len) {
	unsigned char *data_p = data;
	unsigned char ip_addr[CHAR_IP_LEN];
	unsigned char ipv4_addr_buf[INET_ADDRSTRLEN];
	unsigned char ipv6_addr_buf[INET6_ADDRSTRLEN];
 
	struct sockaddr_in addr;
	struct mac_tou mac_r;
	struct ip_v4 ip_r;
	struct ip_v6 ipv6_r;
 
	struct sockaddr_in ipv4_addr;
	//struct sockaddr_in6 ipv6_addr;                                                                            
	struct in6_addr ipv6_addr;
 
	printf("%d bytes read\n", data_len);
 
	data_p = jiexi_mac(data_p, data_len, &mac_r);
	printf("MAC mu_di_di_zhi:%x:%x:%x:%x:%x:%x\t", mac_r.daddr[0], mac_r.daddr[1], mac_r.daddr[2], mac_r.daddr[3],
                                               		mac_r.daddr[4],mac_r.daddr[5]);
	printf("MAC yuan_di_zhi:%x:%x:%x:%x:%x:%x\n", mac_r.saddr[0], mac_r.saddr[1], mac_r.saddr[2], mac_r.saddr[3],
                                            		mac_r.saddr[4], mac_r.saddr[5]);
 
	if(mac_r.types == ETH_P_IP) {
		printf("xie_yi_lei_xing: IPv4\t\t%x\t%x\n", mac_r.types, ETH_P_IP);
    
		data_p = jiexi_ipv4(data_p, &ip_r);
                                                                                                        
		//ipv4_addr.sin_addr.s_addr = htonl(ip_r.daddr);                                                               
		ip_r.daddr = htonl(ip_r.daddr);                                                                 
		inet_ntop(AF_INET, (void *)&ip_r.daddr, ipv4_addr_buf, INET_ADDRSTRLEN);                        
		printf("IP mu_di_di_zhi%s\t", ipv4_addr_buf);                                                       
                                                                                                         
		//ipv4_addr.sin_addr.s_addr = htonl(ip_r.saddr);                                                              
		ip_r.saddr = htonl(ip_r.saddr);                                                                 
		inet_ntop(AF_INET, (void *)&ip_r.saddr, ipv4_addr_buf, INET_ADDRSTRLEN);                                      
		printf("IP yuan_di_zhi:%s\n", ipv4_addr_buf);                                                       
	} else if(mac_r.types == ETH_P_ARP) {                                                                 
		printf("xie_yi_lei_xing: ARP\t\t%x\t%x\n", mac_r.types, ETH_P_ARP);                                              
    
	} else if(mac_r.types == ETH_P_RARP) {                                                                
		printf("xie_yi_lei_xing: RARP\n");                                                                  
	} else if(mac_r.types == ETH_P_IPV6) {                                                                
		printf("xie_yi_lei_xing: IPv6\n");                                                                  
		jiexi_ipv6(data_p, &ipv6_r);                                                                                  
                                                                                                     
		//source_addr                                                                                   
		//destination_addr                                                                              
                                                                                                     
		strncpy(ipv6_addr.s6_addr, ipv6_r.source_addr, 16);                                             
		inet_ntop(AF_INET6, (void *)&ipv6_addr.s6_addr, ipv6_addr_buf, INET6_ADDRSTRLEN);               
		printf("IP mu_di_di_zhi%s\t", ipv6_addr_buf); 
/*                                                                                                                
		addr.sin_addr.s_addr = htonl(ip_r.daddr);                                                                     
		inet_ntop(AF_INET, (void *)&addr, ip_addr, 16);                                                     
		printf("IP mu_di_di_zhi%s\t", ip_addr);                                                             
                                                                                                        
		addr.sin_addr.s_addr = htonl(ip_r.saddr);                                                                     
		inet_ntop(AF_INET, (void *)&addr, ip_addr, 16);                                                     
		printf("IP yuan_di_zhi:%s\n", ip_addr);                                                             
*/                                                                                                  
	} else {                                                                                                        
		printf("xie_yi_lei_xing: qita\t%x\n", mac_r.types);                                                              
   
	}                                                                                                     
	printf("\n\n");                                                                                       
}
