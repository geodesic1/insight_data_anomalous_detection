#include <iostream>
#include <fstream> 
#include <iomanip>   
#include "graph.h"
//using jsoncpp to parse json input
#include "json/json.h"
using namespace std;

//parse string as int
bool parseAsInt(Json::Value input, int & value){
    string tmp = input.asString();
    return  value = atoi(tmp.c_str());    
}
    
//parse string as decimal
bool parseAsDecimal(Json::Value input, double & value){
    string tmp = input.asString();
    return value = atof(tmp.c_str());
}

//update graph object based on json input
bool excute(Graph* cur, Json::Value input){

     string timestamp;
     string event_type = input["event_type"].asString();

     //select the graph operation based on event type
     if( event_type == "purchase"){
        int id;
        double amount;
	timestamp = input["timestamp"].asString();
        parseAsInt(input["id"], id);
        parseAsDecimal(input["amount"], amount);
        cur -> purchase(timestamp, id, amount);
        return true;
     }
     else if( event_type == "befriend"){
        int id1, id2;
        parseAsInt(input["id1"], id1);
        parseAsInt(input["id2"], id2);
        return cur -> befriend(id1, id2);
     }
     else if (event_type == "unfriend"){
        int id1, id2;
        parseAsInt(input["id1"], id1);
        parseAsInt(input["id2"], id2);
        return cur -> unfriend(id1, id2);
     }
     else return false;
}


//main function to process data from log input
int main() {

    Json::Reader reader;
    Json::Value obj;

    //parameter of D,T 
    int Depth, Tracked ;
    //a single line of input
    string cur_line;

    int id;
    double amount;

    double mean, std;

    //open input and target files
    ifstream infile( "../log_input/batch_log.json" );
    ifstream infile2( "../log_input/stream_log.json" );
    ofstream outfile;
    outfile.open("../log_output/flagged_purchases.json");

    //process batch_log.json
    if(!getline(infile, cur_line))return 0;

    reader.parse(cur_line, obj); 
    parseAsInt(obj["D"], Depth); 
    parseAsInt(obj["T"], Tracked); 
    
    Graph* newGraph = new Graph(Depth,Tracked);

    while(getline(infile, cur_line)){
        reader.parse(cur_line, obj);
        excute(newGraph, obj);
    } 
    infile.close();

    //set output format  to two precision
    outfile << std::fixed;
    outfile << std::setprecision(2);

    //process stream_log.json
    while(getline(infile2, cur_line)){

        reader.parse(cur_line, obj);

        if(obj["event_type"].asString() == "purchase"){ 
	   //get history statistics for purchase events
	    parseAsInt(obj["id"],id);
            parseAsDecimal(obj["amount"],amount);
            newGraph->checkStat(id, mean, std);
           
            //write to output file if this is anomalous purchase 
            if(std > 0 && amount > mean + 3 * std){
                cur_line = cur_line.substr(0, cur_line.size()-1);
	        outfile<<cur_line<<", \"mean\": \""<<mean;
                outfile<<"\", \"sd\": \"" <<std<<"\"}"<<endl;
            }

        }
        //update the gragh history
        excute(newGraph,obj);
    }

    infile2.close();
    outfile.close();
    return 0;
}
