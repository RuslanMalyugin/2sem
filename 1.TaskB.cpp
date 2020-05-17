#include <iostream>
#include <vector>
#include <stack>
using std::vector;
using std::stack;
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
    const vector<int> & get_prev(int from) const;
    const int vertex () const;
    void s();

};

void graph::add_vortex()
{
    size++;
    edges.push_back(vector<int> (0) );
}

void graph::add_edge(int from, int to)
{
    edges[from].push_back(to);
    // edges_to[to].push_back(from);
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

const vector<int> &graph::get_prev(int from) const {
}


void DFS1(const graph & curr_graph, int from, vector<int> & result, vector<char> & colors ,bool & is_cycle_exist)
{
    stack<int> tmp_s;
    tmp_s.push(from);
    colors[from] = 1;
    while(!tmp_s.empty())
    {
        bool is_need_to_go = true;
        int curr = tmp_s.top();
        for (int i = 0; i < curr_graph.get_next(curr).size(); i++)
        {
            if (colors[curr_graph.get_next(curr)[i]] == 1 )
            {
                is_cycle_exist = false;
                break;
            }
            if (colors[curr_graph.get_next(curr)[i]] == 0)
            {
                colors[curr_graph.get_next(curr)[i]] = 1;
                tmp_s.push(curr_graph.get_next(curr)[i]);
                is_need_to_go = false;
                break;
            }
        }
        if (!is_cycle_exist)
        {
            break;
        }
        if (is_need_to_go)
        {
            result.push_back(curr);
            colors[curr] = 2;
            tmp_s.pop();
        }
    }
}


int main()
{

    int number_of_points;
    int number_of_edges;
    std::cin >> number_of_points;
    std::cin >> number_of_edges;
    graph curr_graph(number_of_points);
    int from;
    int out;
    for (int i = 0; i < number_of_edges; i++)
    {
        std::cin >> from;
        std::cin >> out;
        curr_graph.add_edge(from,out);
    }
    vector<char> colors (number_of_points, 0);
    vector<int> result;
    bool ice = true;
    DFS1 (curr_graph,0,result,colors, ice);
    for (int i = 0; i < number_of_points; i++)
    {
        if (colors[i] == 0)
        {
            DFS1(curr_graph, i, result, colors, ice);
        }
    }
    if (ice)
    {
        std::cout <<"YES"<< '\n';
        for (int i = result.size() - 1; i >= 0; i--)
        {
            std::cout << result[i] << " ";
        }
    }
    else
        std::cout <<"NO";
};
