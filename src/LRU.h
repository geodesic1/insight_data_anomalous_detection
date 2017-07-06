/* implementation of least recent use cache using doubly linked list;
only keep T numbers of most recent purchases for each person
 */
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

// A Queue Node that contain purchase 
typedef struct QNode
{
    QNode *prev, *next;
    string timeStamp;
   //pID store the internal order to process purchase because timeStamp can be the same
    int pID;
    double purchase;
} QNode;

// A Queue (A FIFO collection of Queue Nodes:doubly linked list)
typedef struct Queue
{
    // count is set to T because maximum number of T is needed
    int count;
    // number of current nodes 
    int curNumber;
    // head and tail of doubly linked list 
    QNode *front, *rear;
}Queue;

// A utility function to create a new Queue Node.
QNode* newQNode(string time, int pID, double purchase);

Queue* createQueue(int count);

int isQueueEmpty( Queue* queue );

//remove last node at the tail when size equal to T;
void deQueue( Queue* queue );

// create a new QNode for purchase event at the head of the queue; 
void Enqueue(Queue* queue, string time, int pID, double purchase);
