#include <iostream>
#include <vector>
#include <set>

using std::vector;
const long long BIG = 10000000000;
class graph
{
    vector<vector<std::pair<long long,long long>>> edges;
    long long size;
public:

    graph(long long size_)
    {
        size = size_;
        for (long long i = 0; i < size_; i++)
        {
            add_vortex();
        }
    }

    void add_vortex();
    void add_edge(long long from, long long to, long long cost);
    bool has_edge(long long from, long long to);
    const vector<std::pair<long long,long long>> & get_next(long long from) const;
    long long vertex () const;


};

void graph::add_vortex()
{
    size++;
    edges.emplace_back(0);
}

void graph::add_edge(long long from, long long to, long long cost)
{
    edges[from].push_back(std::pair<long long,long long>(to,cost));
}

bool graph::has_edge(long long from, long long to)
{
    for (long long i = 0; i < edges[from].size(); i++)
    {
        if ( edges[from][i].first == to)
            return true;
    }
    return false;
}

const vector<std::pair<long long,long long>> & graph::get_next(long long from) const
{
    return edges[from];
}

long long graph::vertex() const
{
    return size;
}

vector<long long> dijkstra (const graph& curr_graph, long long start, long long limit) {
    vector<long long> distance(curr_graph.vertex(), BIG);
    std::set<vector<long long>> queue;
    distance[start] = 0;
    queue.insert(vector<long long> {distance[start], start, 0});
    while (!queue.empty()) {
        long long curr = (*queue.begin())[1];
        long long key = (*queue.begin())[2];
        queue.erase(queue.begin());
        for (size_t i = 0; i < curr_graph.get_next(curr).size(); i++) {
            long long finish = curr_graph.get_next(curr)[i].first;
            long long cost = curr_graph.get_next(curr)[i].second;
            if (distance[curr] < distance[finish] - cost) {
                queue.erase(vector<long long>{distance[finish], finish, key});
                if ( key + 1 <= limit) {
                distance[finish] = distance[curr] + cost;

                queue.insert(vector<long long>{distance[finish], finish, key + 1});}
            }
        }
    }
    return distance;
}

int main () {
    long long N,  M, K, S, F;
    std::cin >> N>> M >> K >> S >> F;
    graph curr_graph(N);
    long long from;
    long long to ;
    long long cost;
    for (long long i = 0; i < M; i++) {
        std::cin >> from>> to >> cost;
        curr_graph.add_edge(from - 1, to - 1, cost);
    }
    long long result = dijkstra(curr_graph,S - 1,K)[F - 1];
    if (result >= BIG)
        std::cout << -1;
    else
    std::cout << result;

}
