#include "Sim_Engine.h"

#include <stdbool.h>
#include <string.h>

#include "helper.h"
#include "queue.h"

#define A                                                                      \
	0 // Could we use the constatns in defined in sim_engine.c instead? Maybe
	  // move them to the header file.
#define B 1

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
	// printf("seq: %d | ack: %d\n", sndpkt.seqnum, sndpkt.acknum);
	tolayer3(A, sndpkt);
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
	new_pkt.seqnum	 = qt.next_seq;
	new_pkt.acknum	 = 0;
	new_pkt.checksum = calc_checksum(new_pkt);
	enqueue(&qt, new_pkt);
	send_packet(false);
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {
	if (!validate_packet(packet)) {
		return;
	}

	if (packet.acknum == peek(&qt).seqnum) {
		dequeue(&qt);
		qt.wait = false;
		stoptimer(A);
		send_packet(false);
	}
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
