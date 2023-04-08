#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* ================================================================ */

typedef struct _node {
    void* data;

    struct _node* next;
} Node;

typedef struct _queue {
    Node* head;
    Node* tail;

    size_t size;

    void (*destroy)(void* data);
} Queue;

#define Queue_size(q) ((q != NULL) ? q->size : -1)

/* ================================================================ */

/*
    * Allocates memory for a queue
*/
extern Queue* Queue_new(void (*destroy)(void* data));

/* 
    * Destroys the queue
*/
extern void Queue_destroy(Queue** q);

/*
    * Enqueues an element at the tail of the queue
*/
extern int Queue_enqueue(Queue* q, const void* data);

/* 
    * Dequeues an element from the head of the queue
*/
extern void* Queue_dequeue(Queue* q);

/*
    * Provides a way to inspect the element at the head of a queue.
*/
extern void* Queue_peek(const Queue* q);

#endif