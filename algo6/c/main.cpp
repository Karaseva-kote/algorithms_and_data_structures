#include <bits/stdc++.h>

using namespace std;

const int N = 1e6, L = 21, inf = 1e9 + 7;
vector<int> vec[N];
vector< vector<int> > dp2(N, vector<int>(L, inf));
int d[N], n, logn, dp[N][L];

void dfs(int v) {
    for (int i = 0; i < vec[v].size(); i++) {
        d[vec[v][i]] = d[v] + 1;
        dfs(vec[v][i]);
    }
}

void preprocess() {
    dfs(1);
    for (int j = 1; j <= logn; j++)
        for (int i = 1; i <= n; i++)
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
}

void preprocess2() {
    for (int j = 1; j <= logn; j++)
        for (int i = 1; i <= n; i++)
            dp2[i][j] = min(dp2[i][j - 1], dp2[dp[i][j - 1]][j - 1]);
}

int lca(int v, int u) {
    int res = inf;
    if (d[v] > d[u]) {
        swap(v, u);
    }
    for (int i = logn; i >= 0; i--) {
        if (d[dp[u][i]] - d[v] >= 0) {
            res = min(res, dp2[u][i]);
            u = dp[u][i];
        }
    }
    if (v == u) {
        return res;
    }
    for (int i = logn; i >= 0; i--) {
        if (dp[v][i] != dp[u][i]) {
            res = min(res, dp2[u][i]);
            res = min(res, dp2[v][i]);
            v = dp[v][i];
            u = dp[u][i];
        }
    }
    res = min(res, dp2[u][0]);
    res = min(res, dp2[v][0]);
    return res;
}

int main()
{
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
    cin >> n;
    int st = 1;
    logn = 0;
    while (st < n) {
        st *= 2;
        logn++;
    }
    logn++;
    for (int i = 2; i <= n; i++) {
        int x, w;
        cin >> x >> w;
        dp[i][0] = x;
        dp2[i][0] = w;
        vec[x].push_back(i);
    }
    preprocess();
    preprocess2();
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }
    return 0;
}
