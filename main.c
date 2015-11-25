#include <stdio.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <string.h>
#include <linux/ip.h>
//#include <linux/in.h>
#include <linux/if_ether.h>
#include <unistd.h>
#include <net/if.h>
#include "./my_types.h"
#include "./protocol_layer.h"

int main(int argc, char *argv[]) {
  int sock;
  u_char buffer[2048];
	int buffer_len = 0;
  struct ifreq ethreq;

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
    buffer_len = recvfrom(sock, buffer, 2048, 0, NULL, NULL);
		get_tou(buffer, buffer_len);
	}
  return 0;
}
