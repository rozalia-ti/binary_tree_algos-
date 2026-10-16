#include <bits/stdc++.h>

using namespace std;

struct Node {
    long long key;
    Node* left;
    Node* right;

    Node(long long value) {
        key = value;
        left = nullptr;
        right = nullptr;
    }
};

Node* insertNode(Node* root, long long x) {
    if (root == nullptr) {
        return new Node(x);
    }

    if (x < root->key) {
        root->left = insertNode(root->left, x);
    } else if (x > root->key) {
        root->right = insertNode(root->right, x);
    }

    return root;
}

Node* removeNode(Node* root, long long x) {
    if (root == nullptr) {
        return nullptr;
    }

    if (x < root->key) {
        root->left = removeNode(root->left, x);
    } else if (x > root->key) {
        root->right = removeNode(root->right, x);
    } else {
        if (root->left == nullptr) {
            Node* result = root->right;
            delete root;
            return result;
        }

        if (root->right == nullptr) {
            Node* result = root->left;
            delete root;
            return result;
        }

        Node* current = root->right;
        while (current->left != nullptr) {
            current = current->left;
        }

        root->key = current->key;
        root->right = removeNode(root->right, current->key);
    }

    return root;
}

bool contains(Node* root, long long x) {
    while (root != nullptr) {
        if (root->key == x) {
            return true;
        }

        if (x < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }

    return false;
}

int getHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

void printTree(Node* root, bool& first) {
    if (root == nullptr) {
        return;
    }

    if (!first) {
        cout << ' ';
    }

    cout << root->key;
    first = false;

    printTree(root->left, first);
    printTree(root->right, first);
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
            long long x;
            cin >> x;
            root = insertNode(root, x);
        } else if (command == "del") {
            long long x;
            cin >> x;
            root = removeNode(root, x);
        } else if (command == "exists") {
            long long x;
            cin >> x;
            cout << (contains(root, x) ? "YES" : "NO") << '\n';
        } else if (command == "height") {
            cout << getHeight(root) << '\n';
        } else if (command == "print") {
            if (root == nullptr) {
                cout << "Empty\n";
            } else {
                bool first = true;
                printTree(root, first);
                cout << '\n';
            }
        }
    }

    return 0;
}