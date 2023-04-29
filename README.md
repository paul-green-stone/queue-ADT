# Queue

## Content

[About](#about)

[API](#api)

[Examples](#examples)

[Resources](#resources)

## About

Queue is an efficient data structures useful for storing and retrieving data in a first-in, first-out, or FIFO, order. This allows us to retrieve data in the same order as it was stored.

The `Queue` is a pointer to an incomplete type,

```C
typedef struct _queue* Queue;
```

which means users are only allowed to work with queues through the use of specified functions (e.g., interfaces, the **first-class ADT pattern**).

## API

### Queue_new

```C
Queue Queue_new(void (*fptr_destroy)(Data data), void (*fptr_print)(Data data));
```

The `Queue_new` function allocates a new instance of a queue data type.

| Type | Description |
| ---- | ----------- |
| `void (*fptr_destroy)(void*)` | Provides a way to free dynamically allocated data when `Queue_destroy` is called. If the queue contains data dynamically allocated using `malloc`, `fptr_destroy` should be set to `free` to free the data as the queue is destroyed. For structured data containing several dynamically allocated members, destroy should be set to a user-defined function that calls `free` for each dynamically allocated member as well as for the structure itself. For a queue containing data that should not be freed, destroy should be set to *NULL* |
| `void (*fptr_print)(const Data)` | Provides a default way to display content of the queue when `Queue_display` is invoked. [How to write `print` functions](#how-to-write-print-functions) |

**Return value**: `Queue` if creating a new queue is successful, or `NULL` otherwise.

### Queue_print

```C
void Queue_print(const Queue queue, void (*fptr_print)(const Data));
```

The `Queue_print` function outputs content of the queue. The `fptr_print` argument is a callback function that is called on every node while traversng the queue. If `fptr_print` is NULL, the `fptr_print` function specified in `Queue_new` is used.

| Type | Description |
| ---- | ----------- |
| `const Queue queue` | The queue to be displayed |
| `void (*fptr_print)(const Data)` | The callback function to print data in a node |

**Return value**: None

### Queue_destroy

```C
void Queue_destroy(Queue* queue);
```

The `Queue_destroy` operation destroys a queue. The function takes a pointer to a queue (*actually, it's a pointer to a pointer to a queue*) and destroys it. This means that the function deallocates memory occupied by queue elements if aforementioned `fptr_destroy` argument is specified. It deallocates the queue too. Sets a pointer (`*queue`) to the queue to *NULL*.

| Type | Description |
| ---- | ----------- |
| `Queue* queue` | A pointer to a queue to be destroyed |

**Return value**: None

### Queue_enqueue

```C
int8_t Queue_enqueue(Queue queue, const Data data);
```

The `Queue_enqueue` operation enqueues an element at the tail of a queue.

| Type | Description |
| ---- | ----------- |
| `Queue queue` | A queue to enqueue an element into |
| `Data data` | Data to insert |

**Return value**: 1 if enqueueing the element is successful, or 0 otherwise.

### Queue_dequeue

```C
Data Queue_dequeue(Queue queue);
```

The `Queue_dequeue` operation dequeues an element from the head of a queue.

| Type | Description |
| ---- | ----------- |
| `Queue queue` | A queue to dequeue from |

**Return value**: `Data` if a queue is not empty, or `NULL` otherwise.

### Queue_peek

```C
Data Queue_peek(const Queue queue)
```

Provides a way to inspect the element at the head of a queue without actually dequeuing it.

| Type | Description |
| ---- | ----------- |
| `const Queue queue` | A queue whose element to examine |

### Queue_size

```C
size_t Queue_size(const Queue* q);
```

The `Queue_size` operation returns the size of the queue.

| Type | Description |
| ---- | ----------- |
| `const Queue queue` | A queue which size to get |

**Return value**: number of elements in the queue, or -1 if queue is `NULL`.

## Examples

### How to write `print` functions

The `fptr_print` argument in the `Queue_print` and `Queue_new` functions is a callback that handles data in a queue node.

One must assume that a queue is homogeneous (e.g., contains data of the same type). For example, suppose we have a queue of integers, then we might write the function:

```C
/* ... */
void print_int(Data data) {
    printf("%d", *((int*) data));
}
```

Keep in mind that `fptr_print` expects its argument to be a type of `Data`.

## Resources

[Mastering Algorithms with C](https://www.amazon.com/Mastering-Algorithms-Techniques-Sorting-Encryption/dp/1565924533/ref=sr_1_1?crid=1ZN4ENEQEGO5&keywords=mastering+c+algorithms&qid=1679619546&s=books&sprefix=mastering+c+algoritms%2Cstripbooks-intl-ship%2C221&sr=1-1) by Kyle Loudon.

[Data Structures, Algorithms, and Software Principles in C](https://www.amazon.com/Data-Structures-Algorithms-Software-Principles/dp/0201591189/ref=sr_1_10?crid=14MCGWUKW0F98&keywords=data+structures+and+algorithms+in+C&qid=1679784448&s=books&sprefix=data+structures+and+algorithms+in+c%2Cstripbooks-intl-ship%2C186&sr=1-10) by Thomas Standish.

[Computer Systems: A Programmer's Perspective](https://www.amazon.com/Computer-Systems-Programmers-Randal-Bryant/dp/013034074X/ref=sr_1_3?crid=1NDI8BHE4BPQM&keywords=computer+systems+a+programmer%27s+perspective&qid=1679784732&s=books&sprefix=computer+pers%2Cstripbooks-intl-ship%2C199&sr=1-3) by Randal E. Bryant, David Richard O'Hallaron.

[Patterns in C](https://leanpub.com/patternsinc) by Adam Tornhill
