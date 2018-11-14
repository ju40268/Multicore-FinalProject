#include <iostream>
#include "graph.h"
using namespace std;

int main(int argc, char** argv) {
    Graph* g = new Graph("test");
    cout << " --- print graph --- " << endl;
    g->print();

}