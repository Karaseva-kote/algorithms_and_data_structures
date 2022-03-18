#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 7;

struct edge {
    int to = 0, f = 0, c = 0;
    edge *rev = nullptr;

    edge() = default;

    edge(int to, int c) : to(to), f(0), c(c) {}
};

int n, m, s, t;
vector<edge> edges;
vector<vector<edge *>> graph;

int dfs(int v, int minCap, vector<bool> &used) {
    if (v == t - 1) {
        return minCap;
    }
    used[v] = 1;
    for (auto & i : graph[v]) {
        int u = i->to;
        edge *e = i;
        if (!used[u] && e->f < e->c) {
            int delta = dfs(u, min(e->c - e->f, minCap), used);
            if (delta != 0) {
                e->f += delta;
                e->rev->f -= delta;
                return delta;
            }
        }
    }
    return 0;
}

long long f() {
    long long ans, sum = 0;
    do {
        vector<bool> used(n, 0);
        ans = dfs(s - 1, inf, used);
        sum += ans;
    } while (ans != 0);
    return sum;
}

vector<int> pred;

void find_pred(int v) {
    pred.push_back(v);
    if (v == t - 1)
        return;
    for (auto it : graph[v]) {
        int u = it->to;
        if (it->f == 1) {
            it->f = 0;
            find_pred(u);
            return;
        }
    }
}

int main() {
    cin >> n >> m >> s >> t;
    graph.resize(n);
    edges.resize(2 * m);
    for (int i = 0; i < 2 * m; i += 2) {
        int from, to;
        cin >> from >> to;
        edges[i] = edge(to - 1, 1);
        edges[i + 1] = edge(from - 1, 0);
        edges[i].rev = &edges[i + 1];
        edges[i + 1].rev = &edges[i];
        graph[from - 1].push_back(&edges[i]);
        graph[to - 1].push_back(&edges[i + 1]);
    }
    long long F = f();
    if (F < 2) {
        cout << "NO";
        return 0;
    }
    cout << "YES" << endl;
    find_pred(s - 1);
    for (auto i : pred) {
        cout << i + 1 << " ";
    }
    pred.clear();
    find_pred(s - 1);
    cout << endl;
    for (auto i : pred) {
        cout << i + 1 << " ";
    }
    return 0;
}