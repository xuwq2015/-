my_zhuabao : main.c my_types.h network_layer.h network_layer.c link_layer.c link_layer.h protocol_layer.h \
protocol_layer.c
	gcc -g main.c my_types.h network_layer.h network_layer.c link_layer.c link_layer.h -o my_zhuabao protocol_layer.h protocol_layer.c
