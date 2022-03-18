#include <bits/stdc++.h>

using namespace std;

struct Node {
    int prior;
    int Size;
    int value;
    Node *left, *right;
    Node() {
        prior = rand();
        value = NULL;
        Size = 1;
        left = NULL;
        right = NULL;
    }
    Node(int x) {
        prior = rand();
        value = x;
        Size = 1;
        left = NULL;
        right = NULL;
    }
};

Node *root, *root2;

int getSize(Node *p) {
    if (p != NULL)
         return p->Size;
    return 0;
}

void refreshSize(Node *&p) {
    p->Size = 1 + getSize(p->left) + getSize(p->right);
}

void print(Node *y) {
    if (y == NULL) {
        return;
    }
    print (y->left);
    cout << y->value << ' ';
    print (y->right);
}

void Split(int pos, Node *rt, Node *&l, Node *&r, int shft) {
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
    refreshSize(rt);
    return;
}

void Merge(Node *l, Node *r, Node *& rt){
    if (l == NULL) {
        rt = r;
        return;
    }
    if (r == NULL) {
        rt = l;
        return;
    }
    if (l->prior > r->prior) {
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
    for (int i = 1; i <= n; i++) {
        Node *h = new Node(i);
        Merge(root, h, root);
        Merge(h, root2, root2);
    }
    for (int i = 0; i < m; i++) {
        int L, R;
        cin >> L >> R;
        Node *LT = new Node(), *RT = new Node(), *MDL = new Node();
        Node *LT2 = new Node(), *RT2 = new Node(), *MDL2 = new Node();
        Split(R + 1, root, MDL, RT, 0);
        Split(L, MDL, LT, MDL, 0);
        Split(n - L + 2, root2, MDL2, RT2, 0);
        Split(n - R + 1, MDL2, LT2, MDL2, 0);
        Merge(LT, MDL2, MDL2);
        Merge(MDL2, RT, root);
        Merge(LT2, MDL, MDL);
        Merge(MDL, RT2, root2);
    }
    print(root);
    return 0;
}
