#include <bits/stdc++.h>

using namespace std;

const long long inf = numeric_limits<long long>::max();

int main() {
    long long n, m;
    cin >> n >> m;
    long long mod = inf;
    vector<vector<pair<long long, long long> > > edge(n);
    for(int i = 0; i < m; i++) {
        long long a, b, d;
        cin >> a >> b >> d;
        edge[a - 1].push_back({b - 1, d});
        edge[b - 1].push_back({a - 1, d});
        if ((a == 1 || a == n || b == 1 || b == n) && mod > d) {
            mod = d;
        }
    }
    if (mod == inf) {
        cout << "Impossible";
        return 0;
    }
    mod *= 2;
    long long t;
    cin >> t;
    vector<vector<long long> > d(n, vector<long long>(mod, 2e18));
    set<pair<long long, pair<long long, long long> > > ver;
    ver.insert({0, {0, 0}});
    d[0][0] = 0;
    while (!ver.empty()) {
        long long v = ver.begin()->second.first;
        long long rest = ver.begin()->second.second;
        ver.erase(ver.begin());
        for (int next = 0; next < edge[v].size(); next++) {
            long long weight = edge[v][next].second;
            long long to = edge[v][next].first;
            long long newRest = (rest + weight) % mod;
            if (d[to][newRest] > d[v][rest] + weight) {
                if (ver.find({d[to][newRest], {to, newRest}}) != ver.end())
                    ver.erase({d[to][newRest], {to, newRest}});
                d[to][newRest] = d[v][rest] + weight;
                ver.insert({d[to][newRest], {to, newRest}});
            }
        }
    }
    if (d[n - 1][t % mod] <= t)
        cout << "Possible";
    else
        cout << "Impossible";
}
