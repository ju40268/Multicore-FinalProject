#include <vector>
#include <fstream>
#include <iostream>
#include "edge.h"

using namespace std;

class Graph {
    private:   
    public:
        int total_nodes;
        vector<Edge>* graph; 
        Graph(void);
        Graph(char* fname);
        void add(Edge edge);
        void init(int total_nodes);
        void print();
};  
 