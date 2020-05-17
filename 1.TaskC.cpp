#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
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

void DFS2(const graph & curr_graph, int from, vector<int> & result2, vector<char> & colors ,bool & is_cycle_exist,
          vector<vector<int>> & components)
{
    stack<int> tmp_s;
    tmp_s.push(from);
    colors[from] = 1;
    components.emplace_back();
    while(!tmp_s.empty())
    {
        bool is_need_to_go = true;
        int curr = tmp_s.top();
        for (int i = 0; i < curr_graph.get_next(curr).size(); i++)
        {
            if (colors[curr_graph.get_next(curr)[i]] == 0)
            {
                colors[curr_graph.get_next(curr)[i]] = 1;
                tmp_s.push(curr_graph.get_next(curr)[i]);
               // components[components.size() - 1].push_back(curr_graph.get_next(curr)[i]);
                is_need_to_go = false;
                break;
            }
        }
        if (is_need_to_go)
        {
            result2.push_back(curr);
            colors[curr] = 2;
            components[components.size() - 1].push_back(curr);
            tmp_s.pop();
        }
    }
}


void DFS1(const graph & curr_graph, int from, vector<int> & result, vector<char> & colors ,bool & is_cycle_exist,
          int & number_of_cycles)
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
            if (colors[curr_graph.get_next(curr)[i]] == 0)
            {
                colors[curr_graph.get_next(curr)[i]] = 1;
                tmp_s.push(curr_graph.get_next(curr)[i]);
                is_need_to_go = false;
                break;
            }
        }
        if (is_need_to_go)
        {
            result.push_back(curr);
            colors[curr] = 2;
            tmp_s.pop();
        }
    }
}

vector<int> points (vector<vector<int>> components, const graph & curr_graph)
{
    vector<int> res (curr_graph.vertex());
    for (int i = 0 ; i < components.size(); i ++)
    {
        for (int j = 0; j < components[i].size(); j++)
        {
            res[components[i][j]] = i;
        }
    }
    return res;
}
int bridges (const graph & curr_graph,const graph & reversed_graph, vector<int> & components2,
        vector<vector<int>> & components)
        {
    int stocks = 0;
    int sources = 0;
    int st = 0;
    int so = 0;
    for (int i = 0; i < components.size(); i++)
    {
        for (int j = 0; j < components[i].size(); j++)
        {
            for (int k = 0; k < curr_graph.get_next(components[i][j]).size(); k++)
            {
                if (i != components2[curr_graph.get_next(components[i][j])[k]])
                {
                    st++;
                    break;
                }
            }
        }

        if (st == 0)
            stocks++;
            // std::cout << 'a'<< i;}
            st = 0;
            //std::cout <<'k';

            for (int j = 0; j < components[i].size(); j++) {
                for (int k = 0; k < reversed_graph.get_next(components[i][j]).size(); k++) {
                    if (components2[reversed_graph.get_next(components[i][j])[k]] != i) {
                        so++;
                        break;
                    }
                }
            }
            if (so == 0)
                sources++;
            so = 0;
        }


            return std::max(sources, stocks);
}
int main()
{
    int number_of_points;
    int number_of_edges;
    //vector<int> components;
    std::cin >> number_of_points;
    std::cin >> number_of_edges;
    graph curr_graph(number_of_points);
    graph reversed_graph(number_of_points);
    int from;
    int out;
    for (int i = 0; i < number_of_edges; i++)
    {
        std::cin >> from;
        std::cin >> out;
        curr_graph.add_edge(from - 1,out - 1);
        reversed_graph.add_edge(out - 1,from - 1);
    }
    vector<char> colors (number_of_points, 0);
    vector<int> result;
    bool ice = true;
    int noc = 0;
    for (int i = 0; i < number_of_points; i++)
    {
        if (colors[i] == 0)
        {
            DFS1(curr_graph, i, result, colors, ice, noc);
            noc ++;
        }
    }
    vector<vector<int>> components;
    vector<char> colors2(number_of_points, 0);
    vector<int> result2;
    bool ice2 = true;
    int counter = 0;
    for (int i = 0; i < number_of_points; i++)
    {
        if (colors2[result[number_of_points - 1 - i]] == 0 && result2.size() <= result.size())
        {
            DFS2(reversed_graph, result[number_of_points - 1 - i], result2, colors2, ice2,components);
            ice2 = true;
            counter++;
        }
    }
    vector<int> components2 = points(components, curr_graph);
    int roads = bridges(curr_graph, reversed_graph, components2,components);
    if (components.size() == 1)
    {
      std::cout << 0;
    }
    else
       std::cout << roads;
}
