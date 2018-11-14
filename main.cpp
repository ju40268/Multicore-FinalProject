#include <iostream>
#include <set>
#include <queue>

#include "graph.h"
#include "fibonacci.h"
#include "disjoint.h"
using namespace std;

void kruskal() {
    Graph* g = new Graph("test");
    g->print();
    vector<Edge>* graph = g->graph;
    int total_nodes = g->total_nodes;

    Graph* mst = new Graph(total_nodes);
    priority_queue<Edge, vector<Edge>, EdgeCompare> pq;  
    
    for(int i = 0; i < total_nodes;i++) {
        for(int j = 0; j < graph[i].size();j++) {
            pq.push(graph[i].at(j));
        }
    }

    DisjointSet* d = new DisjointSet(total_nodes);
    d->init(total_nodes);

    int count = 0;
    int mstcost = 0;
    while (count < total_nodes && !pq.empty()) {
        Edge e = pq.top(); pq.pop();
        cout << "current : " << e.source << ", " << e.destination << endl;
        
        int s1 = d->find(e.source);
        int s2 = d->find(e.destination);
        if (s1 != s2) {
            count++;
            mstcost += e.cost;
            mst->add(e);
            d->merge(s1, s2);
        }
    }
    cout << "final cost : " << mstcost << endl;
    cout << "mst : " << endl;
    mst->print();
}

void prim() {

}

int main(int argc, char** argv) {
    kruskal();
}