//graph class that represents the network
//consists of  all the "people" nodes

#include <iostream>
#include <cstdlib>
#include <unordered_map>
#include <cmath>
#include "node.h"
using namespace std;

class Graph{
  public:
    Graph(int D,int T);
    //process purchase event
    void purchase(string timestamp, int id, double amount);
     //process friend event
    bool befriend(int id1, int id2);
    bool unfriend(int id1, int id2);
    
    //function to find the history statistics given the id of a people node
    void checkStat(int id, double &mean, double&std);

  private:
    //the map to inquire node through id;
    unordered_map<int, Node*> mymap;

    //Depth = D, Length =T
    int Depth;
    int Length;

    // internal processing id for purchases 
    int pID;
};

