#include <bits/stdc++.h>

using namespace std;

struct Node {
    int key;
    Node *left, *right;
    Node(int x) {
        key = x;
        left = NULL;
        right = NULL;
    }
};

Node *root;

void print(Node *r) {
    if (r == NULL) {
        return;
    }
    print(r->left);
    cout << '/' << r->key << '/';
    print(r->right);
}

int minimum(Node *r) {
    if (r->left == NULL) {
        return r->key;
    }
    return minimum(r->left);
}

void insert1(int x, Node *&current) {
    if (current == NULL) {
        current = new Node(x);
        return;
    }
    if (x < current->key) {
        insert1(x, current->left);
        return;
    }
    if (x > current->key) {
        insert1(x, current->right);
        return;
    }
}

void delete1(int x, Node *&current) {
    if (current == NULL) {
        return;
    }
    if (x < current->key) {
        delete1(x, current->left);
        return;
    }
    if (x > current->key) {
        delete1(x, current->right);
        return;
    }
    if (current->left == NULL) {
        if (current->right == NULL) {
            current = NULL;
            return;
        } else {
            current = current->right;
            return;
        }
    }
    if (current->right == NULL) {
        current = current->left;
        return;
    } else {
        current->key = minimum(current->right);
        delete1(current->key, current->right);
        return;
    }
}

bool exists(int x, Node *&current) {
    if (current == NULL) {
        return 0;
    }
    if (x < current->key) {
        return exists(x, current->left);
    }
    if (x > current->key) {
        return exists(x, current->right);
    }
    return 1;
}

int next(int x) {
    Node *current = root, *parent = NULL;
    while (current != NULL) {
        if (current->key > x) {
            parent = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    if (parent == NULL) {
        return NULL;
    }
    return parent->key;
}

int prev(int x) {
    Node *current = root, *parent = NULL;
    while (current != NULL) {
        if (current->key < x) {
            parent = current;
            current = current->right;
        } else {
            current = current->left;
        }
    }
    if (parent == NULL) {
        return NULL;
    }
    return parent->key;
}

int main()
{
    string command;
    while(cin >> command) {
        int x;
        cin >> x;
        if (command == "insert"){
            insert1(x, root);
        }
        if (command == "delete"){
            delete1(x, root);
        }
        if (command == "prev"){
            int res = prev(x);
            if (res == NULL) {
                cout << "none" << endl;
            } else {
                cout << res << endl;
            }
        }
        if (command == "next"){
            int res = next(x);
            if (res == NULL) {
                cout << "none" << endl;
            } else {
                cout << res << endl;
            }
        }
        if (command == "exists"){
            cout << boolalpha;
            cout << exists(x, root) << endl;
        }
        print(root);
        cout << endl;
    }
    return 0;
}
