#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <unordered_map>

using std::vector;
const long long BIG = 1000000000000000000;

class graph {
    vector<vector<std::pair<long long, long long>>> edges;
    long long size;
public:

    graph(long long size_) {
        size = size_;
        for (long long i = 0; i < size_; i++) {
            add_vortex();
        }
    }

    void add_vortex();

    void add_edge(long long from, long long to, long long cost);

    bool has_edge(long long from, long long to);

    const vector<std::pair<long long, long long>> &get_next(long long from) const;

    long long vertex() const;


};

void graph::add_vortex() {
    size++;
    edges.emplace_back(0);
}

void graph::add_edge(long long from, long long to, long long cost) {
    edges[from].push_back(std::pair<long long, long long>(to, cost));
    edges[to].push_back(std::pair<long long, long long>(from, cost));
}

bool graph::has_edge(long long from, long long to) {
    for (long long i = 0; i < edges[from].size(); i++) {
        if (edges[from][i].first == to)
            return true;
    }
    return false;
}

const vector<std::pair<long long, long long>> &graph::get_next(long long from) const {
    return edges[from];
}

long long graph::vertex() const {
    return size;
}

long long prima_MST(const graph &current_graph) {
    vector<bool> used(current_graph.vertex(), false);
    vector<long long> keys(current_graph.vertex(), BIG);
    vector<long long> par(current_graph.vertex(), -1);
    long long sum = 0;
    keys[0] = 0;
    std::set<std::pair<long, long>> tmp_q;
    tmp_q.insert(std::make_pair(0, 0));
    while (!tmp_q.empty()) {
        long long curr = tmp_q.begin()->second;
        used[curr] = true;
        tmp_q.erase(tmp_q.begin());
        for (size_t i = 0; i < current_graph.get_next(curr).size(); i++) {
            if (used[current_graph.get_next(curr)[i].first])
                continue;
            if (current_graph.get_next(curr)[i].second < keys[current_graph.get_next(curr)[i].first]) {
                tmp_q.erase(std::make_pair(keys[current_graph.get_next(curr)[i].first],
                                           current_graph.get_next(curr)[i].first));
                keys[current_graph.get_next(curr)[i].first] = current_graph.get_next(curr)[i].second;
                par[current_graph.get_next(curr)[i].first] = curr;
                tmp_q.insert(std::make_pair(keys[current_graph.get_next(curr)[i].first],
                                            current_graph.get_next(curr)[i].first));
            }
        }
    }
    for (size_t i = 0; i < current_graph.vertex(); i++) {
        if (par[i] != -1) {
            sum += keys[i];
        }
    }
    return sum;
}

int main() {
    long long N, M;
    std::cin >> N >> M;
    vector<long long> costs(N);
    long long cost;
    for (long long i = 0; i < N; i++) {
        std::cin >> cost;
        costs[i] = cost;
    }
    long long mincost = costs[0];
    long long index = 0;
    for (long long i = 0; i < N; i++) {
        if (mincost > costs[i]) {
            index = i;
            mincost = costs[i];
        }
    }
    graph curr_graph(N);
    std::vector<long long> offers(N, BIG);
    for (long long i = 0; i < M; i++) {
        long long from, to;
        std::cin >> from >> to >> cost;
        if (from - 1 == index) {
            if (offers[to - 1] > cost)
                offers[to - 1] = cost;
            continue;
        }
        if (to - 1 == index) {
            if (offers[from - 1] > cost)
                offers[from - 1] = cost;
            continue;
        }
        if (from - 1 != index && to - 1 != index)
            curr_graph.add_edge(from - 1, to - 1, cost);
    }

    for (long long i = 0; i < N; i++) {
        if (index == i)
            continue;
        if (costs[index] + costs[i] < offers[i])
            curr_graph.add_edge(index, i, costs[index] + costs[i]);
        else
            curr_graph.add_edge(index, i, offers[i]);
    }
    std::cout << prima_MST(curr_graph);

}
