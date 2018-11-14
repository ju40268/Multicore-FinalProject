class Edge {
    public:
        int node1;
        int node2;
        double cost;
        Edge(int node1, int node2, double cost) {
            this->node1 = node1;
            this->node2 = node2;
            this->cost = cost;
        }
        inline bool operator< (const Edge& r) {
            if(this->cost != r.cost)
                return this->cost< r.cost;
            else
                return this->node2 < r.node2;
        }
        inline bool operator> (const Edge& r) {
            if(this->cost != r.cost)
                return this->cost > r.cost;
            else
                return this->node2 > r.node2;
        }
        inline bool static compare(const Edge& l,const Edge& r) {
            if(l.cost != r.cost)
                return l.cost> r.cost;
            else
                return l.node1 > r.node2;
        }
};
