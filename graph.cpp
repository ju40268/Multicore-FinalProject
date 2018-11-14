#include <iostream>
#include <fstream>
#include "graph.h" 
using namespace std;
 
Graph::Graph(char* fname) {
    cout << "Currently processing graph file: " << fname << endl;
    ifstream infile(fname);
    infile >> total_nodes;

    init(total_nodes);
    int source, destination;
    double cost;
    //read node1, node2 and cost. store undirected graphs.
    while(infile >> source >> destination >>cost) {
        graph[source].push_back(Edge(source,destination,cost));
        graph[destination].push_back(Edge(destination,source,cost));
    }
    infile.close();
}

Graph::Graph() {
    cout << "Currently init empty mst." << endl;
    init(total_nodes);
}

void Graph::init(int total_nodes) {
    this->total_nodes = total_nodes;
    graph = new vector<Edge>[total_nodes];
}

void Graph::add(Edge edge) {
    cout << "currently adding the edge" << edge.node1 << edge.node1 << endl;
    graph[edge.node1].push_back(Edge(edge.node1,edge.node2,edge.cost));
    graph[edge.node2].push_back(Edge(edge.node2,edge.node1,edge.cost));
}

void Graph::print() {
    for(int i = 0; i < total_nodes; i++) {
        cout<< "Vertex id " << i <<": ";
        for(int j=0; j < graph[i].size(); j++) {
            cout<< graph[i].at(j).node2 << ", cost : " << graph[i].at(j).cost <<". | ";
        }
        cout<<endl;
    }

}