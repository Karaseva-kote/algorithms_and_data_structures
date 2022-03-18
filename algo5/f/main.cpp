#include <bits/stdc++.h>

using namespace std;

struct Node {
    int prior;
    int Size;
    int value;
    Node *left, *right;
    Node(int x) {
        prior = rand();
        Size = 1;
        value = x;
        left = NULL;
        right = NULL;
    }
    Node() {
        prior = rand();
        Size = 1;
        value = NULL;
        left = NULL;
        right = NULL;
    }
};

Node *root;

int getSize(Node *p) {
    if (p != NULL)
         return p->Size;
    return 0;
}

void refreshSize(Node *&p) {
    p->Size = 1 + getSize(p->left) + getSize(p->right);
}

void print (Node *y) {
    if (y == NULL) {
        return;
    }
    print(y->left);
    cout << y->value << ' ';
    print(y->right);
}

void Split (int pos, Node *rt, Node *&l, Node *&r, int shft) {
    if (rt == NULL) {
        l = NULL;
        r = NULL;
        return;
    }
    int key = shft + getSize(rt->left) + 1;
    if (key <= pos) {
        Split(pos, rt->right, rt->right, r, shft + getSize(rt->left) + 1);
        l = rt;
    } else {
        Split(pos, rt->left, l, rt->left, shft);
        r = rt;
    }
    refreshSize(rt);
    return;
}

void Merge(Node *l, Node *r, Node *&rt) {
    if (l == NULL) {
        rt = r;
        return;
    }
    if (r == NULL) {
        rt = l;
        return;
    }
    if (l->prior > r->prior){
        Merge (l->right, r, l->right);
        rt = l;
    } else {
        Merge (l, r->left, r->left);
        rt = r;
    }
    refreshSize(rt);
    return;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        Node *h = new Node(x);
        Merge(root, h, root);
    }
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        if (s == "add") {
            int ind, val;
            cin >> ind >> val;
            Node *X = new Node(val), *L = new Node(), *R = new Node();
            Split(ind, root, L, R, 0);
            Merge(L, X, L);
            Merge(L, R, root);
        }
        if (s == "del") {
            int ind;
            cin >> ind;
            Node *L = new Node(), *R = new Node(), *X = new Node();
            Split(ind, root, L, R, 0);
            Split(ind - 1, L, L, X, 0);
            Merge(L, R, root);
        }
    }
    cout << getSize(root) << endl;
    print(root);
    return 0;
}
