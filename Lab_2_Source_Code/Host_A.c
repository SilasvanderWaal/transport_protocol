#include "Sim_Engine.h"
#include <stdbool.h>
#include <string.h>

#define A                                                                      \
	0 // Could we use the constatns in defined in sim_engine.c instead? Maybe
	  // move them to the header file.
#define B			 1
#define PAYLOAD_SIZE 20
#define RTT			 15.0
#define TIMEOUT		 30.0

/* Global variables*/
struct pkt active_pkt;

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

/*We are going to need some type of queue system for the packages created from
 * the data that is recieved from layer 5*/

/* Called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message) {
	memcpy(active_pkt.payload, message.data, sizeof(message.data));
	active_pkt.checksum = calc_checksum(active_pkt);
	starttimer(A, TIMEOUT); // Not sure about the increment argument, think it
							// sets the TIMEOUT interval
	tolayer3(A, active_pkt);
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet) {
	if (packet.acknum != active_pkt.seqnum ||
		packet.checksum != calc_checksum(packet)) {
		return;
	}
	stoptimer(A);
	active_pkt.seqnum = ++active_pkt.seqnum % 1;
}

/* Called when A's timer goes off */
void A_timerinterrupt() {
	starttimer(A, TIMEOUT);
	tolayer3(A, active_pkt);
}

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init() { active_pkt.seqnum = 0; }
