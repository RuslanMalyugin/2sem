#include <iostream>
#include <vector>
#include <string>
#include <bitset>
using std::vector;
using std::bitset;
class graph {
public:
    unsigned long long** edges;
    int size = 0;

    graph(int size_) {
        unsigned long long** edges_tmp;
        size = size_;
        edges_tmp = new unsigned long long * [size];
        for (int i = 0; i < size; i++) {
            edges_tmp[i] = new unsigned long long[size / 64 + 1];
        }
        for(int i = 0; i < size; i++) {
            for (int j = 0; j < size / 64 + 1; j++) {
                //std::cout << 1;
                edges_tmp[i][j] = 0;
            }
        }
        edges =  edges_tmp;


    }
    void add_edge(int from, int to) {
        std::cout << "a";
        edges[from][to / 64] += (1 << (to % 64 - 1));
    }

    ~graph() {
        for (int i = 0; i < size; i ++)
            delete[] edges[i];
    }

    int vortex () const {
        return size;
    }
    unsigned long long ** & get_graph () {
        return edges;
    }

};

void solve (bitset<1000> * curr_graph, int size) {
    for (int k = 0; k < size; k ++) {
        for (int i = 0; i < size; i++) {
            if (curr_graph[i][k] == true) {
                curr_graph[i] = curr_graph[k] | curr_graph[i];
            }
        }
    }
}

int main() {
    int size;
    std::cin >> size;
    std::string bit;
    auto *pseudo_graph = new bitset<1000>[size];
    for (int j = 0; j < size; j++) {
        std::cin >> bit;
        for (int i = 0; i < size; i++) {
            pseudo_graph[j][i] = bit[i] - '0';
        }
    }



    solve(pseudo_graph, size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << pseudo_graph[i][j];
        }
        std::cout << '\n';
    }





    return 0;
}
