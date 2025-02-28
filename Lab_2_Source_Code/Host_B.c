#include "Sim_Engine.h"
#define B 1

/* Called from layer 5, passed the data to be sent to other side */
void B_output(struct msg message)
{
  /* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet)
{
  tolayer5(B, packet.payload);
  //  Validate packet
  packet.acknum = packet.seqnum;
  tolayer3(B, packet);
}

/* Called when B's timer goes off */
void B_timerinterrupt()
{
  /* TODO */
}

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init()
{
  /* TODO */
}
