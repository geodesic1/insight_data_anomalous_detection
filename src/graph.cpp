#include "graph.h"

Graph::Graph(int D, int T){
   Depth = D;
   Length = T;
   pID = 0;
}

//function to process purchase event
void Graph::purchase(string timestamp, int id, double amount){
    Node* tmp;
    //find people Node by the id, if cannot find one, creat a new node;
    if(mymap.find(id) == mymap.end()){
       tmp = new Node(id, Length);
       mymap.insert(make_pair(id, tmp));
     }
     else{
       tmp = mymap[id];
     }
     tmp -> insertQueue(timestamp, pID, amount);

     pID++;
}

//connect two people given their id
bool Graph::befriend(int id1, int id2){
    if(mymap.find(id1) == mymap.end()){
       Node* tmp = new Node(id1, Length);
       mymap.insert(make_pair(id1, tmp));
     }
    if(mymap.find(id2) == mymap.end()){
       Node* tmp = new Node(id2, Length);
       mymap.insert(make_pair(id2, tmp));
     }
    // update both nodes friend list
    return mymap[id1]->connect(id2, mymap[id2]) && mymap[id2]->connect(id1, mymap[id1]);
}

//deconnect two people given their id
bool Graph::unfriend(int id1, int id2){
    if(mymap.find(id1) == mymap.end()||mymap.find(id2) == mymap.end())return false;
    //remove both nodes from each other's friend list
    return mymap[id1]->deConnect(id2) && mymap[id2]->deConnect(id1);
}

//get the statistics given the id of this people
void Graph::checkStat( int id, double &mean, double &std){
    //if this is a new node return default statistics 
    if(mymap.find(id) == mymap.end()){
        mean = 0.0;
        std = -1.0;
        return;
     }
     else{
       mymap[id] -> calStat(Depth, Length);
       mean = mymap[id] -> getMean();
       std = mymap[id] -> getStd();
     }
}

