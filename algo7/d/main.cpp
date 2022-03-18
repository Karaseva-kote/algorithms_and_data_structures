#include <bits/stdc++.h>

using namespace std;

const int N = 20050;
int n, m, a, b, timer, tm_in[N], up[N], root, color[N], maxcolor;
bool used[N];
vector <pair <int, int> > vec[N];
stack<int> st;

void paint(int v) {
    maxcolor++;
    int last = -1;
    while (last != v && !st.empty()) {
        color[st.top()] = maxcolor;
        last = st.top();
        st.pop();
    }
}

void dfs (int v, int edge) {
    st.push(v);
    tm_in[v] = timer;
    timer++;
    used[v] = 1;
    up[v] = tm_in[v];
    for (int i = 0; i < vec[v].size(); i++) {
        int u = vec[v][i].first;
        int e = vec[v][i].second;
        if (!used[u]) {
            dfs(u, e);
            up[v] = min(up[v], up[u]);
        }
        else {
            if (e != edge)
                up[v] = min(up[v], tm_in[u]);
        }
        if (up[u] > tm_in[v])
            paint(u);
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
    root = 1;
    for (; root <= n; root++) {
        if (!used[root])
            dfs(root, 0);
        if (!st.empty()) {
            maxcolor++;
            while(!st.empty()) {
                int r = st.top();
                color[r] = maxcolor;
                st.pop();
            }
        }
    }
    cout << maxcolor << endl;
    for (int i = 1; i <= n; i++) {
        cout << color[i] << " ";
    }
    return 0;
}
