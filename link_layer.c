#include "./link_layer.h"

u_char *jiexi_mac(u_char *data, int len, struct mac_tou *mac_r) {
	uint8_t frame_types;

	frame_types = (data[12] << 8) + data[13];
	
  u_char *ip_data;
  strncpy(mac_r->daddr, data, 6);
  data += 6;
  strncpy(mac_r->saddr, data, 6);
  data += 6;

  mac_r->types = (data[0] << 8) + data[1];
  data += 2;
  ip_data = data;
  data[len - 14 - 5] = '\0';
  return ip_data;
}
