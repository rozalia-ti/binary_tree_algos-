#include <bits/stdc++.h>

using namespace std;

struct Node {
    long long key;
    Node* left;
    Node* right;
    Node* parent;

    Node(long long value) {
        key = value;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

Node* root = nullptr;

void insertNode(long long x) {
    Node* node = new Node(x);

    if (root == nullptr) {
        root = node;
        return;
    }

    Node* current = root;

    while (true) {
        if (x < current->key) {
            if (current->left == nullptr) {
                current->left = node;
                node->parent = current;
                return;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = node;
                node->parent = current;
                return;
            }
            current = current->right;
        }
    }
}

void leftRotate(Node* a) {
    Node* b = a->right;
    Node* parent = a->parent;

    a->right = b->left;
    if (b->left != nullptr) {
        b->left->parent = a;
    }

    b->left = a;
    a->parent = b;
    b->parent = parent;

    if (parent == nullptr) {
        root = b;
    } else if (parent->left == a) {
        parent->left = b;
    } else {
        parent->right = b;
    }
}

void rightRotate(Node* a) {
    Node* b = a->left;
    Node* parent = a->parent;

    a->left = b->right;
    if (b->right != nullptr) {
        b->right->parent = a;
    }

    b->right = a;
    a->parent = b;
    b->parent = parent;

    if (parent == nullptr) {
        root = b;
    } else if (parent->left == a) {
        parent->left = b;
    } else {
        parent->right = b;
    }
}

void preorder(Node* node, vector<long long>& result) {
    if (node == nullptr) {
        return;
    }

    result.push_back(node->key);
    preorder(node->left, result);
    preorder(node->right, result);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_map<long long, Node*> nodes;

    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        insertNode(x);

        Node* current = root;
        while (current->key != x) {
            if (x < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        nodes[x] = current;
    }

    int m;
    cin >> m;

    while (m--) {
        string command;
        long long x;
        cin >> command >> x;

        if (command == "left") {
            leftRotate(nodes[x]);
        } else {
            rightRotate(nodes[x]);
        }

        vector<long long> result;
        preorder(root, result);

        for (int i = 0; i < (int)result.size(); i++) {
            if (i > 0) {
                cout << ' ';
            }
            cout << result[i];
        }

        cout << '\n';
    }

    return 0;
}