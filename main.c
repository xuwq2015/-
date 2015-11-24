#include <stdio.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <string.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <linux/if_ether.h>
#include <unistd.h>
#include <net/if.h>
//#include <arpa/inet.h>

typedef unsigned char u_char;
typedef unsigned short int u_short;
typedef unsigned int u_int;
typedef unsigned long int l_int;

struct mac_tou {
	u_char daddr[6];	//MAC目的地址
	u_char saddr[6];	//MAC源地址
	u_short types;	//帧类型
};
struct ip_tou {
  	u_char version;          //版本号
  	u_char ihl;              //ip首部
  	u_char tos;              //服务类型
  	u_short len;           //总长度
  	u_short id;            //标识
  	u_short frag;          //3位分段标志+13位分段偏移数
  	u_char ttl;              //数据报生存时间
  	u_char protocol;         //协议字段
  	u_short check;         //校验和
  	u_int saddr;         //源地址
	u_int daddr;         //目的地址
};

void inttoip( int ip_num, char *ip )
{
    	//strcpy( ip, (char*)inet_ntoa( htonl( ip_num ) ) );
    	struct in_addr addr;
	addr.s_addr = htonl(ip_num);
	inet_ntop(AF_INET, (void *)&addr, ip, 16); 
}
char *ip_zhuan(int data, char *buffer) {
	buffer[0] = (data & 0xFF000000) >> 6;
	buffer[1] = '.';
	buffer[2] = (data & 0xFF0000) >> 4;
	buffer[3] = '.';
	buffer[4] = (data & 0xFF00) >> 2;
	buffer[5] = '.';
	buffer[6] = data & 0xFF;
	buffer[7] = '\0';
	return buffer;
}

u_char *jiexi_ip(u_char *data, struct ip_tou *ip_r) {
	ip_r->version = (data[0] & 0xF0) >> 4;
	ip_r->ihl = data[0] & 0x0F;
	ip_r->tos = data[1];
	ip_r->len = (u_short)((data[2] << 8) + data[3]);
	ip_r->id = (u_short)((data[4] << 8) + data[5]);
	ip_r->frag = (u_short)((data[6] << 8) + data[7]);
	ip_r->ttl = data[8];
	ip_r->protocol = data[9];
	ip_r->check = (u_short)((data[10] << 8) + data[11]);

	ip_r->saddr = (data[12] << 24) + (data[13] << 16) + (data[14] <<8) + data[15];

	ip_r->daddr = (data[16] << 24) + (data[17] << 16) + (data[18] <<8) + data[19];
	return data+20;
}
u_char *jiexi_mac(u_char *data, int len, struct mac_tou *mac_r) {
	u_char *ip_data;
	strncpy(mac_r->daddr, data, 6);
	data += 6;
	strncpy(mac_r->saddr, data, 6);
	data += 6;
	strncpy(mac_r->saddr, data, 2);
	data += 2;
	ip_data = data;
	data[len - 14 - 5] = '\0';
	return ip_data;
}

int main(int argc, char *argv[]) {
  	int sock, n, i;
	char ip_addr[2048];
  	u_char buffer[2048];
	u_char *unresolved;
  	struct ethhdr *eth;
  	struct iphdr *iph;
  	struct ifreq ethreq;

	struct in_addr addr;

	struct mac_tou mac_r;
	struct ip_tou ip_r;

	/*创建原始套接字*/
  	if((sock=socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL)))<0) {
    		perror("socket");
    		exit(1);
  	}


 	/* 修改网卡为混合模式*/
  	strncpy(ethreq.ifr_name,"eno16777736",IFNAMSIZ);
  	if (ioctl(sock,SIOCGIFFLAGS,&ethreq)==-1) {
    		perror("ioctl");
    		close(sock);
    		exit(1);
  	}
  	ethreq.ifr_flags|=IFF_PROMISC;
  	if (ioctl(sock,SIOCSIFFLAGS,&ethreq)==-1) {
    		perror("ioctl");
    		close(sock);
    		exit(1);
  	}

	/*抓取网络数据包*/
  	while(1) {
		/*读取经过网卡的所有数据包，包括非发往本机的数据包*/
    		n = recvfrom(sock, buffer, 2048, 0, NULL, NULL);
		unresolved = buffer;
    		printf("%d bytes read\n", n);
		unresolved = jiexi_mac(unresolved, n, &mac_r);
		printf("MAC目的地址:%x:%x:%x:%x:%x:%x\n", mac_r.daddr[0], mac_r.daddr[1], mac_r.daddr[2], mac_r.daddr[3],
																							mac_r.daddr[4],mac_r.daddr[5]);
		printf("MAC源地址:%x:%x:%x:%x:%x:%x\n", mac_r.saddr[0], mac_r.saddr[1], mac_r.saddr[2], mac_r.saddr[3],
																						mac_r.saddr[4], mac_r.saddr[5]);
		unresolved = jiexi_ip(unresolved, &ip_r);
		addr.s_addr = htonl(ip_r.daddr);
		inet_ntop(AF_INET, (void *)&addr, ip_addr, 16);
		printf("IP目的地址%s\n", ip_addr);
	}
  	return 0;
}
