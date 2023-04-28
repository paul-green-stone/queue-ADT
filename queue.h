#ifndef QUEUE_H
#define QUEUE_H

/* ================================================================ */

#include "data.h"
#include "guard/guard.h"

typedef struct _queue_node* Node;       /* A pointer to an incomplite type */

typedef struct _queue* Queue;           /* A pointer to an incomplite type */

/* ================================ */

/* Allocate a new instance of a queue data structure */
extern Queue Queue_new(void (*fptr_destroy)(Data data), void (*fptr_print)(Data data));

/* Print the content of a queue */
extern void Queue_print(const Queue queue, void (*fptr_print)(const Data));

/* Deallocate memory occupied by the queue */
extern void Queue_destroy(Queue* queue);

/* Enqueue an element at the tail of the queue */
extern int8_t Queue_enqueue(Queue queue, const Data data);

/* Dequeue an element from the head of the queue */
extern Data Queue_dequeue(Queue queue);

/* Peek data at the head of the queue */
extern Data Queue_peek(const Queue queue);

/* Get the size of the queue */
extern ssize_t Queue_get_size(const Queue queue);

/* ================================================================ */

#endif