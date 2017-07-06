/*declaration of a "people" node:

1.LRU cache in LRU.h&LRU.cpp is used to generate its own purchase history;

2.each node use the unorderd map to contain the neighbors;

3.node class also contains the funtion to look up its current neighbors and find the top T most recent purchases for mean and std calculation.
*/ 

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "LRU.h"
using namespace std;

// A Queue Node (Queue is implemented using Doubly Linked List)
class Node
{
    public:
       //constructor: x-id, y-Tracked number of purchases;
       Node(int x, int y);
       //connect to friend node;
       bool connect(int id, Node* nei);
       //unconnect to friend node;
       bool deConnect(int id);
       //add purchase event to LRU cache
       void insertQueue(string timestamp, int pID, double amount);
      
       //get the most recent purchase
       QNode* getLatest();

       int getId();

       double getMean();

       double getStd();

       //given D, find the candidate neighboring nodes.
       void findCan(Node *cur, unordered_set<Node*> &base, int depth);
       
       //given D and T, find the statistics.
       void calStat(int Depth, int Length);

       //comparator to sort out the most recent purchase node

    private:
       //unique id
       int id;
      
       double mean;

       double std;
       //access neighboring nodes through id;
       unordered_map<int, Node*> neighbors;
       //its own purchase history
       Queue* myqueue;
};
