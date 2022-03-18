#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 7;

struct edge {
    int from = 0, to = 0, f = 0, c = 0, number = 0;
    edge *rev = nullptr;

    edge() = default;

    edge(int from, int to, int c, int num) : from(from), to(to), f(0), c(c), number(num) {}
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

void draw(int v, vector<bool> &color) {
    color[v] = 1;
    for (auto e : graph[v]) {
        int u = e->to;
        if (!color[u] && e->f < e->c) {
            draw(u, color);
        }
    }
}

vector<edge *> cut;

void find_edges(vector<bool> &color) {
    for (int i = 0; i < 2 * m; i += 2) {
        if (color[edges[i].from] ^ color[edges[i].to]) {
            cut.push_back(&edges[i]);
        }
    }
}

bool cmp(edge *e1, edge *e2) {
    return e1->number < e2->number;
}

int main() {
    cin >> n >> m;
    graph.resize(n);
    edges.resize(2 * m);
    for (int i = 0; i < 2 * m; i += 2) {
        int from, to, c;
        cin >> from >> to >> c;
        edges[i] = edge(from - 1, to - 1, c, i);
        edges[i + 1] = edge(to - 1, from - 1, c, i + 1);
        edges[i].rev = &edges[i + 1];
        edges[i + 1].rev = &edges[i];
        graph[from - 1].push_back(&edges[i]);
        graph[to - 1].push_back(&edges[i + 1]);
    }
    long long F = f();
    vector<bool> color(n, 0);
    draw(0, color);
    find_edges(color);
    sort(cut.begin(), cut.end(), cmp);
    cout << cut.size() << " " << F << endl;
    for (auto i : cut) {
        cout << i->number/2 + 1 << " ";
    }
    return 0;
}