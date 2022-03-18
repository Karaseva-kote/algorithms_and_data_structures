#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 7, N = 200050;
int n, edge[N];
bool used[N];
vector <pair <int, int> > vec[N];
set <pair <int, int> > p;

void search_tree () {
    p.insert({0, 1});
    for (int i = 0; i < n; i++) {
        if (p.empty())
            break;
        int v = p.begin()->second;
        p.erase(p.begin());
        used[v] = 1;
        for (int j = 0; j < vec[v].size(); j++) {
            int u = vec[v][j].first;
            int W = vec[v][j].second;
            if (!used[u] && edge[u] > W) {
                p.erase({edge[u], u});
                edge[u] = W;
                p.insert({edge[u], u});
            }
        }
    }
}

int main() {
    int m, b, e, w;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> b >> e >> w;
        vec[b].push_back(make_pair(e, w));
        vec[e].push_back(make_pair(b, w));
    }
    for (int i = 0; i <= n; i++)
        edge[i] = inf;
    edge[1] = 0;
    search_tree();
    long long SUM = 0;
    for (int i = 0; i <= n; i++) {
        if (edge[i] != inf)
            SUM += edge[i];
    }
    cout << SUM;
    return 0;
}
