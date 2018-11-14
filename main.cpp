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
        cout << "node 1:" << e.node1 << " node 2: " << e.node2 << " ";
        q.pop();
    }
    cout << endl;
}

int main(int argc, char** argv) {
    Graph* g = new Graph("test");
    cout << " --- print graph --- " << endl;
    g->print();
    vector<Edge>* graph = g->graph;
    int vertex = g->total_nodes;
    int parent[vertex];
    set<int> sets[vertex];
    priority_queue<Edge, vector<Edge>, EdgeCompare> pq;  
    
    for(int i=0;i< g->total_nodes;i++) {
        for(int j=0;j<graph[i].size();j++) {
            pq.push(graph[i].at(j));
        }
    }
    DisjointSet* d = new DisjointSet(vertex);
    print_queue(pq);
}