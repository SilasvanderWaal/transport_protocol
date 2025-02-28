#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "Sim_Engine.h"

#define QUEUE_SIZE 20

struct queue {
	unsigned int front;
	unsigned int back;
	struct pkt	 queue[QUEUE_SIZE];
	bool		 active_seq;
};

int enqueue(struct queue *q, struct pkt p);

int dequeue(struct queue *q);

void peek(struct queue *q, struct pkt *p);

bool is_full(struct queue *q);

bool is_empty(struct queue *q);
