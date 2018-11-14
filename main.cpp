#include <iostream>
#include <set>
#include <queue>

#include "graph.h"
#include "fibonacci.h"
#include "disjoint.h"
using namespace std;

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        Edge e = q.top();
        cout << "node source:" << e.source << " + node destination: " << e.destination << " ";
        q.pop();
    }
    cout << endl;
}

int main(int argc, char** argv) {
    Graph* g = new Graph("test");
    cout << " --- print graph --- " << endl;
    g->print();
    vector<Edge>* graph = g->graph;
    int total_nodes = g->total_nodes;
    priority_queue<Edge, vector<Edge>, EdgeCompare> pq;  
    
    for(int i = 0; i < total_nodes;i++) {
        for(int j = 0; j < graph[i].size();j++) {
            pq.push(graph[i].at(j));
        }
    }

    DisjointSet* d = new DisjointSet(total_nodes);
    d->init(total_nodes);
    int count = 0;
    double mstcost = 0;
    while (count < total_nodes && !pq.empty()) {
        Edge e = pq.top();
        pq.pop();

        cout << "current" << e.source << "," << e.destination << endl;
        
        int s1 = d->find(e.source);
        int s2 = d->find(e.destination);
        cout << "set:" << s1 << "," << s1 << endl;
        if (s1 != s2) {
            count++;
            mstcost += e.cost;
            d->merge(s1, s2);
        }
        count++;
    }
    cout << "final cost : " << mstcost;
}