#include <iostream>
#include <vector>
#include <cmath>

using std::vector;
int BIG = 10000000;

void make_tree(const vector<int> &array, vector<int> &max_items, vector<int> &items, int current, int left, int right) {
    if (left == right) {
        //items[current] = array[left];
        max_items[current] = array[left];
    } else {
        int mid = (left + right) / 2;
        make_tree(array, max_items, items, current * 2, left, mid);
        make_tree(array, max_items, items, current * 2 + 1, mid + 1, right);
        //items[current] = std::max(items[current * 2], items[current * 2 + 1]);
        max_items[current] = std::max(max_items[current * 2], max_items[2 * current + 1]);
    }
}

void change_items(vector<int> &max_items, vector<int> &items, int current, int left, int right, int curr_left,
                  int curr_right, int change) {
    if (curr_left > curr_right)
        return;
    if (left == curr_left && right == curr_right) {
        max_items[current] += change;
        items[current] += change;
        return;
    }
    int mid = (left + right) / 2;
    if (curr_right <= mid) {
        change_items(max_items, items, 2 * current, left, mid, curr_left, curr_right, change);
        //max_items[current] = std::max(max_items[2 * current], max_items[2 * current + 1]) + items[current];
    }
    else if (curr_left > mid) {
        change_items(max_items, items, 2 * current + 1, mid + 1, right, curr_left, curr_right, change);
       // max_items[current] = std::max(max_items[2 * current], max_items[2 * current + 1]) + items[current];
    } else {
        change_items(max_items, items, 2 * current, left, mid, curr_left, mid, change);
        change_items(max_items, items, 2 * current + 1, mid + 1, right, mid + 1, curr_right, change);
      //  max_items[current] = std::max(max_items[2 * current], max_items[2 * current + 1]) + items[current];
    }
    max_items[current] = std::max(max_items[2 * current], max_items[2 * current + 1]) + items[current];
}

//int count_max_item(vector<int> &max_items, vector<int> &items, int current, int left, int right, int curr_left,
//                   int curr_right) {
//    if (left == curr_left && right == curr_right) {
//        return max_items[current];
//    }
//    int mid = (left + right) / 2;
//    if (curr_right <= mid) {
//        return count_max_item(max_items, items, 2 * current, left, mid, curr_left, curr_right) + items[current];
//    }
//    if (curr_left >= mid ) {
//        return count_max_item(max_items, items, 2 * current + 1, mid + 1, right, curr_left, curr_right) + items[current];
//    } else
//        return std::max(
//                count_max_item(max_items, items, 2 * current, left, mid, curr_left, mid),
//                count_max_item(max_items, items, 2 * current + 1, mid + 1, right, mid + 1, curr_right)) + items[current];
//}

int main() {
    int n;
    std::cin >> n;
    vector<int> array(n, 0);
    vector<int> max_items(4 * n, 0);
    vector<int> items(4 * n, 0);
    for (int i = 0; i < n - 1; i++) {
        std::cin >> array[i];
    }
    make_tree(array, max_items, items, 1, 0, n - 2);
//    for (int i = 0; i < max_items.size(); i++) {
//        std::cout << i << ":" << max_items[i] << '\n';
//    }
//    for (int i = 0; i < items.size(); i++) {
//        std::cout << i << ":" << items[i] << '\n';
//    }

    vector<int> bad_attempts;
    int limit, requests_counter;
    std::cin >> limit >> requests_counter;
    int from, to, amount;
    for (int i = 0; i < requests_counter; i++) {
        std::cin >> from >> to >> amount;
        change_items(max_items, items, 1, 0, n - 2, from , to - 1, amount);
        //std::cout << "A" << max_items[1] << "A" << '\n';
        if (limit < max_items[1]) {
            bad_attempts.emplace_back(i);
            change_items(max_items, items, 1, 0, n - 2, from, to - 1, -1 * amount);
        }
    }
    for (int i = 0; i < bad_attempts.size(); i++)
        std::cout << bad_attempts[i] << '\n';

    return 0;
}
