#include <iostream>
#include <vector>
#include <stack>
using std::vector;
using std::stack;
class graph
{
    vector<vector<int>> edges;
    long long  size;
public:

    graph(int size_)
    {
        size = size_;
        for (int i = 0; i < size_; i++)
        {
            edges.push_back(vector<int> (0) );
            //edges_to.push_back(vector<int> (0) );
        }
    }

    void add_vortex();
    void add_edge(int from, int to);
    bool has_edge(int from, int to);
    const vector<int> & get_next(int from) const;
    const vector<int> & get_prev(int from) const;
    const long long  vertex () const;

};

void graph::add_vortex()
{
    size++;
    edges.push_back(vector<int> (0) );
}

void graph::add_edge(int from, int to)
{
    edges[from].push_back(to);
    edges[to].push_back(from);
}

bool graph::has_edge(int from, int to)
{
    for (int i = 0; i < edges[from].size(); i++)
    {
        if ( edges[from][i] == to )
            return true;
    }
    return false;
}

const vector<int> & graph::get_next(int from) const
{
    return edges[from];
}

const long long  graph::vertex() const
{
    return size;
}

const vector<int> &graph::get_prev(int from) const {
    //return edges_to[from];
}


bool DFS2 (const graph & curr_graph, int from, vector<int> & matching, vector<bool> & used, int & sum) {
    if (used[from])
        return false;
    used[from] = true;
    for (long long i = 0; i < curr_graph.get_next(from).size(); i++) {
        if (matching[curr_graph.get_next(from)[i]] == -1 || DFS2(curr_graph, matching[curr_graph.get_next(from)[i]], matching, used, sum)) {
            if (matching[curr_graph.get_next(from)[i]] == -1)
                sum++;
            matching[curr_graph.get_next(from)[i]] = from;
            return true;
        }
    }
    return false;
}
long long repair_bridge(const graph & curr_graph, int cost2, int cost1, int count, vector<vector<char>> bridges) {
    if (2 * cost1 <= cost2)
        return count * cost1;
    int sum = 0;
    int n = bridges.size();
    int m = bridges[0].size();
    int sum2 = 0;
    vector<int> matching(curr_graph.vertex(), -1);
    for (long long  i = 0 ; i < curr_graph.vertex(); i++) {
       if (bridges[i / m][i % m] == '*' && (i / m + i % m) % 2 == 0 ) {
           vector<bool> used(curr_graph.vertex(), false);
           if (DFS2(curr_graph, i , matching, used, sum))
               sum2++;
       }
    }

    return (count - sum * 2) * cost1 + sum * cost2;
}

int main()
{
    long long n, m , a, b;
    int count = 0;
    vector<vector<char>> bridge;
    std::cin >> n >> m >> a >> b;
    for (long long i = 0 ; i < n ; i++){
        bridge.emplace_back();
        for (long long j = 0; j < m; j++) {
            char tile;
            std::cin >> tile;
            if (tile == '*')
                count++;
            bridge[i].push_back(tile);
        }
    }

    graph current (n * m) ;
    for (long long i = 0; i < n; i++) {
        for (long long j = 0; j < m - 1; j++) {
            if (bridge[i][j] == '*' && bridge[i][j + 1] == '*')
                current.add_edge(m * i + j, m * i + j + 1);
        }
    }
    for (long long i = 0; i < n - 1; i++) {
        for (long long j = 0; j < m; j++) {
            if (bridge[i][j] == '*' && bridge[i + 1][j] == '*')
                current.add_edge(m * i + j, m * (i + 1) + j);
        }
    }

    std::cout << repair_bridge(current, a, b, count, bridge);
}
