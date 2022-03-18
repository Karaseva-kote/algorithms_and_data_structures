#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;

struct p {
    int l;
    int r;
    int Min;
    bool change;
    int index;
};

struct ans {
    int Min;
    int ind;
    ans() {
        Min = inf;
        ind = inf;
    }
    ans(int mn, int i) {
        Min = mn;
        ind = i;
    }
};

const int N = 21e5;
int n, m, t = 1;
p tree[N];

void push(int v) {
    if (tree[v].change) {
        tree[v*2].Min = max(tree[2*v].Min, tree[v].Min);
        tree[v*2].change = 1;
        tree[v*2 + 1].Min = max(tree[2*v + 1].Min, tree[v].Min);
        tree[v*2 + 1].change = 1;
    }
}

void defend(int v, int l, int r, int h) {
    //cout << v << " " <<
    if (tree[v].l > r || tree[v].r < l) {
        return;
    }
    if (v >= t) {
        tree[v].Min = max(tree[v].Min, h);
        return;
    }
    if (l <= tree[v].l && tree[v].r <= r) {
        tree[v].Min = max(tree[v].Min, h);
        tree[v].change = 1;
        return;
    }
    push(v);
    defend(2*v, l, r, h);
    defend(2*v + 1, l, r, h);
    tree[v].Min = min(tree[v*2].Min, tree[v*2 + 1].Min);
    if (tree[v*2].Min <= tree[v*2 + 1].Min) {
        tree[v].index = tree[v*2].index;
    } else {
        tree[v].index = tree[v*2 + 1].index;
    }
}

ans attack(int v, int l, int r) {
    if (tree[v].l > r || tree[v].r < l) {
        return ans();
    }
    if (l <= tree[v].l && tree[v].r <= r) {
        return ans(tree[v].Min, tree[v].index);
    }
    push(v);
    ans a1 = attack(v*2, l, r);
    ans a2 = attack(v*2 + 1, l, r);
    if (a1.Min < a2.Min)
        return a1;
    return a2;
}

void print(ans a) {
    cout << a.Min << " " << a.ind << endl;
}

int main()
{
    cin >> n >> m;
    while (t < n) {
        t *= 2;
    }
    for (int i = t; i < t + n; i++) {
        tree[i].l = i - t + 1;
        tree[i].r = i - t + 1;
        tree[i].index = i - t + 1;
        tree[i].change = 0;
        tree[i].Min = 0;
    }
    for (int i = t + n; i < t*2; i++) {
        tree[i].l = i - t + 1;
        tree[i].r = i - t + 1;
        tree[i].index = i - t + 1;
        tree[i].change = 0;
        tree[i].Min = inf;
    }
    for (int i = t - 1; i > 0; i--) {
        tree[i].l = tree[i*2].l;
        tree[i].r = tree[i*2 + 1].r;
        tree[i].change = 0;
        tree[i].Min = min(tree[i*2].Min, tree[i*2 + 1].Min);
        if (tree[i*2].Min <= tree[i*2 + 1].Min) {
            tree[i].index = tree[i*2].index;
        } else {
            tree[i].index = tree[i*2 + 1].index;
        }
    }
    string s;
    /*for (int i = 1; i < 2*t; i++) {
        if (tree[i].Min != inf)
            cout << tree[i].Min << " ";
        else
            cout << "inf ";
    }
    cout << endl;*/
    for (int i = 0; i < m; i++) {
        cin >> s;
        if (s == "defend") {
            int a, b, c;
            cin >> a >> b >> c;
            defend(1, a, b, c);
        }
        if (s == "attack") {
            int d, e;
            cin >> d >> e;
            print(attack(1, d, e));
        }
        /*for (int i = 1; i < 2*t; i++) {
            if (tree[i].Min != inf)
                cout << tree[i].Min << " ";
            else
                cout << "inf ";
        }
        cout << endl;*/
    }
    return 0;
}
