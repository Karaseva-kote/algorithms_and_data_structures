#include <bits/stdc++.h>

using namespace std;

const long long inf = numeric_limits<long long>::max();

void dfs(long long v, vector<vector<pair<long long, long long> > > &vec, vector<bool> &fin, vector<bool> &used) {
    used[v] = 1;
    fin[v] = 0;
    for (long long i = 0; i < vec[v].size(); i++) {
        long long u = vec[v][i].first;
        if (!used[u]) {
            dfs(u, vec, fin, used);
        }
    }
}

int main()
{
    long long n, m, s;
    cin >> n >> m >> s;
    vector<vector<pair<long long, long long> > > rv(n);
    vector<vector<pair<long long, long long> > > vec(n);
    for(long long i = 0; i < m; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        rv[b - 1].push_back({a - 1, c});
        vec[a - 1].push_back({b - 1, c});
    }
    vector<long long> d(n, inf);
    d[s - 1] = 0;
    for(long long k = 0; k < n; k++) {
        for (long long v = 0; v < n; v++) {
            for (long long i = 0; i < rv[v].size(); i++) {
                long long u = rv[v][i].first, w = rv[v][i].second;
                if (d[u] != inf && d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                }
            }
        }
    }
    vector<bool> fin(n, 1);
    for (long long v = 0; v < n; v++) {
        bool flag = 0;
        for (long long i = 0; i < rv[v].size(); i++) {
            long long u = rv[v][i].first, w = rv[v][i].second;
            if (d[u] != inf && d[v] > d[u] + w) {
                fin[v] = 0;
                flag = 1;
                break;
            }
        }
        if (flag) {
            vector<bool> used(n, 0);
            dfs(v, vec, fin, used);
        }
    }
    for (long long v = 0; v < n; v++) {
        if (!fin[v]) {
            cout << "-" << endl;
        } else {
            if (d[v] == inf) {
                cout << "*" << endl;
            } else {
                cout << d[v] << endl;
            }
        }
    }
    return 0;
}
