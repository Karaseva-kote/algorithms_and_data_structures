#include <bits/stdc++.h>

using namespace std;

const int inf = numeric_limits<int>::max();

void dijkstra(vector<int> &dist, set<pair<int, int> > &st, vector<vector<pair<int, int> > > &vec) {
    while(!st.empty()) {
        pair<int, int> p = *st.begin();
        st.erase(st.begin());
        for (int i = 0; i < vec[p.second].size(); i++) {
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
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int> > > vec(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        vec[a - 1].push_back({b - 1, c});
        vec[b - 1].push_back({a - 1, c});
    }
    vector<int> dist(n, inf);
    dist[0] = 0;
    set<pair<int, int> > st;
    for (int i = 0; i < n; i++) {
        st.insert({dist[i], i});
    }
    dijkstra(dist, st, vec);
    for (int i = 0; i < n; i++) {
        cout << dist[i] << ' ';
    }
    return 0;
}
