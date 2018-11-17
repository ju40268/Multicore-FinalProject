#include <iostream>
#include <set>
#include <queue>
#include "graph.h"
#include "fibonacci.h"
#include "disjoint.h"
#include "adjMatrix.h"
using namespace std;
#define total_nodes 9

// void kruskal() {
//     Graph* g = new Graph("test3");
//     g->print();
//     vector<Edge>* graph = g->graph;
//     int total_nodes = g->total_nodes;

//     Graph* mst = new Graph(total_nodes);
//     priority_queue<Edge, vector<Edge>, EdgeCompare> pq;  
    
//     for(int i = 0; i < total_nodes;i++) {
//         for(int j = 0; j < graph[i].size();j++) {
//             pq.push(graph[i].at(j));
//         }
//     }

//     DisjointSet* d = new DisjointSet(total_nodes);
//     d->init(total_nodes);

//     int count = 0;
//     int mstcost = 0;
//     while (count < total_nodes && !pq.empty()) {
//         Edge e = pq.top(); pq.pop();
//         cout << "current : " << e.source << ", " << e.destination << endl;
        
//         int s1 = d->find(e.source);
//         int s2 = d->find(e.destination);
//         if (s1 != s2) {
//             count++;
//             mstcost += e.cost;
//             mst->add(e);
//             d->merge(s1, s2);
//         }
//     }
//     cout << "final kruskal cost : " << mstcost << endl;
//     cout << "mst : " << endl;
//     mst->print();
// }

// void prim() {
//     Graph* g = new Graph("test3");
//     priority_queue<Edge, vector<Edge>, EdgeCompare> pq;
//     vector<Edge>* graph = g->graph;
//     int total_nodes = g->total_nodes;
//     bool visited[total_nodes];

//     Graph* mst = new Graph(total_nodes);

//     int start = 0, count = 0, mstcost = 0, cur = 0;
//     // mark everything node as not visited
//     for (int i = 0; i < total_nodes; i++) {
//         visited[i] = false;
//     }
//     for(int i = 0; i < graph[start].size(); i++) {
//         pq.push(graph[start].at(i));
//     }
//     visited[start] = true;
//     while (count < total_nodes && !pq.empty()) {
//         Edge e = pq.top(); pq.pop();
//         if (!visited[e.source] || !visited[e.destination]) {
//             mst->add(e);
//             mstcost += e.cost;
//             if (!visited[e.source]) {
//                 visited[e.source] = true;
//                 cur = e.source;
//             }
//             if (!visited[e.destination]) {
//                 visited[e.destination] = true;
//                 cur = e.destination;
//             }
//             for (Edge neighbour : graph[cur]) {
//                 pq.push(neighbour);
//             }
//             count++;
//         }
//     }
//     cout << "final prim cost : " << mstcost << endl;
//     cout << "mst : " << endl;
//     mst->print();
// } 


void dfs(int v, bool visited[], vector<Edge>* graph) {
    visited[v] = true;
    cout << v << " "; 
    for (Edge e : graph[v]) {
        if (!visited[e.destination]) dfs(e.destination, visited, graph);
    }
}

// void connected_component() {
//     Graph* g = new Graph("test4");
//     vector<Edge>* graph = g->graph;
//     int total_nodes = g->total_nodes;
//     bool *visited = new bool[total_nodes]; 
//     int component_count = 0;

//     for(int i = 0; i < total_nodes; i++) 
//         visited[i] = false; 
  
//     for (int i = 0; i < total_nodes; i++) {
//         if (!visited[i]) {
//             dfs(i, visited, graph);
//             component_count++;
//             cout << endl;
//         }
//     }
//     cout << "Total component count : " << component_count << endl;
// }


int minKey(int key[], bool mstSet[]) { 
    // Initialize min value 
    int min = INT_MAX, min_index; 
    
    for (int i = 0; i < total_nodes; i++) 
        if (mstSet[i] == false && key[i] < min) 
            min = key[i], min_index = i; 
    
    return min_index; 
} 

int printMST(int parent[], int n, int graph[][total_nodes]) { 
    cout << "Edge \tWeight\n"; 
    for (int i = 1; i < total_nodes; i++) 
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]); 
} 

void calculateMST(int graph[][total_nodes]) { 
    int parent[total_nodes];  
    int key[total_nodes];  
    bool mstSet[total_nodes];   
    for (int i = 0; i < total_nodes; i++) {
        key[i] = INT_MAX, mstSet[i] = false;
    }
    key[0] = 0;      
    parent[0] = -1; 
    for (int count = 0; count < total_nodes-1; count++) { 
        int u = minKey(key, mstSet); 
        mstSet[u] = true; 
        for (int v = 0; v < total_nodes; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) 
                parent[v] = u, key[v] = graph[u][v]; 
        }
    } 
    printMST(parent, total_nodes, graph); 
} 
  

void parallel_prim() {
    int nodes_local = 0;
    int total_edges = 14;
    matrixGraph* mg = new matrixGraph(total_nodes, total_edges);
    char* fname = "test";
    ifstream infile(fname);
    infile >> nodes_local;
    int source, destination;
    double cost;
    while(infile >> source >> destination >> cost) {
        mg->addedge(source, destination, cost);
    }
    infile.close();
    mg->PrintMG();
    calculateMST(mg->adjMatrix);
}

int main(int argc, char** argv) {
    parallel_prim();
    // connected_component();
    // kruskal();
    // prim();
}