class DisjointSet {
    private:
        int total_nodes;   
        int *parent;
        int *rank;
    public:
        DisjointSet(int total_nodes);
        void print();
        void init(int total_nodes);
        int find(int u);
        void merge(int x, int y);
};

DisjointSet::DisjointSet(int total_nodes) {
    this->total_nodes = total_nodes;
    parent = new int[total_nodes + 1];
    rank = new int[total_nodes + 1];
}
void DisjointSet::init(int total_nodes) {
    for (int i = 0; i < total_nodes; i++) {
        this->parent[i] = i;
        this->rank[i] = 0;
    }
}

void DisjointSet::print() {
    for (int i = 0; i < total_nodes; i++) {
        cout << this->parent[i] << ", ";
    }
    cout << endl;
}
int DisjointSet::find(int x) {
    if (this->parent[x] == x) return x;
    return find(this->parent[x]);
}

void DisjointSet::merge(int x, int y) {
    x = find(x), y = find(y); 
    if (this->rank[x] > this->rank[y]) this->parent[y] = x; 
    else this->parent[x] = y; 
    if (this->rank[x] == this->rank[y]) this->rank[y]++; 
}

