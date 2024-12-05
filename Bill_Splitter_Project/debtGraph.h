#ifndef DEBTGRAPH_H
#define DEBTGRAPH_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <list>
#include <vector>

using namespace std;

class Graph{
private:
    //holds key and value of vector of pairs
    unordered_map<string, vector<pair<string, double>>> graph;
public:
    Graph(){
        //nothing
    }
    void addDebtEdge(string& from, string& to, double amount){
        graph[from].emplace_back(to, amount);
    }

};

#endif // DEBTGRAPH_H
