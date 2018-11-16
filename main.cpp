#include <iostream>
#include <set>
#include <queue>
#include "graph.h"
#include "fibonacci.h"
#include "disjoint.h"
using namespace std;

void kruskal() {
    Graph* g = new Graph("test3");
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
    cout << "final kruskal cost : " << mstcost << endl;
    cout << "mst : " << endl;
    mst->print();
}

void prim() {
    Graph* g = new Graph("test3");
    priority_queue<Edge, vector<Edge>, EdgeCompare> pq;
    vector<Edge>* graph = g->graph;
    int total_nodes = g->total_nodes;
    bool visited[total_nodes];

    Graph* mst = new Graph(total_nodes);

    int start = 0, count = 0, mstcost = 0, cur = 0;
    // mark everything node as not visited
    for (int i = 0; i < total_nodes; i++) {
        visited[i] = false;
    }
    for(int i = 0; i < graph[start].size(); i++) {
        pq.push(graph[start].at(i));
    }
    visited[start] = true;
    while (count < total_nodes && !pq.empty()) {
        Edge e = pq.top(); pq.pop();
        if (!visited[e.source] || !visited[e.destination]) {
            mst->add(e);
            mstcost += e.cost;
            if (!visited[e.source]) {
                visited[e.source] = true;
                cur = e.source;
            }
            if (!visited[e.destination]) {
                visited[e.destination] = true;
                cur = e.destination;
            }
            for (Edge neighbour : graph[cur]) {
                pq.push(neighbour);
            }
            count++;
        }
    }
    cout << "final prim cost : " << mstcost << endl;
    cout << "mst : " << endl;
    mst->print();
} 


void dfs(int v, bool visited[], vector<Edge>* graph) {
    visited[v] = true;
    cout << v << " "; 
    for (Edge e : graph[v]) {
        if (!visited[e.destination]) dfs(e.destination, visited, graph);
    }
}

void connected_component() {
    Graph* g = new Graph("test4");
    vector<Edge>* graph = g->graph;
    int total_nodes = g->total_nodes;
    bool *visited = new bool[total_nodes]; 
    int component_count = 0;

    for(int i = 0; i < total_nodes; i++) 
        visited[i] = false; 
  
    for (int i = 0; i < total_nodes; i++) {
        if (!visited[i]) {
            dfs(i, visited, graph);
            component_count++;
            cout << endl;
        }
    }
    cout << "Total component count : " << component_count << endl;
}

int main(int argc, char** argv) {
    connected_component();
    kruskal();
    prim();
}