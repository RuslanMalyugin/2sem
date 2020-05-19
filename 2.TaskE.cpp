#include <iostream>
#include <vector>

using std::vector;
using std::pair;
const double BIG = 10000000000;

struct simple_graph {
    struct edge {
        int from;
        int to;
        double cost;
        double comm;
        edge(int from_, int to_, double cost_, double comm_) {
            from = from_;
            to = to_;
            cost = cost_;
            comm = comm_;
        }
    };
    vector<edge> edges;
    int size;
    int edge_count;

    simple_graph(int size_) {
        size = size_;
        edge_count = 0;
    }

    void add_edge (int from, int to, double cost, double comm) {
        edges.emplace_back(edge(from, to, cost, comm));
        edge_count++;
    }
};

bool ford_bellman(const simple_graph & curr_graph, int start, double start_money) {
    vector<double> distance(curr_graph.size, 0);
    distance[start] = start_money;
    int checker = -1;
    for ( int i = 0 ; i < curr_graph.size + 1; i++) {
        checker = -1;
        for ( int j = 0 ; j < curr_graph.edge_count; j++) {
                if (distance[curr_graph.edges[j].to] < (distance[curr_graph.edges[j].from] - curr_graph.edges[j].comm) * curr_graph.edges[j].cost) {
                    distance[curr_graph.edges[j].to] = std::max(-BIG,(distance[curr_graph.edges[j].from] - curr_graph.edges[j].comm) * curr_graph.edges[j].cost);
                    checker = curr_graph.edges[j].to;
            }
        }
    }
    return checker != -1;
}

int main () {
    int N, M, S;
    double V;
    std::cin >> N >> M >> S >> V;
    int from, to;
    double money1, comm1, money2, comm2;
    simple_graph graph(N);
    for (int i = 0 ; i < M; i++) {
        std::cin >> from >> to >> money1 >> comm1 >> money2 >> comm2;
        graph.add_edge(from - 1, to - 1, money1, comm1);
        graph.add_edge(to - 1,from - 1, money2, comm2);
    }
    bool chk = ford_bellman(graph,S - 1,V);
    if (chk)
        std::cout << "YES";
    else
        std::cout << "NO";

}
