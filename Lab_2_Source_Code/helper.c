#include "helper.h"

int calc_checksum(struct pkt packet) {
	int sum = 0;
	sum += packet.acknum;
	sum += packet.seqnum;
	for (size_t i = 0; i < PAYLOAD_SIZE; i++) {
		sum += packet.payload[i];
	}
	return sum;
}

bool validate_packet(struct pkt packet) {
	return packet.checksum == calc_checksum(packet);
}
