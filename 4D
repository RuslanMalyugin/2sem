#include <iostream>
#include <vector>

using std::vector;

class graph {
    vector<vector<long long>> edges;
public:
    graph(long long size) {
        edges = vector<vector<long long>>(size, vector<long long>());
    }

    void add_edge(long long from, long long to) {
        edges[from].push_back(to);
    }

    long long vertex() const {
        return edges.size();
    }

    vector<long long> get_next(long long from) const {
        return edges[from];
    }

    vector<vector<long long>> get_edges() const {
        return edges;
    }
};

void dfs(vector<long long> &enters, vector<long long> &exits, vector<vector<long long>> &parents, long long &timer,
         const graph &current_graph,
         long long current, long long lg, long long par = 0) {
    enters[current] = ++timer;
    parents[current][0] = par;
    for (long long i = 1; i <= lg; i++) {
        parents[current][i] = parents[parents[current][i - 1]][i - 1];
    }
    for (long long i = 0; i < current_graph.get_next(current).size(); i++) {
        long long to = current_graph.get_next(current)[i];
        if (to != par) {
            dfs(enters, exits, parents, timer, current_graph, to, lg, current);
        }
    }
    exits[current] = ++timer;
}

bool upper(vector<long long> &enters, vector<long long> &exits, long long first, long long second) {
    return enters[first] <= enters[second] && exits[first] >= exits[second];
}

long long lca(vector<long long> &enters, vector<long long> &exits, vector<vector<long long>> &parents, long long first,
              long long second, long long lg) {
    if (first == second)
        return first;
    if (upper(enters, exits, first, second))
        return first;
    if (upper(enters, exits, second, first))
        return second;
    for (long long i = lg; i >= 0; i--) {
        if (!upper(enters, exits, parents[first][i], second))
            first = parents[first][i];
    }
    return parents[first][0];
}

long long simple_log(long long n) {
    long long l = 1;
    while ((1 << l) <= n)
        ++l;
    return l;
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    long long from;
    graph curr_graph(n);
    for (long long i = 0; i < n - 1; i++) {
        std::cin >> from;
        curr_graph.add_edge(from, i + 1);
    }
    vector<long long> enters(n);
    vector<long long> exits(n);
    long long lg = simple_log(n);
    vector<vector<long long>> parents(n, vector<long long>(lg + 1));
    long long a1, a2;
    std::cin >> a1 >> a2;
    long long x, y, z;
    std::cin >> x >> y >> z;
    long long  timer = 0;
    dfs(enters,exits,parents,timer,curr_graph, 0,lg);
    long long v = lca(enters, exits, parents, a1, a2, lg);
    long long res = v;
    for (long long i = 2; i <= m; i++) {
        long long tmp_a1 = (x * a1 + y * a2 + z) % n;
        long long tmp_a2 = (x * a2 + y * tmp_a1 + z) % n;
        a1 = tmp_a1;
        a2 = tmp_a2;
        long long  tmp = lca(enters, exits, parents, (a1 + v) % n, a2, lg);
        res += tmp;
        v = tmp;
    }

    std::cout << res;
    return 0;
}
