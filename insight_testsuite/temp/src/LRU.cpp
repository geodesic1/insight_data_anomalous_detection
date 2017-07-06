/*
 * C++ Program to Implement LRU Cache
 */
#include "LRU.h"
 
// A utility function to create a new Queue Node.
QNode* newQNode(string time, int pID, double purchase)
{
    QNode* temp = new QNode;
    temp->timeStamp = time;
    temp->purchase = purchase;
    temp->pID = pID;
    temp->prev = temp->next = NULL;
    return temp;
}
 
// A utility function to create an empty Queue.
Queue* createQueue(int count)
{
    Queue* queue = new Queue;
    queue->curNumber = 0;
    queue->front = queue->rear = NULL;
    queue->count = count;
    return queue;
}
 
// A utility function to check if queue is empty
int isQueueEmpty( Queue* queue )
{
    return queue->rear == NULL;
}
 
// A utility function to delete a node from queue
void deQueue( Queue* queue )
{
    if (isQueueEmpty(queue))
        return;
    if (queue->front == queue->rear)
        queue->front = NULL;
    QNode* temp = queue->rear;
    queue->rear = queue->rear->prev;
    if (queue->rear)
        queue->rear->next = NULL;
    free(temp);
    queue->curNumber--;
}
 
// A function to add a node at the head of the queue 
void Enqueue(Queue* queue, string time, int pID, double purchase)
{
    //when total number of nodes equals T, delete one node from queue.
    if (queue->curNumber == queue->count)
    {
        deQueue(queue);
    }
    QNode* temp = newQNode(time,pID,purchase);
    temp->next = queue->front;
    if (isQueueEmpty(queue))
        queue->rear = queue->front = temp;
    else
    {
        queue->front->prev = temp;
        queue->front = temp;
    }
    queue->curNumber++;
}

