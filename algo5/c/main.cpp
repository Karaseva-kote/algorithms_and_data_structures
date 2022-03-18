#include <bits/stdc++.h>

using namespace std;

struct Node {
    int prior;
    int Size;
    int value;
    int cntEmpty;
    Node *left, *right;
    Node(int x) {
        prior = rand();
        Size = 1;
        value = x;
        cntEmpty = 0;
        left = NULL;
        right = NULL;
    }
    Node() {
        prior = rand();
        Size = 1;
        value = 0;
        cntEmpty = 1;
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

int getCnt(Node *p) {
    if (p != NULL)
         return p->cntEmpty;
    return 0;
}

void refresh(Node *&p) {
    p->Size = 1 + getSize(p->left) + getSize(p->right);
    p->cntEmpty = getCnt(p->left) + getCnt(p->right);
    if (p->value == 0) {
        p->cntEmpty++;
    }
}

void print(Node *y) {
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
    if (key < pos) {
        Split(pos, rt->right, rt->right, r, shft + getSize(rt->left) + 1);
        l = rt;
    } else {
        Split(pos, rt->left, l, rt->left, shft);
        r = rt;
    }
    refresh(rt);
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
    refresh(rt);
    return;
}

int getLeftPos0(Node *p) {
    if (p == NULL) {
        return NULL;
    }
    if (getCnt(p->left) > 0) {
        return getLeftPos0(p->left);
    }
    if (p->value == 0) {
        return getSize(p->left) + 1;
    }
    if (getCnt(p->right) > 0) {
        int r = getLeftPos0(p->right);
        if (r != NULL) {
            return getSize(p->left) + 1 + r;
        }
    }
    return NULL;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        while(getSize(root) < x) {
            Node *h = new Node();
            Merge(root, h, root);
        }
        Node *X = new Node(i), *L = new Node(), *R = new Node();
        Split(x, root, L, R, 0);
        Merge(L, X, L);
        int pos0 = getLeftPos0(R);
        if (pos0 != NULL) {
            Node *l = new Node(), *x = new Node(), *r = new Node();
            Split(pos0 + 1, R, l, r, 0);
            Split(pos0, l, l, x, 0);
            Merge(l, r, R);
        }
        Merge(L, R, root);
    }
    cout << getSize(root) << endl;
    print(root);
    return 0;
}
