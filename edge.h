class Edge {
    public:
        int source;
        int destination;
        double cost;
        Edge() {}
        Edge(int source, int destination, double cost) {
            this->source = source;
            this->destination = destination;
            this->cost = cost;
        }
        inline bool operator< (const Edge& r) {
            if(this->cost != r.cost)
                return this->cost < r.cost;
            else
                return this->destination < r.destination;
        }
        inline bool operator> (const Edge& r) {
            if(this->cost != r.cost)
                return this->cost > r.cost;
            else
                return this->destination > r.destination;
        }
        inline bool static compare(const Edge& l,const Edge& r) {
            if(l.cost != r.cost)
                return l.cost> r.cost;
            else
                return l.source > r.destination;
        }
};

/**
 * class EdgeWrapper wrapper around edge class used in Kruskal's concurrent execution
 * where each priority queue stores object of type Edgewrapper to keep a track of which 
 * priority queue edge belonged.
 *
 */
class EdgeWrapper
{
    public:
        Edge edge;

        //identifier to priority queue to which edge belongs.
        //
        int pq_num;
        EdgeWrapper() {
        }
        EdgeWrapper(Edge edge, int pq_num) {
            this->edge = edge;
            this->pq_num = pq_num;
        }
        EdgeWrapper(const EdgeWrapper& ew) {
            this->edge = ew.edge;
            this->pq_num = ew.pq_num;
        }
        bool operator()(const EdgeWrapper& lhs, const EdgeWrapper& rhs) const {
            return (Edge::compare(lhs.edge, rhs.edge)); 
        }
        inline bool operator< (const EdgeWrapper& rhs) {
            return this->edge < rhs.edge;
        }
        inline bool operator> (const EdgeWrapper& rhs) {
            return this->edge > rhs.edge;
        }

};
/*
 * Class EdgeCompare declared for comparison of Edges in Priority Queue.
 * It overrides () operator which is used by STL priority queue for comparison.
 *
 */
class EdgeCompare
{
    public:
    bool operator()(const Edge& lhs, const Edge& rhs) const
    {
        if(lhs.cost != rhs.cost)
            return lhs.cost> rhs.cost;
        else
            return lhs.source> rhs.destination;
    }
};