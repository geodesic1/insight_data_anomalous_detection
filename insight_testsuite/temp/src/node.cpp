#include "node.h"
struct compare {
    bool operator()(const QNode* l, const QNode* r) {
     //sort by internal sequence of pruchase event creation
        return l->pID < r->pID;
    }
};


Node::Node(int x, int y){
   id = x;
   //y is the input T:maximum tracked number of purchases
   myqueue = createQueue(y);
   //default: set standard deviation to negative
   mean = 0.0;
   std = -1.0;
   
}

//add friends to nodes
//return boolean is not used, but is can be extended in the future to check invalid inputs
bool Node::connect(int id, Node* nei){

     if(neighbors.find(id) != neighbors.end())return false;

     neighbors.insert(make_pair(id, nei));

     return true;
}

//delete friends
bool Node::deConnect(int id){

     if(neighbors.find(id) == neighbors.end())return false;

     neighbors.erase(id);

     return true;
}

//add its own purchase event for each node
void Node::insertQueue(string timestamp, int pID, double amount){

    Enqueue(myqueue, timestamp, pID, amount);

}

//get most recent purchse for each node
QNode* Node::getLatest(){
    
    return myqueue->front;

}

int Node::getId(){
    
    return id;

}

double Node::getMean(){
    return mean;
}

double Node::getStd(){
    return std;
}


//call iteratively to find all candidate friend node given T
//using unordered_set to check whether a node is visited
void Node::findCan(Node* cur, unordered_set<Node*> & base, int depth){

   if(depth == 0) return;

   for(auto s : cur->neighbors){

      if(base.find(s.second) == base.end()){

         base.insert(s.second);

         findCan(s.second, base, depth - 1);
      }

   }
}

//calculate the mean and standard deviation given D and T
void Node::calStat(int Depth, int Length){

    //using heap structure to compare the purchases in multiple doubly linked list (LRU) from friend nodes
    priority_queue< QNode*, vector<QNode*>, compare> q;

    unordered_set<Node*> base;

    int size = 1;

    double sqsum = 0.0;

    //find all candidate friend nodes given T
    for(auto s: neighbors){
       base.insert(s.second);
       findCan(s.second, base, Depth-1);
    }

    //base contains all the candidate neibouring nodes;
    //add purchase nodes from all candidate friend nodes into the heap;
    for(auto s : base){
      if(s -> getLatest()) {
        q.push(s -> getLatest());
      }
    }
    if( q.empty() ){
        return;
    }

    mean = 0.0;
    std = -1.0;

    QNode* tmp = q.top();
    q.pop();
    if(tmp -> next) q.push(tmp -> next);

    mean += tmp->purchase;
    //keep the squared sum of purchases to calculate std one pass
    sqsum += tmp ->purchase * tmp->purchase;

    //continue updates the sum until size equals the maximum
    while(!q.empty() && size < Length){

       tmp = q.top();
       q.pop();
       if(tmp->next) q.push(tmp->next);
       mean += tmp->purchase;
       sqsum += tmp ->purchase * tmp->purchase;

       ++size;
    }
    //only update statistics if there are at least 2 purchases
    if(size >= 2){
       mean = mean / size;
       std = sqrt(sqsum / size - mean * mean);
    }

    base.clear(); 
}


