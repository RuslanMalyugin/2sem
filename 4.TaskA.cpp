#include <iostream>
#include <vector>
#include <cmath>

int BIG = 1000000000;
using std::vector;

vector<vector<int> > make_sparse_table(const vector<int> &array, vector<vector<int> > &indexes) {
    vector<vector<int> > tmp_table(2 * array.size(), vector<int>(int(std::log2(array.size())) + 1, BIG));
    for (int j = 0; j < tmp_table[0].size(); j++) {
        for (int i = 0; i < array.size(); i++) {
            if (j == 0) {
                tmp_table[i][j] = array[i];
                indexes[i][j] = i;
            } else {
                tmp_table[i][j] = std::min(tmp_table[i][j - 1], tmp_table[i + pow(2, j - 1)][j - 1]);
                if (tmp_table[i][j - 1] >= tmp_table[i + pow(2, j - 1)][j - 1])
                    indexes[i][j] = indexes[i + pow(2, j - 1)][j - 1];
                else
                    indexes[i][j] = indexes[i][j - 1];
            }
        }
    }
    return tmp_table;
}

int second_statistic(const vector<int> &array, const vector<vector<int> > &sparse_table,
                     const vector<vector<int> > &indexes, int left, int right) {
    if (right - left == 1)
        return std::max(array[right], array[left]);
    int dist_log = int(log2(right - left));
    int index = 0;
    int minimal = std::min(sparse_table[left][dist_log], sparse_table[right - pow(2, dist_log) + 1][dist_log]);
    if (minimal == sparse_table[left][dist_log])
        index = indexes[left][dist_log];
    else
        index = indexes[right - pow(2, dist_log) + 1][dist_log];
    int log_min2 = std::max(int(log2(index - 1 - left)), 0);
    int log_min1 = std::max(int(log2(right - index - 1)), 0);
    if (left == index) {
        int dist_log2 = std::max(int(log2(right - left - 1)), 0);
        return std::min(sparse_table[left + 1][dist_log2], sparse_table[1 + right - pow(2, dist_log2)][dist_log2]);
    }
    if (right == index) {
        int dist_log2 = std::max(int(log2(right - left - 1)), 0);
        return std::min(sparse_table[left][dist_log2], sparse_table[1 + right - 1 - pow(2, dist_log2)][dist_log2]);
    }
    int min2 = std::min(sparse_table[left][log_min2],
                        sparse_table[std::max(left, int(1 + index - 1 - pow(2, log_min2)))][log_min2]);
    if (index - left == 1)
        min2 = std::max(array[index], array[left]);
    int min1 = std::min(sparse_table[std::min(index + 1, int(right - pow(2, log_min1)))][log_min1],
                        sparse_table[1 + right - pow(2, log_min1)][log_min1]);
    if (right - index == 1)
        min1 = std::max(array[index], array[right]);
    return std::min(min1, min2);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<int> array(n);
    for (int i = 0; i < n; i++) {
        std::cin >> array[i];
    }
    vector<int> requests(2 * m);
    int first, second;
    vector<vector<int> > indexes(2 * array.size(), vector<int>(int(std::log2(array.size())) + 1));

    vector<vector<int> > sparse_table = make_sparse_table(array, indexes);
    for (int i = 0; i < 2 * m; i += 2) {
        std::cin >> first >> second;
        requests[i] = first - 1;
        requests[i + 1] = second - 1;
    }
    for (int i = 0; i < 2 * m; i += 2) {
        std::cout << second_statistic(array, sparse_table, indexes, requests[i], requests[i + 1]);
        std::cout << '\n';
    }
    return 0;
}
