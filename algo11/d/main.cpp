#include <bits/stdc++.h>

using namespace std;

struct cell {
    int l, h;
    cell() = default;
    cell(int l, int h) : l(l)
};

struct edge {
    cell u, v;
    int f, c;
};

int n, m;
cell s, t;
vector<edge> edges;
vector<vector<vector<int>>> graph;
vector<vector<int>> d, p;
vector<vector<char>> table;
vector<vector<bool>> reachable;

void add_edges(cell u, cell v, int c) {
    graph[u.l][u.h].push_back(edges.size());
    edges.push_back({u, v, 0, c});
    graph[v.l][v.h].push_back(edges.size());
    edges.push_back({v, u, 0, 0});
}

bool bfs() {
    for (auto &i : d) {
        for (int &j : i) {
            j = -1;
        }
    }
    d[s.l][s.h] = 0;

    queue<cell> q;
    q.push(s);

    while (!q.empty()) {
        cell u = q.front();
        q.pop();

        for (int edge : graph[u.l][u.h]) {
            int f = edges[edge].f;
            int c = edges[edge].c;
            cell v = edges[edge].v;
            if (f < c && d[v.l][v.h] == -1) {
                d[v.l][v.h] = d[u.l][u.h] + 1;
                q.push(v);
            }
        }
    }
    return d[t.l][t.h] != -1;
}

int dfs(cell u, int minC) {
    if (u.l == t.l && u.h == t.h || minC == 0) {
        return minC;
    }
    for (; p[u.l][u.h] < graph[u.l][u.h].size(); p[u.l][u.h]++) {
        int edge = graph[u.l][u.h][p[u.l][u.h]];
        int f = edges[edge].f;
        int c = edges[edge].c;
        cell v = edges[edge].v;
        if (d[v.l][v.h] != d[u.l][u.h] + 1) {
            continue;
        }

        int pushed = dfs(v, min(minC, c - f));
        if (pushed) {
            edges[edge].f += pushed;
            edges[edge ^ 1].f -= pushed;
            return pushed;
        }
    }
    return 0;
}

void check_reachable(cell u) {
    if (reachable[u.l][u.h]) {
        return;
    }
    reachable[u.l][u.h] = true;
    for (int edge : graph[u.l][u.h]) {
        int f = edges[edge].f;
        int c = edges[edge].c;
        cell v = edges[edge].v;
        if (f != c) {
            check_reachable(v);
        }
    }
}

int main() {
    cin >> m >> n;
    graph.resize(m, vector<vector<int>>(2 * n));
    d.resize(m, vector<int>(2 * n));
    p.resize(m, vector<int>(2 * n));
    table.resize(m, vector<char>(n));
    reachable.resize(m, vector<bool>(2 * n, false));

    char c;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c;
            table[i][j] = c;
            if (c == '#') {
                continue;
            }
            if (c == '-') {
                add_edges({i, 2 * j}, {i, 2 * j + 1}, INT_MAX);
                continue;
            }
            if (c == '.') {
                add_edges({i, 2 * j}, {i, 2 * j + 1}, 1);
                continue;
            }
            if (c == 'A') {
                add_edges({i, 2 * j}, {i, 2 * j + 1}, INT_MAX);
                s = {i, 2 * j};
                continue;
            }
            if (c == 'B') {
                add_edges({i, 2 * j}, {i, 2 * j + 1}, INT_MAX);
                t = {i, 2 * j + 1};
                continue;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (table[i][j] == '#') {
                continue;
            }
            if (j + 1 < n && table[i][j + 1] != '#') {
                add_edges({i, 2 * j + 1}, {i, 2 * (j + 1)}, INT_MAX);
                add_edges({i, 2 * (j + 1) + 1}, {i, 2 * j}, INT_MAX);
            }
            if (i + 1 < m && table[i + 1][j] != '#') {
                add_edges({i, 2 * j + 1}, {i + 1, 2 * j}, INT_MAX);
                add_edges({i + 1, 2 * j + 1}, {i, 2 * j}, INT_MAX);
            }
        }
    }

    int ans = 0;
    while (bfs()) {
        for (auto &i : p) {
            for (int &j : i) {
                j = 0;
            }
        }
        while (int curFlow = dfs(s, INT_MAX)) {
            ans += curFlow;
        }
    }
    check_reachable(s);
    for (int edge = 0; edge < edges.size(); edge += 2) {
        cell u = edges[edge].u;
        cell v = edges[edge].v;
        if (reachable[u.l][u.h] == reachable[v.l][v.h] || edges[edge].f != 1) {
            continue;
        }
        table[u.l][u.h / 2] = '+';
    }
    if (ans >= INT_MAX) {
        cout << -1;
        return 0;
    }
    cout << ans << endl;
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            cout << table[i][j];
        }
        cout << endl;
    }
    return 0;
}