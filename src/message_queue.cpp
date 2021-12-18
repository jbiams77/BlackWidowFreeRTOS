#include "message_queue.h"


MessageQueue* constructMessage(void) {
    MessageQueue *queue = (MessageQueue*) malloc(sizeof (MessageQueue)); 
    int i;
    queue->SIZE = HAL_BUFFER_SIZE;
    queue->front = -1;
    queue->rear = 0;
    queue->messageRdy = false;
    for (i=0; i<queue->SIZE; i++){
        queue->fifo[i] = 0;    
    }
    return queue;
}


bool enQueue(MessageQueue *queue, uint8_t data){
    if(isFull(queue)){
        return false;
    } else if(isEmpty(queue)){
        queue->front = queue->rear;
        queue->fifo[queue->rear] = data;
        return true;
    } else {
        queue->rear = nextRear(queue);
        queue->fifo[queue->rear] = data;
        return true;
    }
}


bool deQueue(MessageQueue *queue, uint8_t *byte){
    if(isEmpty(queue)) {
        // Empty queue, return false
        return false;
    } else if (queue->front == queue->rear) {
        // Last message in the queue, reset front to -1
        *byte = queue->fifo[queue->front];
        queue->front = -1;
        return true;
    } else {
        // Get message out and go next front
        *byte = queue->fifo[queue->front];
        queue->front = nextFront(queue);
        return true;
    }
}

uint8_t peek(MessageQueue *queue){
    return queue->fifo[queue->front];
}

bool isEmpty(MessageQueue *queue){
    if(queue->front == -1){
        return true;    
    }
    return false;
}

bool isFull(MessageQueue *queue){
    if(nextRear(queue)==queue->front){
        return true;
    }
    return false;
}

int nextRear(MessageQueue *queue){
    return (queue->rear + 1) % queue->SIZE;
}

int nextFront(MessageQueue *queue){
    return (queue->front + 1) % queue->SIZE;
}

void flush(MessageQueue *queue){
    queue->front = -1;
    queue->rear = 0;
}