class DisjointSet {
    private:
        int total_nodes;   
        int *parent;
        int *rank;
    public:
        DisjointSet(int total_nodes);
        int find(int u);
        void merge(int x, int y);
};
DisjointSet::DisjointSet(int total_nodes) {
    this->total_nodes = total_nodes;
    parent = new int[total_nodes + 1];
    rank = new int[total_nodes + 1];
}
int DisjointSet::find(int u) {
    if (u != parent[u]) 
        parent[u] = find(parent[u]); 
    return parent[u]; 
}
void DisjointSets::merge(int x, int y) {
    x = find(x), y = find(y); 
    if (rank[x] > rank[y]) parent[y] = x; 
    else parent[x] = y; 
    if (rank[x] == rank[y]) rank[y]++; 
}

