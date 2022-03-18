#include <bits/stdc++.h>

using namespace std;

struct Node {
    int key, high;
    Node *left, *right;
    Node(int x) {
        key = x;
        high = 1;
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
    cout << '/' << r->key << " " << r->high << '/';
    print(r->right);
}

int getHigh(Node *r) {
    if (r == NULL) {
        return 0;
    }
    return r->high;
}

int getKey(Node *r) {
    if (r == NULL) {
        return 0;
    }
    return r->key;
}

void printSmall(Node *r) {
    if (r == NULL) {
        cout << "null" << endl;
    }
    cout << getKey(r->left) << " " << getKey(r) << " " << getKey(r->right) << endl;
}

void refreshHigh(Node *r) {
    if (r == NULL) {
        return;
    }
    r->high = max(getHigh(r->left), getHigh(r->right)) + 1;
}

int minimum(Node *r) {
    if (r->left == NULL) {
        return r->key;
    }
    return minimum(r->left);
}

void rr(Node *&current) {
    Node *b = current->left->right;
    current->left->right = current;
    current = current->left;
    current->right->left = b;
    refreshHigh(current->right);
    refreshHigh(current);
}

void rl(Node *&current) {
    Node *b = current->right->left;
    current->right->left = current;
    current = current->right;
    current->left->right = b;
    refreshHigh(current->left);
    refreshHigh(current);
}

void round(Node *&current) {
    if (getHigh(current->left) > (getHigh(current->right) + 1)) {
        if (getHigh(current->left->left) >= getHigh(current->left->right)){ //small right
            rr(current);
        } else {
            rl(current->left);
            rr(current);
        }
        return;
    }
    if ((getHigh(current->left) + 1) < getHigh(current->right)) {
        if (getHigh(current->right->right) >= getHigh(current->right->left)){
            rl(current);
        } else {
            rr(current->right);
            rl(current);
        }
        return;
    }
}

void insert1(int x, Node *&current) {
    if (current == NULL) {
        current = new Node(x);
        return;
    }
    if (x < current->key) {
        insert1(x, current->left);
        refreshHigh(current);
        round(current);
        return;
    }
    if (x > current->key) {
        insert1(x, current->right);
        refreshHigh(current);
        round(current);
        return;
    }
}

void delete1(int x, Node *&current) {
    if (current == NULL) {
        return;
    }
    if (x < current->key) {
        delete1(x, current->left);
        refreshHigh(current);
        round(current);
        return;
    }
    if (x > current->key) {
        delete1(x, current->right);
        refreshHigh(current);
        round(current);
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
        refreshHigh(current);
        round(current);
        return;
    }
}

bool exists(int x, Node *current) {
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
