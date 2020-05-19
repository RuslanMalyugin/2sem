#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

using std::vector;
using std::stack;

class graph {
    vector<vector<int>> edges;
    long long size;
public:

    graph(int size_) {
        size = size_;
        for (int i = 0; i < size_; i++) {
            edges.push_back(vector<int>(0));
        }
    }

    void add_vortex();

    void add_edge(int from, int to);

    int has_edge(int from, int to);

    const vector<int> &get_next(int from) const;

    const vector<int> &get_prev(int from) const;

    const long long vertex() const;

    void del(int from, int to) {
        int tmp_size = edges[from].size();
        int index = has_edge(from, to);
        if (index != -1) {
            edges[from].erase(edges[from].begin() + index);
            while (tmp_size - edges[from].size() != 1)
                edges[from].emplace_back(to);
        }
    }

};

void graph::add_vortex() {
    size++;
    edges.push_back(vector<int>(0));
}

void graph::add_edge(int from, int to) {
    edges[from].push_back(to);
}

int graph::has_edge(int from, int to) {
    for (int i = 0; i < edges[from].size(); i++) {
        if (edges[from][i] == to)
            return i;
    }
    return -1;
}

const vector<int> &graph::get_next(int from) const {
    return edges[from];
}

const long long graph::vertex() const {
    return size;
}

const vector<int> &graph::get_prev(int from) const {
}


bool BFS(graph &curr_graph, int start, int finish, vector<int> &path_) {
    std::queue<int> q;
    q.push(start);
    vector<bool> used(curr_graph.vertex());
    vector<int> curr(curr_graph.vertex());
    vector<int> prev(curr_graph.vertex());
    used[start] = true;
    prev[start] = -1;
    while (!q.empty()) {
        int curr_node = q.front();
        q.pop();
        for (size_t i = 0; i < curr_graph.get_next(curr_node).size(); ++i) {
            int to = curr_graph.get_next(curr_node)[i];
            if (!used[to]) {
                used[to] = true;
                q.push(to);
                curr[to] = curr[curr_node] + 1;
                prev[to] = curr_node;
            }
        }
    }
    if (!used[finish])
        return false;
    else {
        vector<int> path;
        for (int v = finish; v != -1; v = prev[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); ++i)
            path_.push_back(path[i]);
        return true;
    }
}

int main() {
    long long n, m, s, t;
    std::cin >> n >> m >> s >> t;
    s--;
    t--;
    graph current(n);
    bool p = false;
    for (int i = 0; i < m; i++) {
        long long from, to;
        std::cin >> from >> to;
        current.add_edge(from - 1, to - 1);
    }
    int a = 0;
    vector<int> matching(n, 0);
    vector<int> previous;
    vector<bool> used(n, false);
    if (!BFS(current, s, t, previous))
        std::cout << "NO";
    else {
        for (int i = 0; i < previous.size() - 1; i++)
            current.del(previous[i], previous[i + 1]);
        for (int i = 0; i < previous.size() - 1; i++)
            current.add_edge(previous[i + 1], previous[i]);
        vector<int> previous2;
        used = vector<bool>(n, false);
        if (!BFS(current, s, t, previous2))
            std::cout << "NO";
        else {
            graph new_graph(n);
            for (int i = 0; i < previous.size() - 1; i++)
                new_graph.add_edge(previous[i], previous[i + 1]);
            for (int i = 0; i < previous2.size() - 1; i++)
                new_graph.add_edge(previous2[i], previous2[i + 1]);
            for (int i = 0; i < new_graph.vertex(); i++) {
                for (int j = 0; j < new_graph.get_next(i).size(); j++) {
                    if (new_graph.has_edge(i, new_graph.get_next(i)[j]) != -1 &&
                            new_graph.has_edge(new_graph.get_next(i)[j], i) != -1) {
                        new_graph.del(i, new_graph.get_next(i)[j]);
                        new_graph.del(new_graph.get_next(i)[j], i);
                    }
                }
            }
            vector<int> previous3;
            vector<int> previous4;
            if (!BFS(new_graph,s,t,previous3)) {
                std::cout << "NO";
            }
            else {
                for (int i = 0; i < previous3.size() - 1; i++) {
                    new_graph.del(previous3[i], previous3[i + 1]);
                }
                if (!BFS(new_graph,s,t,previous4)) {
                    std::cout << "NO";
                }
                else {
                    std::cout << "YES" << '\n';
                    for (int i = 0; i < previous3.size(); i++) {
                        std::cout << previous3[i] + 1 << " ";
                    }
                    std::cout << '\n';
                    for (int i = 0; i < previous4.size(); i++) {
                        std::cout << previous4[i] + 1 << " ";
                    }
                }
            }
        }
    }

}

