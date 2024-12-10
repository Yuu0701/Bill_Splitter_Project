#ifndef DEBTGRAPH_H
#define DEBTGRAPH_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <list>
#include <stack>
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
        for (auto& [receiver, debt] : graph[from]){
            if (receiver == to){
                debt += amount;
                return;
            }
        }

        graph[from].emplace_back(to, amount);
    }

    unordered_map<string, vector<pair<string, double>>>& getGraph(){
        return graph;
    }

    void reduceDebt(string& payer, string& owed, double amount){
        for (auto& [receiver, debt] : graph[payer]){
            if (receiver == owed){
                debt -= amount;
            }
        }
    }

    void increaseDebt(string& payer, string& owed, double amount){
        for (auto& [receiver, debt] : graph[payer]){
            if (receiver == owed){
                debt += amount;
            }
        }
    }
};

#endif // DEBTGRAPH_H
