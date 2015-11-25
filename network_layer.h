#ifndef NETWORK_LAYER_H
#define NETWORK_LAYER_H

#include <string.h>
#include "./my_types.h"

u_char *jiexi_ipv4(u_char *data, struct ip_v4 *ip_r);

void jiexi_ipv6(u_char *data, struct ip_v6 *ip_r);

#endif	//NETWORK_LAYER_H
