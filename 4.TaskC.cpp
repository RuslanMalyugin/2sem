#include <iostream>
#include <vector>
#include <cmath>

using std::vector;
int BIG = 10000000;

void push(vector<int> &min_items, vector<int> &items, int current) {
    if (items[current] != BIG) {
        items[current * 2 + 1] = items[current];
        items[current * 2] = items[current * 2 + 1];
        min_items[current * 2 + 1] = items[current];
        min_items[current * 2] = min_items[current * 2 + 1];
        items[current] = BIG;
    }
}

void make_tree(const vector<int> &array, vector<int> &min_items, vector<int> &items, int current, int left, int right) {
    if (left > right)
        return;
    if (left == right) {
        items[current] = array[left];
        min_items[current] = array[left];
    } else {
        int mid = (left + right) / 2;
        make_tree(array, min_items, items, current * 2, left, mid);
        make_tree(array, min_items, items, current * 2 + 1, mid + 1, right);
        min_items[current] = std::min(min_items[current * 2], min_items[2 * current + 1]);
    }
}

void change_items(vector<int> &min_items, vector<int> &items, int current, int left, int right, int curr_left,
                  int curr_right, int change) {
    if (curr_left > curr_right)
        return;
    if (left == curr_left && right == curr_right) {
        min_items[current] = change;
        items[current] = change;
        return;
    }

    else {
        push(min_items, items, current);
        int mid = (left + right) / 2;
        change_items(min_items, items, current * 2, left, mid, curr_left, std::min(curr_right, mid), change);
        change_items(min_items, items, current * 2 + 1, mid + 1, right, std::max(curr_left, mid + 1), curr_right, change);
    }
    min_items[current] = std::min(min_items[2 * current], min_items[2 * current + 1]);
}

int count_min(vector<int> &min_items,  vector<int> &items, int current, int left, int right, int curr_left, int curr_right) {
    if (left == curr_left && right == curr_right) {
        return min_items[current];
    }
    if (curr_left > curr_right)
        return BIG;
    push(min_items, items, current);
    int mid = (left + right) / 2;
    return std::min(count_min(min_items, items, current * 2, left, mid, curr_left, std::min(mid, curr_right)),
                    count_min(min_items, items , current * 2 + 1, mid + 1, right, std::max(curr_left, mid + 1), curr_right));
}

int main() {
    int n;
    std::cin >> n;
    n ++;
    vector<int> array(n, BIG);
    vector<int> min_items(4 * n, BIG);
    vector<int> items(4 * n, BIG);
    int R, G, B;
    for (int i = 0; i < n - 1; i++) {
        std::cin >> R >> G >> B;
        array[i] = R + G + B;
    }
    make_tree(array,min_items, items, 1, 0, n - 2);
    int changes;
    std::cin >> changes;
    int from, to ;
    int minfrom, minto;
    vector<int> bad_attempts;
    for (int i = 0; i < changes; i++) {
        std::cin >> from >> to >> R >> G >> B >> minfrom >> minto;
        change_items(min_items, items,  1, 0, n - 2, from, to, R + G + B);
        std::cout << '\n' << count_min(min_items, items, 1, 0, n - 2, minfrom, minto);
    }
    return 0;
}

