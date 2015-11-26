#include "./link_layer.h"

void jiexi_mac(u_char *data, int len, struct frame_types *mac_r) {
	uint16_t frame_types;
	
	//获取MAC目的地址
  strncpy(mac_r->daddr, data, 6);
  data += 6;

	//获取MAC源地址
  strncpy(mac_r->saddr, data, 6);
  data += 6;

	//获取上层协议类型或数据段长度
	frame_types = (data[0] << 8) + data[1];

	/* 分辨帧的封装类型 */
	if(frame_types > ETHERNET_II) {	//Ethernet II帧

		mac_r->link_types = ETHERNET_TYPES;
		mac_r->network_types = frame_types;
		data += 2;
		strncpy(mac_r->data, data, len - 18);
		mac_r->network_len = len - 18;

	} esle {

		data += 2;
		uint16_t sap;
		sap = (data[0] << 8) + data[1];

		if(sap == NOVELL_ETHER) {	//Novell Ether帧

			mac_r->link_types = NOVELL_TYPES;
			mac_r->netwok_len = frame_types;
			mac_r->network_types = 0;

			data += 2;
			strncpy(mac_r->data, data, mac_r->network_len);

		} else if(sap == ETHERNET_SNAP) {	//Ethernet SNAP帧

			mac_r->link_types = SNAP_TYPES;
			mac_r->network_len = frame_types;
			mac_r->network_types = (data[6] << 8) + data[7];

			data += 8;
			strncpy(mac_r->data, data, mac_r->network_len);

		} else {	//802.3/802.2格式的帧

			mac_r->link_types = IEEE_TYPES;
			mac_r->network_len = frame_types;
			mac_r->network_types = 0;

			data += 3;
			strncpy(mac_r->data, data, mac_r->network_len);
		}
	}
}
