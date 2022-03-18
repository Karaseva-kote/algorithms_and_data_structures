#include <bits/stdc++.h>

using namespace std;

const long long inf = numeric_limits<long long>::max();

void dijkstra(vector<long long> &dist, set<pair<long long, long long> > &st, vector<vector<pair<long long, long long> > > &vec) {
    while(!st.empty()) {
        pair<long long, long long> p = *st.begin();
        st.erase(st.begin());
        for (long long i = 0; i < vec[p.second].size(); i++) {
            if (st.find({dist[vec[p.second][i].first], vec[p.second][i].first}) != st.end()) {
                st.erase({dist[vec[p.second][i].first], vec[p.second][i].first});
                dist[vec[p.second][i].first] = min(dist[vec[p.second][i].first], dist[p.second] + vec[p.second][i].second);
                st.insert({dist[vec[p.second][i].first], vec[p.second][i].first});
            }
        }
    }
}

int main()
{
    long long n, m;
    cin >> n >> m;
    vector<vector<pair<long long, long long> > > vec(n);
    for (long long i = 0; i < m; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        vec[a - 1].push_back({b - 1, c});
        vec[b - 1].push_back({a - 1, c});
    }
    long long a, b, c;
    cin >> a >> b >> c;
    vector<long long> dist(n, inf);
    dist[a - 1] = 0;
    set<pair<long long, long long> > st;
    for (long long i = 0; i < n; i++) {
        st.insert({dist[i], i});
    }
    dijkstra(dist, st, vec);
    vector<long long> dist2(n, inf);
    dist2[b - 1] = 0;
    set<pair<long long, long long> > st2;
    for (long long i = 0; i < n; i++) {
        st2.insert({dist2[i], i});
    }
    dijkstra(dist2, st2, vec);
    long long ans = inf;
    if(dist[c - 1] != inf && dist2[c - 1] != inf && dist[c - 1] + dist2[c - 1] < ans) {
        ans = dist[c - 1] + dist2[c - 1];
    }
    if(dist[c - 1] != inf && dist[b - 1] != inf && dist[c - 1] + dist[b - 1] < ans) {
        ans = dist[c - 1] + dist[b - 1];
    }
    if(dist2[a - 1] != inf && dist2[c - 1] != inf && dist2[a - 1] + dist2[c - 1] < ans) {
        ans = dist2[a - 1] + dist2[c - 1];
    }
    if (ans == inf) {
        cout << -1;
    } else {
        cout << ans;
    }
    return 0;
}
