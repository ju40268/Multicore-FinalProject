// STL implementation of Prim's algorithm for MST
#include<bits/stdc++.h>
#include <iostream>
#include <climits>
#include <chrono>
#define INF INT_MAX
using namespace std;
using namespace chrono;

typedef pair<int, int> iPair;
ifstream input ("test.txt");

priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
vector<int> key;
vector<int> parent;
vector<bool> inMST;

class Graph {
    int V;   
    public:
        list< pair<int, int> > *adj;
        Graph(int V); 
        void addEdge(int u, int v, int w);
        void primMST();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<iPair> [V];
}
void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}
void mst(int v, int u, int weight) {
    if (inMST[v] == false && key[v] > weight) {
        // Updating key of v
        key[v] = weight;
        pq.push(make_pair(key[v], v));
        parent[v] = u;
    }
}
void Graph::primMST() {   
    pq.push(make_pair(0, 0));
    key[0] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
 
        inMST[u] = true; 
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            int v = (*i).first;
            int weight = (*i).second;
            mst(v,u,weight);
        }
    }
    printf("MST:\nV1 - V2\n");
    for (int i = 1; i < V; ++i)
        printf("%d - %d\n", parent[i], i);
}
 
int main() {

    int V,E;
    input>>V;
    input>>E;
    Graph g(V);

    key.resize(V,INF);
    parent.resize(V,-1);
    inMST.resize(V,false);
    int source, destination, weight;
    for(int i = 0; i < E; i++) {
        input >> source >> destination >>weight;
        g.addEdge(source,destination,weight);
    }
    cout << "\n --- Graph Description ---\n\tNo. Of vertices : "<<V<<"\n\tNo. Of edges : "<<E<<"\n";
    for (int u = 0; u < V; ++u) {
        cout << "\t" << u << ": ";
        for(auto i = g.adj[u].begin(); i != g.adj[u].end(); ++i) {
            int v = (*i).first;
            int w = (*i).second;
            cout << "(" << v << "," << w << ") --> ";
        }
        cout<< "END" << endl;
    }
  
    auto start = std::chrono::high_resolution_clock::now();
    g.primMST();
    auto totaltime = std::chrono::high_resolution_clock::now() - start;
    printf("Total time consumed: %lld \n", totaltime);
    return 0;
}