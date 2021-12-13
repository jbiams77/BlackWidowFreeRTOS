#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H


#include "stm32f1xx_utility.h"

#define HAL_BUFFER_SIZE 255

/* the HEAD of the MessageQueue, hold the amount of node's that are in the queue*/
typedef struct MessageQueue { 
    uint8_t fifo[HAL_BUFFER_SIZE];
    uint8_t SIZE;
    int front; 
    int rear;
    bool messageRdy;
} MessageQueue;

MessageQueue* constructMessage(void);

// Put a byte in
bool enQueue(MessageQueue*, uint8_t);

// Take a byte out
bool deQueue(MessageQueue*, uint8_t*);
bool isEmpty(MessageQueue*);
bool isFull(MessageQueue*);
uint8_t peek(MessageQueue*);
int nextRear(MessageQueue*);
int nextFront(MessageQueue*);

// For now, lets let flush just remove the entire queue
// Later on we need to handle multiple messages
void flush(MessageQueue *);

#endif
