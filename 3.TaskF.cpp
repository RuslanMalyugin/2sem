#include <iostream>
#include <vector>
#include <string>
using std::vector;
const int BIG = 100000000;
struct graph {
    vector<vector<int>> matrix;
    int size;
    graph(int s) {
        matrix = vector<vector<int>>(s, vector<int>(s, 0));
        size = s;
    }

    void add_edge(int from, int to) {
        matrix[from][to] = 1;
    }

};

vector<int> seating (graph & current_graph) {
    vector<int> indexes[current_graph.size];
    for(int i = 0; i < current_graph.size; i++) {
        indexes[i].assign(1, i);
    }
    vector<int> result;
    int max_cost = BIG;
    vector<int> max_indexes;
    vector<bool> exist (current_graph.size, true);
    vector<bool> belonging;
    int previous = 0;
    for (int k = 0; k < current_graph.size - 1; k++) {
        max_indexes = vector<int>(current_graph.size, 0);
        belonging = vector<bool>(current_graph.size, false);
        for (int j = 0; j < current_graph.size - k; j++) {
            int select = -1;
            for (int i = 0; i < current_graph.size; i++) {
                if(exist[i] && !belonging[i]  && (select == -1 || max_indexes[i] > max_indexes[select])) {
                    select = i;
                }
            }
            if (j == current_graph.size - k - 1) {
                if (max_indexes[select] < max_cost) {
                    max_cost = max_indexes[select];
                    result = indexes[select];
                }
                indexes[previous].insert(indexes[previous].end(), indexes[select].begin(), indexes[select].end());
                for (int i = 0 ; i < current_graph.size; i++) {
                    current_graph.matrix[previous][i] = current_graph.matrix[i][previous] += current_graph.matrix[select][i];
                }
                exist[select] = false;
            }
            else {
                belonging[select] = true;
                for(int i = 0; i < current_graph.size; i ++) {
                    max_indexes[i] += current_graph.matrix[select][i];
                }
                previous = select;
            }
        }
    }
    return result;
}

int main() {
    int size;
    std::cin >> size;
    graph current(size);
    for (int i = 0; i < size; i++) {
        std::string a;
        std::cin >> a;
        for (int j = 0; j < a.size(); j++) {
            if (a[j] == '1')
                current.add_edge(j,i);
        }
    }
    vector<int> first;
    vector<int> second;
    vector<bool> tmp(size, false);
    vector<int> tmp2 = seating(current);
    for(int i = 0; i < tmp2.size(); i++) {
        tmp[tmp2[i]] = true;
    }
    for(int i = 0; i < size; i++){
        if (tmp[i])
            first.push_back(i);
        else
            second.push_back(i);
    }
    
    for(int i = 0; i < first.size(); i++)
        std::cout << first[i] + 1 << " ";
    std::cout << '\n';
    for(int i = 0; i < second.size(); i++)
        std::cout << second[i] + 1 << " ";
    return 0;
}
