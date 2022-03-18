#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7, N = 1e6;

struct Node {
    int prior;
    int Size;
    int Min;
    int minV;
    int dep;
    int ver;
    Node *left, *right;
    Node(int d, int v) {
        prior = rand();
        Size = 1;
        dep = d;
        ver = v;
        Min = d;
        minV = v;
        left = NULL;
        right = NULL;
    }
    Node() {
        prior = rand();
        Size = 1;
        left = NULL;
        right = NULL;
    }
};

Node *root;
int I[N];
vector<int> depth, msv, vec[N];
bool used[N];

int getSize(Node *p) {
    if (p != NULL)
         return p->Size;
    return 0;
}

int getMin(Node *p) {
    if (p != NULL)
         return p->Min;
    return INF;
}

void refresh(Node *&p) {
    p->Size = 1 + getSize(p->left) + getSize(p->right);
    p->Min = min(min(getMin(p->left), getMin(p->right)), p->dep);
    if (getMin(p->right) < getMin(p->left)) {
        if (getMin(p->right) < p->dep) {
            p->minV = p->right->minV;
        } else {
            p->minV = p->ver;
        }
    } else {
        if (getMin(p->left) <= p->dep) {
            p->minV = p->left->minV;
        } else {
            p->minV = p->ver;
        }
    }
}

void print (Node *y) {
    if (y == NULL) {
        return;
    }
    print(y->left);
    cout << y->dep << ' ';
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

void dfs (int v, int d) {
    I[v] = depth.size();
    depth.push_back(d);
    msv.push_back(v);
    for (int i = 0; i < vec[v].size(); i++) {
        dfs(vec[v][i], d + 1);
        depth.push_back(d);
        msv.push_back(v);
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        vec[x].push_back(i);
    }
    dfs(1, 1);
    for (int i = 0; i < depth.size(); i++) {
        Node *h = new Node(depth[i], msv[i]);
        Merge(root, h, root);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int l, r, L, R;
        cin >> l >> r;
        L = min(I[l], I[r]);
        R = max(I[l], I[r]);
        Node *LT = new Node(), *RT = new Node(), *MDL = new Node();
        Split(R + 1, root, MDL, RT, 0);
        Split(L, MDL, LT, MDL, 0);
        cout << MDL->minV << endl;
        Merge(LT, MDL, LT);
        Merge(LT, RT, root);
    }
    return 0;
}
