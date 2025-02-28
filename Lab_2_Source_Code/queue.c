#include "queue.h"

int q_front(struct queue *q) { return q->front % QUEUE_SIZE; }
int q_back(struct queue *q) { return q->back % QUEUE_SIZE; }

int enqueue(struct queue *q, struct pkt p) {
	if (is_full(q)) {
		return -1;
	}

	q->queue[q_back(q)] = p;
	q->back++;

	return 1;
}

int dequeue(struct queue *q) {
	if (is_empty(q)) {
		return -1;
	}

	q->front++;

	return 1;
}

void peek(struct queue *q, struct pkt *p) { *p = q->queue[q_front(q)]; }

bool is_full(struct queue *q) { return q_back(q) + 1 == q_front(q); }

bool is_empty(struct queue *q) { return q_front(q) + 1 == q_back(q); }
