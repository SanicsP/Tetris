#ifndef INCLUDE_INT_QUEUE_H
#define INCLUDE_INT_QUEUE_H

#define INT_QUEUE_CAPACITY 3
#include <inttypes.h>
#include <assert.h>

typedef struct intqueue_s {
    size_t capacity;
    size_t size;
    int data[INT_QUEUE_CAPACITY];

} IntQueue;

IntQueue IntQueue_new(const size_t init_size);

int IntQueue_enqueue(IntQueue* queue , const int new_value);

int IntQueue_dequeue(IntQueue* queue);

int IntQueue_front(IntQueue* queue);

int IntQueue_is_full(IntQueue* queue);

int IntQueue_is_empty(IntQueue* queue);





#endif 