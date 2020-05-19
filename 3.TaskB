#include <iostream>
#include <vector>
#include <algorithm>

template<typename T1>
struct triplet {
    triplet(T1 c, T1 f, T1 t) : cost(c), from(f), to(t) {
    }

    triplet() = default;

    T1 cost;
    T1 from;
    T1 to;

    bool operator<(const triplet &another) const {
        if (cost != another.cost)
            return cost < another.cost;
        else {
            if (from != another.from)
                return from < another.from;
            else {
                return to < another.to;
            }
        }
    }
};

struct graph {
    std::vector<triplet<long long>> edges = {};
    long long size = 0;
public:
    graph() = default;
    graph(const graph & another) {
        size = another.size;
        edges = another.edges;
    }
    explicit graph(long long s) {
        size = s;
        edges = {};
    }

    void sort() {
        std::sort(edges.begin(), edges.end());
    }

    std::vector<triplet<long long>> get_edges() const {
        return edges;
    }

    void add_edge(long long from, long long to, long long cost) {
        edges.emplace_back(triplet<long long>(cost, from, to));
    }

    long long edges_count() const {
        return edges.size();
    }

    long long vertex() const {
        return size;
    }

};

long long kruscal_MST(const graph &current) {
    graph current_graph = current;
    current_graph.sort();
    std::vector<long long> indexes(current_graph.vertex());
    long long  cost = 0;
    for (long long i = 0; i < current_graph.vertex(); i++) {
        indexes[i] = i;
    }
    for (long long i = 0; i < current_graph.edges_count(); i++) {
        if (indexes[current_graph.edges[i].to] != indexes[current_graph.edges[i].from]) {
            cost += current_graph.edges[i].cost;
            long long old_index = indexes[current_graph.edges[i].to];
            long long new_index = indexes[current_graph.edges[i].from];
            for (long long j = 0; j < current_graph.vertex(); j++) {
                if (indexes[j] == old_index) {
                    indexes[j] = new_index;
                }
            }
        }
    }
    return cost;
}

int main() {
    long long N, M;
    std::cin >> N >> M;
    graph current(N);
    for (long long i = 0; i < M; i++) {
        long long from, to, cost;
        std::cin >> from >> to >> cost;
        current.add_edge(from - 1, to - 1, cost);
    }
    long long result = kruscal_MST(current);
    std::cout << result;
    return 0;
}
