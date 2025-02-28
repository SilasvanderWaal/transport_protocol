#include "queue.h"

int q_front(struct queue *q) { return q->front % QUEUE_SIZE; }
int q_back(struct queue *q) { return q->back % QUEUE_SIZE; }

int enqueue(struct queue *q, struct pkt p) {
	if (is_full(q)) {
		printf("Queue is full! Dropping message from layer 5. \n");
		return -1;
	}

	q->queue[q_back(q)] = p;
	q->back++;
	q->next_seq = !q->next_seq;

	return 1;
}

int dequeue(struct queue *q) {
	if (is_empty(q)) {
		return -1;
	}

	q->front++;

	return 1;
}

struct pkt peek(struct queue *q) { return q->queue[q_front(q)]; }

bool is_full(struct queue *q) { return q_back(q) + 1 == q_front(q); }

bool is_empty(struct queue *q) { return q_front(q) == q_back(q); }
