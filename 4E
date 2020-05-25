#include <iostream>
#include <cassert>
#include <stack>
#include <string>
#include <random>
#include <ctime>

using std::stack;
using std::string;

template<class T>
bool isbigger(const T &leftElement, const T &rightElement) {
    return leftElement > rightElement;
}

template<class Info>
struct DecNode {
    DecNode(int element, Info data_, int currentPriority) {
        priority = currentPriority;
        count = element;
        data = data_;
        left = nullptr;
        right = nullptr;
    }

    const DecNode &operator=(const DecNode<Info> &node1) {
        priority = node1.priority;
        count = node1.count;
        left = node1.left;
        right = node1.right;
        data = node1.right;
        return *this;
    }

    DecNode() {
        count = 1;
        data;
        priority = 0;
        left = nullptr;
        right = nullptr;
    }

    ~DecNode() = default;

    int count;
    Info data;
    int priority;
    DecNode *left;
    DecNode *right;
};

template<class Info>
struct DecartTree {
    DecartTree() {
        root = nullptr;
    }

    DecNode<Info> *root;

    int counting(DecNode<Info> *current) {
        if (current)
            return current->count;
        else
            return 0;
    }

    void update_counts(DecNode<Info> *current) {
        if (current) {
            current->count = 1 + counting(current->left) + counting(current->right);
        }
    }

    void split(DecNode<Info> *start, DecNode<Info> *&new_left, DecNode<Info> *&new_right, int key, int delta = 0) {
        if (!start) {
            new_left = nullptr;
            new_right = nullptr;
            return;
        } else {
            int current_key = delta + counting(start->left);
            if (key <= current_key) {
                split(start->left, new_left, start->left, key, delta);
                new_right = start;
            } else {
                split(start->right, start->right, new_right, key, delta + 1 + counting(start->left));
                new_left = start;
            }
            update_counts(start);
        }
    }

    void merge(DecNode<Info> * & start, DecNode<Info> *old_left, DecNode<Info> *old_right) {
        if (!old_left) {
            start = old_right;
            return;
        }
        if (!old_right) {
            start = old_left;
            return;
        }
        else if (old_left->priority > old_right->priority) {
            merge(old_left->right, old_left->right, old_right);
            start = old_left;
        } else {
            merge(old_right->left, old_left, old_right->left);
            start = old_right;
        }
        update_counts(start);
    }

    void add(DecNode<Info> *new_node, int pos) {
        if (root == nullptr) {
            root = new_node;
            return;
        }
        DecNode<Info> *new_left = nullptr;
        DecNode<Info> *new_right = nullptr;
        split(root, new_left, new_right, pos);
//        merge(new_right, new_node, new_right);
//        merge(root, new_left, new_right);
        merge(new_left, new_left, new_node);
        merge(root, new_left, new_right);
        //update_counts(root);
    }

    void remove_on_distance(int first_index, int second_index) {
        for (int i = first_index; i <= second_index; i++) {
            DecNode<Info> *new_left1 = nullptr;
            DecNode<Info> *new_right1 = nullptr;
            DecNode<Info> *deleted = nullptr;
            split(root, new_left1, new_right1, i);
            split(new_right1, deleted, new_right1, 1);
            merge(root,new_left1, new_right1);
            delete(deleted);
        }
    }

    Info get_value(DecNode<Info> *current, int index) {
        int tmp_index = counting(current->left);
        if (index < tmp_index) {
            return get_value(current->left, index);
        } else if (index == tmp_index) {
            return current->data;
        } else {
            return get_value(current->right, index - tmp_index - 1);
        }
    }
};


int main() {

    int number;
    std::cin >> number;
    DecartTree<string> Tree;
    string command;
    string data;
    int index1, index2;
    std::vector<string> output;
    for (int i = 0; i < number; i ++) {
        std::cin >> command;
        if (command == "+") {
            std::cin >> index1;
            std::cin >> data;
            Tree.add(new DecNode<string> (1, data, rand()), index1);
        }
        if (command == "-") {
            std::cin >> index1 >> index2;
            Tree.remove_on_distance(index1, index2);
        }
        if (command == "?") {
            std::cin >> index1;
            output.push_back(Tree.get_value(Tree.root, index1));
        }
    }

    for (int i = 0 ; i < output.size(); i++) {
        std::cout << output[i] << '\n';
    }

    return 0;
}
