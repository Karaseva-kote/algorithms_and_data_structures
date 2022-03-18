#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 7;

struct edge {
    int to = 0, f = 0, c = 0;
    edge *rev = nullptr;

    edge() = default;

    edge(int to, int c) : to(to), f(0), c(c) {}
};

int n;
int m;
vector<edge> edges;
vector<vector<edge *>> graph;

int dfs(int v, int minCap, vector<bool> &used) {
    if (v == n - 1) {
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
        ans = dfs(0, inf, used);
        sum += ans;
    } while (ans != 0);
    return sum;
}

int main() {
    cin >> n >> m;
    graph.resize(n);
    edges.resize(2 * m);
    for (int i = 0; i < 2 * m; i += 2) {
        int from, to, c;
        cin >> from >> to >> c;
        edges[i] = edge(to - 1, c);
        edges[i + 1] = edge(from - 1, c);
        edges[i].rev = &edges[i + 1];
        edges[i + 1].rev = &edges[i];
        graph[from - 1].push_back(&edges[i]);
        graph[to - 1].push_back(&edges[i + 1]);
    }
    cout << f() << endl;
    for (int i = 0; i < 2 * m; i += 2) {
        cout << edges[i].f << endl;
    }
    return 0;
}