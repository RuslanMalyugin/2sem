#include <iostream>
#include <vector>
#include <queue>
using std::vector;
using std::queue;
class graph
{
    vector<vector<int>> edges;
    int size;
public:

     graph(int size_)
    {
        size = size_;
        for (int i = 0; i < size_; i++)
        {
            edges.push_back(vector<int> (0) );
        }
    }

    void add_vortex();
    void add_edge(int from, int to);
    bool has_edge(int from, int to);
    const vector<int> & get_next(int from) const;
    const int vertex () const;

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

const int graph::vertex() const
{
    return size;
}

vector<int> BFS (graph curr_graph, int from)
{
    queue <int> tmp_q;
    tmp_q.push (from);
    vector <bool> color(curr_graph.vertex(),false);
    color[from] = true;
    vector<int> ranges(curr_graph.vertex(), 0);
    while (!tmp_q.empty())
    {
        int curr = tmp_q.front();
        tmp_q.pop();
        const vector<int> & curr_children = curr_graph.get_next(curr);
        for (int i = 0; i < curr_children.size(); i++)
        {
            if (!color[curr_children[i]])
            {
                color[curr_children[i]] = true;
                tmp_q.push(curr_children[i]);
                ranges[curr_children[i]] = ranges[curr] + 1;
            }
        }
    }

    return ranges;
}



int best_way (vector<int> matilda, vector<int> leon, vector<int> milk)
{
    int sum[matilda.size()];
    for ( int i = 0; i < matilda.size(); i++)
    {
        sum[i] = matilda[i] + leon[i] + milk [i];
    }
    int min = sum[0];
    for ( int i = 1; i < matilda.size(); i++)
    {
        if (sum[i] < min)
        {
            min = sum[i];
        }
    }
    return min;
}

int main()
{
    int number_of_points;
    int number_of_edges ;
    int matilda ;
    int leon ;
    int milk ;
    std::cin >> number_of_points;
    std::cin >> number_of_edges;
    std::cin >> matilda;
    std::cin >> leon;
    std::cin >> milk;
    graph curr_graph (number_of_points);
    int from;
    int to;
    for (int i = 0; i < number_of_edges; i++)
    {
        std::cin >> from;
        std::cin >> to;
        curr_graph.add_edge(from - 1,to - 1);
    }
    int min_way;
    min_way = best_way(BFS(curr_graph, matilda - 1),BFS(curr_graph, leon - 1),BFS(curr_graph, milk - 1));
    std::cout << min_way;
    return 0;
}
