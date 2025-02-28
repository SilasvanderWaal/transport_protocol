#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "Sim_Engine.h"

#define QUEUE_SIZE 128

struct queue {
	unsigned int front;
	unsigned int back;
	struct pkt	 queue[QUEUE_SIZE];
	bool		 next_seq;
	bool		 wait;
};

int enqueue(struct queue *q, struct pkt p);

int dequeue(struct queue *q);

struct pkt peek(struct queue *q);

bool is_full(struct queue *q);

bool is_empty(struct queue *q);
