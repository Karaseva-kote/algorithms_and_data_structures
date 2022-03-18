#include <bits/stdc++.h>

using namespace std;

const int N = 20050, M = 2e6 + 50;
int n, m, a, b, timer, tm_in[N], up[N], j, colors[M], maxcolor;
bool used[N];
vector <pair <int, int> > vec[N];
stack <int> st;

void dfs (int v, int edge) {
    tm_in[v] = timer++;
    used[v] = 1;
    up[v] = tm_in[v];
    for (int i = 0; i < vec[v].size(); i++) {
        int u = vec[v][i].first;
        int e = vec[v][i].second;
        if (e == edge)
            continue;
        if (!used[u]) {
            st.push(e);
            dfs(u, e);
            up[v] = min(up[v], up[u]);
            if (up[u] >= tm_in[v]) {
                int color = ++maxcolor;
                while(st.top() != e) {
                    colors[st.top()] = color;
                    st.pop();
                }
                colors[e] = color;
                st.pop();
            }
        } else {
            if (tm_in[u] < tm_in[v]) {
                st.push(e);
                if (tm_in[u] < up[v])
                    up[v] = tm_in[u];
            } else {
                if (up[v] > tm_in[u])
                    up[v] = up[u];
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a >> b;
        vec[a].push_back(make_pair(b, i));
        vec[b].push_back(make_pair(a, i));
    }
    timer = 1;
    j = 1;
    for (; j <= n; j++) {
        if (!used[j])
            dfs(j, 0);
    }
    cout << maxcolor << endl;
    for (int i = 1; i <= m; i++) {
        cout << colors[i] << " ";
    }
    return 0;
}
