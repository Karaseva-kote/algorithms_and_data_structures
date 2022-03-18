#include <bits/stdc++.h>

using namespace std;

struct Node {
    int key, prior;
    int size1;
    Node *left, *right;
    Node(int x) {
        key = x;
        prior = rand();
        size1 = 1;
        left = NULL;
        right = NULL;
    }
    Node() {
        key = NULL;
        prior = rand();
        size1 = 1;
        left = NULL;
        right = NULL;
    }
};

Node *ROOT;

int getSize(Node *p) {
    if (p != NULL)
         return p->size1;
    return 0;
}

void refreshSize(Node *&p) {
    p->size1 = 1 + getSize(p->left) + getSize(p->right);
}

void Merge (Node *left, Node *right, Node *&root) {
    if (left == NULL) {
        root = right;
        return;
    }
    if (right == NULL) {
        root = left;
        return;
    }
    if (left->prior > right->prior) {
        Merge(left->right, right, left->right);
        root = left;
    } else {
        Merge(left, right->left, right->left);
        root = right;
    }
    refreshSize(root);
    return;
}

void Split (int x, Node *root, Node *&left, Node *&right) {
    if (!root) {
        left = NULL;
        right = NULL;
        return;
    }
    if (root->key >= x) {
        Split(x, root->left, left, root->left);
        right = root;
    } else {
        Split(x, root->right, root->right, right);
        left = root;
    }
    refreshSize(root);
    return;
}

int searchMAX (int M, Node *tree) {
    if (tree == NULL)
        return 0;
    if (getSize(tree->right) + 1 == M)
        return tree->key;
    if (getSize(tree->right) + 1 < M)
        return searchMAX(M - getSize(tree->right) - 1, tree->left);
    if (getSize(tree->right) + 1 > M)
        return searchMAX(M, tree->right);
}


int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        int x;
        cin >> s >> x;
        if (s == "+1" || s == "1") {
            Node *Y = new Node(x), *L = new Node(), *R = new Node();
            Split(x, ROOT, L, R);
            Merge(L, Y, L);
            Merge(L, R, ROOT);
        }
        if (s == "-1") {
            Node *Y = new Node(), *L = new Node(), *R = new Node();
            Split(x, ROOT, L, R);
            Split(x + 1, R, Y, R);
            Merge(L, R, ROOT);
        }
        if (s == "0") {
            cout << searchMAX(x, ROOT) << endl;
        }
    }
    return 0;
}
