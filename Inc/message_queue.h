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
} MessageQueue;

MessageQueue* constructMessage(void);
bool enQueue(MessageQueue*, uint8_t);
bool deQueue(MessageQueue*, uint8_t*);
bool isEmpty(MessageQueue*);
bool isFull(MessageQueue*);
uint8_t peek(MessageQueue*);
int nextRear(MessageQueue*);
int nextFront(MessageQueue*);

#endif
