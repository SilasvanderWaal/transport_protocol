#include "Sim_Engine.h"
#include "queue.h"
#include <stdbool.h>
#include <string.h>

#define A                                                                      \
	0 // Could we use the constatns in defined in sim_engine.c instead? Maybe
	  // move them to the header file.
#define B			 1
#define PAYLOAD_SIZE 20
#define TIMEOUT		 30.0

/* Global variables*/
struct queue qt;

/*
==============================================================
				Private functions
==============================================================
*/

/* Send oldest package */
void send_packet(bool is_resend) {
	if (is_empty(&qt) || (qt.wait && !is_resend))
		return;
	struct pkt sndpkt = peek(&qt);
	starttimer(A, TIMEOUT);
	qt.wait = true;
	tolayer3(A, sndpkt);
}

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

/*
==============================================================
				Public functions
==============================================================
*/

/* Called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message) {
	struct pkt new_pkt;
	strcpy(new_pkt.payload, message.data);
	new_pkt.checksum = calc_checksum(new_pkt);
	enqueue(&qt, new_pkt);
	send_packet(false);
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {
	if (packet.acknum != peek(&qt).seqnum || !validate_packet(packet)) {
		return;
	}
	stoptimer(A);
	dequeue(&qt);
	qt.wait = false;
	send_packet(false);
}

/* Called when A's timer goes off */
void A_timerinterrupt() { send_packet(true); }

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init() {
	qt.next_seq = 0;
	qt.wait		= false;
	qt.front	= 0;
	qt.back		= 0;
}
