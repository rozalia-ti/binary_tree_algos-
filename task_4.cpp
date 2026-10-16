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
    return node == nullptr ? 0 : node->height;
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

Node* findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}

Node* eraseNode(Node* node, int x) {
    if (node == nullptr) {
        return nullptr;
    }

    if (x < node->key) {
        node->left = eraseNode(node->left, x);
    } else if (x > node->key) {
        node->right = eraseNode(node->right, x);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            Node* child = node->left != nullptr ? node->left : node->right;
            delete node;
            return child;
        }

        Node* nextNode = findMin(node->right);
        node->key = nextNode->key;
        node->right = eraseNode(node->right, nextNode->key);
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

bool nextValue(Node* node, int x, int& result) {
    bool found = false;

    while (node != nullptr) {
        if (node->key >= x) {
            result = node->key;
            found = true;
            node = node->left;
        } else {
            node = node->right;
        }
    }

    return found;
}

bool prevValue(Node* node, int x, int& result) {
    bool found = false;

    while (node != nullptr) {
        if (node->key <= x) {
            result = node->key;
            found = true;
            node = node->right;
        } else {
            node = node->left;
        }
    }

    return found;
}

void printPreorder(Node* node, bool& first) {
    if (node == nullptr) {
        return;
    }

    if (!first) {
        cout << ' ';
    }

    cout << node->key;
    first = false;

    printPreorder(node->left, first);
    printPreorder(node->right, first);
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
        } else if (command == "del") {
            int x;
            cin >> x;
            root = eraseNode(root, x);
        } else if (command == "exists") {
            int x;
            cin >> x;
            cout << (exists(root, x) ? "YES" : "NO") << '\n';
        } else if (command == "next") {
            int x;
            int result;
            cin >> x;

            if (nextValue(root, x, result)) {
                cout << result << '\n';
            } else {
                cout << "None\n";
            }
        } else if (command == "prev") {
            int x;
            int result;
            cin >> x;

            if (prevValue(root, x, result)) {
                cout << result << '\n';
            } else {
                cout << "None\n";
            }
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
                printPreorder(root, first);
                cout << '\n';
            }
        }
    }

    return 0;
}