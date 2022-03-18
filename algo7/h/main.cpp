#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9 + 7;
int n;

int dfs(int v, int k, vector<vector<int> > &graph, vector<bool> &used, int &timer, vector<int> &tm_out) {
    used[v] = 1;
    int cnt_v = 1;
    for (int i = 0; i < n; i++) {
        if (graph[v][i] <= k && !used[i]) {
            cnt_v += dfs(i, k, graph, used, timer, tm_out);
        }
    }
    tm_out[v] = timer;
    timer--;
    return cnt_v;
}

bool connected(int k, vector<vector<int> > &graph, vector<vector<int> > &rev_graph) {
    vector<bool> used(n, 0);
    vector<int> tm_out(n);
    int timer = n - 1;
    if (dfs(0, k, graph, used, timer, tm_out) < n)
        return 0;
    vector<int> topsort(n);
    for (int i = 0; i < n; i++) {
        topsort[tm_out[i]] = i;
    }
    vector<bool> used2(n, 0);
    vector<int> tm_out2(n);
    int timer2 = n - 1;
    if (dfs(topsort[0], k, rev_graph, used2, timer2, tm_out2) < n)
        return 0;
    else
        return 1;
}

int bin_search(int l, int r, vector<vector<int> > &graph, vector<vector<int> > &rev_graph){
    while(r - l > 1) {
        int m = (l + r)/2;
        if (connected(m, graph, rev_graph)) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

int main()
{
    freopen("avia.in", "r", stdin);
    freopen("avia.out", "w", stdout);
    cin >> n;
    vector<vector<int> > graph(n, vector<int>(n));
    vector<vector<int> > rev_graph(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
            rev_graph[j][i] = graph[i][j];
        }
    }
    cout << bin_search(-1, inf, graph, rev_graph);
    return 0;
}
