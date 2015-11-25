#include "./network_layer.h"

u_char *jiexi_ipv4(u_char *data, struct ip_v4 *ip_r) {
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

void jiexi_ipv6(u_char *data, struct ip_v6 *ip_r) {
  uint32_t buffer;
  ip_r->version = (data[0] & 0xF0) >> 4;
  ip_r->traffic_class = ((data[0] & 0x0f) << 4) + ((data[1] & 0xf0) >> 4);
  ip_r->flow_label = data[3] + (data[2] << 8) + ((data[1] & 0x0f) << 16);
  ip_r->payload_length = (data[4] << 8) + data[5];
  ip_r->next_header = data[6];
  ip_r->hop_limit = data[7];
  data += 8;
  strncpy(ip_r->source_addr, data, 16);
  data += 16;
  strncpy(ip_r->destination_addr, data, 16);
}
