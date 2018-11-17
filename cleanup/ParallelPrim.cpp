// STL implementation of Prim's algorithm for MST
#include<bits/stdc++.h>
#include <iostream>
#include <climits>
#include <chrono>
#include <thread>
#include "PriorityQueue.h"

#define INF INT_MAX
using namespace std;
using namespace chrono;

typedef pair<int, int> iPair;
ifstream input ("test.txt");

void concurrentAdd(int v, int u, int weight, int ID);
FineGrainedHeap pq;

class Graph {
    int V;   
    public:
        vector<int> key;
        vector<int> parent;
        vector<bool> inMST;
        list< pair<int, int> > *adj;
        Graph(); 
        void init(int V);
        void addEdge(int u, int v, int w);
        void primMST(int V);
};

Graph::Graph() {}
void Graph::init(int V) {
    this->V = V;
    adj = new list<pair<int, int> > [V];;
}
void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

void Graph::primMST(int V) {   
    pq.insert(0, 0, 0);
    key[0] = 0;

    int pqsize = V;
    while (pqsize != 0) {
        int u = pq.removeMin().second;
        inMST[u] = true; 

        int m = adj[u].size();
        int pid = 0;
        thread *threads = new thread[m];

        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            int v = (*i).first;
            int weight = (*i).second;
            threads[pid] = thread(concurrentAdd, v, u, weight, pid);
            pid++;
        }
        for (int j = 0; j < m; j++) {
                threads[j].join();
        }
        pqsize--;
    }

    printf(" --- MST Result --- :\nSource - Destination\n");
        for (int i = 1; i < V; ++i)
            printf("%d - %d\n", parent[i], i);

}
 
Graph g;
void concurrentAdd(int v, int u, int weight, int ID) {
    if (g.inMST[v] == false && g.key[v] > weight) {
        g.key[v] = weight;
        pq.insert(v, ID, weight);
        g.parent[v] = u;
    }

}
int main() {
    int V, E;
    input >> V;
    input >> E;
    g.init(V);
    g.key.resize(V, INF);
    g.parent.resize(V, -1);
    g.inMST.resize(V, false);
    pq.init(V);
    int source, destination, weight;

    for (int i = 0; i < E; i++) {
        input >> source >> destination >> weight;
        g.addEdge(source, destination, weight);
    }

    cout << "\n --- Graph Description --- \n\tNo. Of vertices : " << V << "\n\tNo. Of edges : " << E << "\n";
    for (int u = 0; u < V; ++u) {
        cout << "\t" << u << ": ";
        for (auto i = g.adj[u].begin(); i != g.adj[u].end(); ++i) {
            int v = (*i).first;
            int w = (*i).second;
            cout << "(" << v << "," << w << ") --> ";
        }
        cout << "END" << endl;
    }

    auto start = std::chrono::high_resolution_clock::now();
    g.primMST(V);
    auto totaltime = std::chrono::high_resolution_clock::now() - start;
    printf("Execution time for parallel Prim's is %lld microseconds\n", totaltime);

    return 0;
}