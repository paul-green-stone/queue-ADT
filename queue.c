#include "queue.h"

/* ================================================================ */

static Node* Node_new(const void* data) {
    /*
        * Allocates a container for queue data.
        *
        * Returns a pointer to the container if successful, NULL otherwise.
    */

    Node* node = NULL;

    if (data != NULL) {
        if ((node = (Node*) malloc(sizeof(Node))) != NULL) {
            node->data = (void*) data;
            node->next = NULL;
        }
        else {
            fprintf(stderr, "error: %s\n", strerror(errno));
        }
    }

    return node;
}

/* ================================================================ */

extern Queue* Queue_new(void (*destroy)(void* data)) {
    /*
        * Allocates a new queue.
        * The `destroy` argument provides a way to free queue data when
        * `Queue_destroy` is called.
    */

    Queue* q = NULL;

    if ((q = (Queue*) malloc(sizeof(Queue))) != NULL) {
        q->head = q->tail = NULL;
        q->size = 0;

        q->destroy = destroy;
    }
    else {
        fprintf(stderr, "error: %s\n", strerror(errno));
    }

    return q;
}

/* ================================================================ */

void Queue_destroy(Queue** q) {
    /*
        * Destroys a queue. 
    */

    void* data = NULL;

    if ((q != NULL) && (*q != NULL)) {
        if ((*q)->destroy != NULL) {
            
        }
        while ((*q)->size > 0) {
            /* Free the node */
            data = Queue_dequeue(*q);

            if ((*q)->destroy != NULL) {
                (*q)->destroy(data);
            }
        }
        /* Clear sensitive data */
        memset(*q, 0, sizeof(Queue));
        /* Free a queue */
        free(*q);

        *q = NULL;
    }

    return ;
}

/* ================================================================ */

int Queue_enqueue(Queue* q, const void* data) {
    /* 
        * Enqueues an element at the tail of the queue specified by `q`. 
        * The new element contains a pointer to data, so the memory referenced by data
        * should remain valid as long as the element remains in the queue. 
        * 
        * Returns 1 if enqueuing the element is successful, or 0 otherwise.
    */

    int status_code = 0;
    /* Node to insert */
    Node* node = NULL;

    if (q != NULL) {
        if ((node = Node_new(data)) != NULL) {
            switch (q->size) {
                /* Special case */
                case 0:
                    q->head = q->tail = node;

                    break ;

                default:
                    q->tail->next = node;
                    q->tail = node;

                    break ;
            }

            q->size++;
            status_code = 1;
        }
    }

    return status_code;
}

/* ================================================================ */

void* Queue_dequeue(Queue* q) {
    /*
        * Dequeues an element from the head of the queue specified by queue.
        * Upon return, data points to the data stored in the element that was
        * dequeued.
        * 
        * Returns a pointer to data of the dequeued element if successful, or NULL otherwise.
    */

    void* data = NULL;
    /* Node to be freed */
    Node* node = NULL;

    if (q != NULL) {
        if (q->size > 0) {
            data = q->head->data;
            node = q->head;

            switch (q->size) {
                /* Special case */
                case 1:
                    q->head = q->tail = NULL;

                    break ;

                default:
                    q->head = q->head->next;

                    break ;
            }
            /* Clear sensitive data */
            memset(node, 0, sizeof(Node));
            /* Free a node */
            free(node);

            q->size--;
        }
    }

    return data;
}

/* ================================================================ */

void* Queue_peek(const Queue* q) {
    /*
        * Provides a way to inspect the element at the head of a queue
        * without actually dequeuing it.
    */

    return ( ((q != NULL) && (q->size > 0)) ? q->head->data : NULL );
}

/* ================================================================ */