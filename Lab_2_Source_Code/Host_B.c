#include "Sim_Engine.h"
#include <stdbool.h>

#include "helper.h"

#define B 1

bool bit;

/* Called from layer 5, passed the data to be sent to other side */
void B_output(struct msg message) { /* DON'T IMPLEMENT */ }

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet) {

	if ((packet.checksum != calc_checksum(packet))) {
		return;
	}

	if (packet.seqnum == bit) {
		bit = !bit;
		tolayer5(B, packet.payload);
		return;
	}

	//  Validate packet
	int tmp		  = packet.seqnum;
	packet.seqnum = packet.acknum;
	packet.acknum = tmp;

	packet.checksum = calc_checksum(packet);

	tolayer3(B, packet);
}

/* Called when B's timer goes off */
void B_timerinterrupt() { /* TODO */ }

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init() { bit = 0; }
