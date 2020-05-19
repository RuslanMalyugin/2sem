#include <iostream>
#include <vector>
#include <set>

using std::vector;
const double BIG = 10.0;
class graph
{
    vector<vector<std::pair<long long,double>>> edges;
    long long size = 0;
public:

    graph(long long size_)
    {
        size = size_;
        for (long long i = 0; i < size_; i++)
        {
            edges.emplace_back(vector<std::pair<long long,double>>(0));
        }
    }

    void add_vortex();
    void add_edge(long long from, long long to, double cost);
    bool has_edge(long long from, long long to);
    const vector<std::pair<long long,double>> & get_next(long long from) const;
    long long vertex () const;


};

void graph::add_vortex()
{
    size++;
    edges.emplace_back(vector<std::pair<long long,double>>(0));
}

void graph::add_edge(long long from, long long to, double cost)
{
    edges[from].push_back(std::pair<long long,double>(to,cost));
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

const vector<std::pair<long long,double>> & graph::get_next(long long from) const
{
    return edges[from];
}

long long graph::vertex() const
{
    return size;
}

vector<double> dijkstra(const graph& curr_graph, long long start) {
    vector<double> distance(curr_graph.vertex(), BIG);
    std::set<std::pair<double,long long>> queue;
    distance[start] = 0.0;
    queue.insert(std::pair<double,long long>(distance[start],start));
    while (!queue.empty()) {
        long long curr = queue.begin()->second;
        queue.erase(queue.begin());
        for (size_t i = 0; i < curr_graph.get_next(curr).size(); i++) {
            long long finish = curr_graph.get_next(curr)[i].first;
            double cost = curr_graph.get_next(curr)[i].second;
            if ((1 - (1 - distance[curr]) * (1 - cost) ) < distance[finish]) {
                queue.erase(std::pair<double, long long>(distance[finish], finish));
                distance[finish] = (1 - (1 - distance[curr]) * (1 - cost) ) ;
                queue.insert(std::pair<double, long long>(distance[finish], finish));
            }
        }
    }
    return distance;
}

int main () {
    long long N, M, S, F;
    std::cin >> N>> M >> S >> F;
    graph curr_graph(N);
    long long s, f;
    int p;
    double p2;
    for (long long i = 0; i < M; i++) {
        std::cin >> s >> f >> p;
        p2 = p * 0.01;
        curr_graph.add_edge(s - 1, f - 1, p2);
        curr_graph.add_edge(f - 1, s - 1, p2);
    }
    double result = dijkstra(curr_graph,S - 1)[F - 1];
    std::cout << result;

}
