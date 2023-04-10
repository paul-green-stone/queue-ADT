# Queue

## Content

[About](#about)

[API](#api)

## About

A queue is a data structure that stores and retreives data in a *first-in, first-out*, or *FIFO*, manner. This means that the first element placed in the queue is the first to be removed.

## API

### Queue_new

```C
Queue* Queue_new(void (*destroy)(void* data));
```

The `Queue_new` function dynamically allocates and initializes the queue. The `destroy` argument provides a way to free dynamically allocated data when `Queue_destroy` is called. For a queue containig data that should not be freed, `destroy` should be set to *NULL*.

| Type | Description |
| ---- | ----------- |
| `void (*destroy)(void* data)` | Provides a way to free dynamically allocated data when `Queue_destroy` is called |

Returns a pointer to a queue if memory allocation for it is successful, or *NULL* otherwise.

### Queue_destroy

```C
void Queue_destroy(Queue** q);
```

Destroys the queue. The function takes a pointer to a queue (*actually, it's a pointer to a pointer to a queue*) and destroys it. This means that the function deallocates memory occupied by queue elements if aforementioned `destroy` argument is specified. It deallocates the queue too. Sets a pointer (`*q`) to the queue to *NULL*.

| Type | Description |
| ---- | ----------- |
| `Queue** q` | A pointer to a pointer to a queue to destroy |

Upon return, `*q` becomes *NULL*.

### Queue_enqueue

```C
int Queue_enqueue(Queue* q, const void* data);
```

Enqueues an element at the tail of the queue specified by `q`. The new element contains a pointer to `data`.

| Type | Description |
| ---- | ----------- |
| `Queue* q` | A queue to insert into |
| `const void* data` | Data to insert |

Returns 1 if enqueuing the element is successful, or 0 otherwise.

### Queue_dequeue

```C
void* Queue_dequeue(Queue* q);
```

Dequeues an element from the head of the queue specified by `q`.

| Type | Description |
| ---- | ----------- |
| `Queue* q` | A queue to delete from |

Returns a pointer to deleted data from a queue if dequeuing is successful, or *NULL* otherwise.

### Queue_peek

```C
void* Queue_peek(const Queue* q);
```

Provides a way to inspect the element at the head of a queue without actually dequeuing it.

| Type | Description |
| ---- | ----------- |
| `const Queue* q` | A queue whose element to examine |

### Queue_size

```C
size_t Queue_size(const Queue* q);
```

Macro that evaluates to the number of elements in the queue specified by `q`.
