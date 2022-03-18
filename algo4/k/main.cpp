#include <bits/stdc++.h>

using namespace std;

struct p {
    int l;
    int r;
    int indL0;
    int indR0;
};

const int N = 3e5, inf = 5e6;
int n, m, t = 1;
p tree[N];

void exit (int v, int x) {
    if (tree[v].l == x && tree[v].r == x) {
        tree[v].indL0 = tree[v].l;
        tree[v].indR0 = tree[v].l;
        return;
    }
    if (tree[v].l <= x && x <= tree[v].r) {
        exit(v*2, x);
        exit(v*2 + 1, x);
        tree[v].indL0 = min(tree[v*2].indL0, tree[v*2 + 1].indL0);
        tree[v].indR0 = max(tree[v*2].indR0, tree[v*2 + 1].indR0);
        return;
    }
    return;
}

void enter (int v, int x) {
    if (tree[v].l == x && tree[v].r == x) {
        tree[v].indL0 = inf;
        tree[v].indR0 = -1;
        return;
    }
    if (tree[v].l <= x && x <= tree[v].r) {
        enter(v*2, x);
        enter(v*2 + 1, x);
        tree[v].indL0 = min(tree[v*2].indL0, tree[v*2 + 1].indL0);
        tree[v].indR0 = max(tree[v*2].indR0, tree[v*2 + 1].indR0);
        return;
    }
    return;
}

int findPlace (int v, int x) {
    if (v >= t) {
        return tree[v].indL0;
    }
    if ((tree[v].indL0 != inf && x < tree[v].indL0) || (tree[v].indR0 != -1 && x > tree[v].indR0))
        return tree[v].indL0;
    if (tree[v*2].indL0 <= x && x <= tree[v*2].indR0) {
        return findPlace(2*v, x);
    }
    if (tree[v*2 + 1].indL0 <= x && x <= tree[v*2 + 1].indR0) {
        return findPlace(2*v + 1, x);
    }
    return tree[v*2 + 1].indL0;
}

int main()
{
    //freopen("parking.in", "r", stdin);
    //freopen("parking.out", "w", stdout);
    cin >> n >> m;
    while (t < n) {
        t *= 2;
    }
    for (int i = t; i < t + n; i++) {
        tree[i].l = i - t + 1;
        tree[i].r = i - t + 1;
        tree[i].indL0 = i - t + 1;
        tree[i].indR0 = i - t + 1;
    }
    for (int i = t + n; i < 2*t; i++) {
        tree[i].l = i - t + 1;
        tree[i].r = i - t + 1;
        tree[i].indL0 = inf;
        tree[i].indR0 = -1;
    }
    for (int i = t - 1; i > 0; i--) {
        tree[i].l = tree[i*2].l;
        tree[i].r = tree[i*2 + 1].r;
        tree[i].indL0 = min(tree[i*2].indL0, tree[i*2 + 1].indL0);
        tree[i].indR0 = max(tree[i*2].indR0, tree[i*2 + 1].indR0);
    }
    /*for (int i = 1; i < 2*t; i++) {
        if (tree[i].indL0 != inf)
            cout << "(" << tree[i].indL0;
        else
            cout << "(m";
        cout << ' ' << tree[i].indR0 << ") ";
    }
    cout << endl;*/
    for (int i = 0; i < m; i++) {
        string s;
        int x;
        cin >> s >> x;
        if (s == "enter") {
            int ans = findPlace(1, x);
            cout << ans << endl;
            enter(1, ans);
        }
        if (s == "exit") {
            exit(1, x);
        }
        /*for (int i = 1; i < 2*t; i++) {
            if (tree[i].indL0 != inf)
                cout << "(" << tree[i].indL0;
            else
                cout << "(m";
            cout << ' ' << tree[i].indR0 << ") ";
        }
        cout << endl;*/
    }
    return 0;
}
