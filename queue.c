#include "queue.h"

/* ================================ */

struct _queue_node {
    Data data;

    struct _queue_node* next;
};

struct _queue {
    Node head;
    Node tail;

    ssize_t size;

    void (*fptr_destroy)(Data data);
    void (*fptr_print)(Data data);
};

/* ================================================================ */

static Node Node_new(const Data data) {
    Node node = NULL;

    if (data != NULL) {
        if ((node = (Node) malloc(sizeof(struct _queue_node))) != NULL) {
            node->data = (Data) data;
            node->next = NULL;
        }
        else {
            warn_with_sys_msg("Memory allocation failure");
        }
    }
    else {
        warn_with_user_msg(__func__, "data can't be NULL");
    }

    return node;
}

static Data Node_destroy(Node* node) {
    Data data = NULL;

    if ((node != NULL) && (*node != NULL)) {
        data = (*node)->data;
        (*node)->next = NULL;

        /* Clear memory*/
        memset(*node, 0, sizeof(struct _queue_node));
        /* Deallocate memory */
        free(*node);

        *node = NULL;
    }

    return data;
}

/* ================================================================ */

Queue Queue_new(void (*fptr_destroy)(Data data), void (*fptr_print)(Data data)) {
    Queue queue = NULL;

    if ((queue = (Queue) malloc(sizeof(struct _queue))) != NULL) {
        queue->size = 0;
        queue->head = queue->tail = NULL;

        queue->fptr_destroy = fptr_destroy;
        queue->fptr_print = fptr_print;
    }
    else {
        warn_with_user_msg(__func__, "data can't be NULL");
    }

    return queue;
}

/* ================================ */

void Queue_print(const Queue queue, void (*fptr_print)(const Data)) {
    void (*alt_fptr_print)(const Data) = NULL;

    if (queue != NULL) {
        if ((queue->fptr_print == NULL) && (fptr_print == NULL)) {
            warn_with_user_msg(__func__, "there is no associated `print` function with the list");

            return ;
        }

        printf("[");

        if (queue->size > 0) {
            alt_fptr_print = (queue->fptr_print == NULL) ? fptr_print : queue->fptr_print;

            for (Node node = queue->head; node != NULL; node = node->next) {
                alt_fptr_print(node->data);

                if (node->next != NULL) {
                    printf(" -> ");
                }
            }
        }

        printf("]\n");
    }
    else {
        warn_with_user_msg(__func__, "stack can't be NULL");
    }

    return ;
}

/* ================================ */

void Queue_destroy(Queue* queue) {
    Data data = NULL;

    if ((queue != NULL) && (*queue) != NULL) {
        while ((*queue)->size > 0) {
            data = Queue_dequeue(*queue);

            if ((*queue)->fptr_destroy != NULL) {
                (*queue)->fptr_destroy(data);
            }
        }

        /* Clear memory */
        memset(*queue, 0, sizeof(struct _queue));
        /* Dealloce memory */
        free(*queue);

        *queue = NULL;
    }
    else {
        warn_with_user_msg(__func__, "*queue can't be NULL");
    }

    return ;
}

/* ================================ */

int8_t Queue_enqueue(Queue queue, const Data data) {
    int8_t result = 0;
    Node node = NULL;

    if (queue != NULL) {
        if ((node = Node_new(data)) != NULL) {
            switch (queue->size) {
                case 0:
                    queue->tail = queue->head = node;

                    break ;

                default:
                    queue->tail->next = node;
                    queue->tail = node;

                    break ;
            }

            queue->size++;
            result = 1;
        }
    }
    else {
        warn_with_user_msg(__func__, "queue can't be NULL");
    }

    return result;
}

/* ================================ */

Data Queue_dequeue(Queue queue) {
    Node node = NULL;
    Data data = NULL;

    if (queue != NULL) {
        if (queue->size > 0) {
            node = queue->head;

            switch (queue->size) {
                case 1:
                    queue->head = queue->tail = NULL;

                    break ;

                default:
                    queue->head = node->next;

                    break ;
            }

            data = Node_destroy(&node);
        }

        queue->size--;
    }
    else {
        warn_with_user_msg(__func__, "queue can't be NULL");
    }

    return data;
}

/* ================================ */

ssize_t Queue_get_size(const Queue queue) {
    return (queue != NULL) ? queue->size : -1;
}

/* ================================ */

Data Queue_peek(const Queue queue) {
    Data data = NULL;

    if (queue != NULL) {
        if (queue->size > 0) {
            data = queue->head->data;
        }
    }
    else {
        warn_with_user_msg(__func__, "queue can't be NULL");
    }

    return data;
}