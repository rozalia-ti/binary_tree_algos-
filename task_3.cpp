#include <bits/stdc++.h>

using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int value) {
        key = value;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

int getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

void updateHeight(Node* node) {
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

int getBalance(Node* node) {
    return getHeight(node->right) - getHeight(node->left);
}

Node* rotateLeft(Node* node) {
    Node* rightNode = node->right;
    node->right = rightNode->left;
    rightNode->left = node;

    updateHeight(node);
    updateHeight(rightNode);

    return rightNode;
}

Node* rotateRight(Node* node) {
    Node* leftNode = node->left;
    node->left = leftNode->right;
    leftNode->right = node;

    updateHeight(node);
    updateHeight(leftNode);

    return leftNode;
}

Node* balance(Node* node) {
    updateHeight(node);

    if (getBalance(node) == 2) {
        if (getBalance(node->right) < 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    if (getBalance(node) == -2) {
        if (getBalance(node->left) > 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    return node;
}

Node* add(Node* node, int x) {
    if (node == nullptr) {
        return new Node(x);
    }

    if (x < node->key) {
        node->left = add(node->left, x);
    } else if (x > node->key) {
        node->right = add(node->right, x);
    } else {
        return node;
    }

    return balance(node);
}

bool exists(Node* node, int x) {
    while (node != nullptr) {
        if (node->key == x) {
            return true;
        }

        if (x < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return false;
}

void print(Node* node, bool& first) {
    if (node == nullptr) {
        return;
    }

    if (!first) {
        cout << ' ';
    }

    cout << node->key;
    first = false;

    print(node->left, first);
    print(node->right, first);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    Node* root = nullptr;

    while (q--) {
        string command;
        cin >> command;

        if (command == "add") {
            int x;
            cin >> x;
            root = add(root, x);
        } else if (command == "exists") {
            int x;
            cin >> x;
            cout << (exists(root, x) ? "YES" : "NO") << '\n';
        } else if (command == "root") {
            if (root == nullptr) {
                cout << "Empty\n";
            } else {
                cout << root->key << '\n';
            }
        } else if (command == "height") {
            cout << getHeight(root) << '\n';
        } else if (command == "print") {
            if (root == nullptr) {
                cout << "Empty\n";
            } else {
                bool first = true;
                print(root, first);
                cout << '\n';
            }
        }
    }

    return 0;
}