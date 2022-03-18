#include <bits/stdc++.h>

using namespace std;

map<string, int> name_num;
map<int, string> num_name;
int n, m, timer;

void dfs (int v, vector<bool> &used, vector<int> &tm_out, vector<vector<int> > &graph) {
    used[v] = 1;
    for(int i = 0; i < graph[v].size(); i++) {
        int u = graph[v][i];
        if (!used[u])
            dfs(u, used, tm_out, graph);
    }
    tm_out[v] = timer++;
}

void paint (int v, int color, vector<bool> &used, vector<int> &colors, vector<vector<int> > &graph) {
    used[v] = 1;
    colors[v] = color;
    for(int i = 0; i < graph[v].size(); i++) {
        int u = graph[v][i];
        if (!used[u])
            paint(u, color, used, colors, graph);
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;
        name_num.insert({name, i});
        num_name.insert({i, name});
    }
    vector<vector<int> > vec(2*n);
    vector<vector<int> > rev(2*n);
    for (int i = 0; i < m; i++) {
        string line;
        cin >> line;
        int from = 0;
        if (line[0] == '-')
            from = n;
        string name = line.substr(1, line.size() - 1);
        from += name_num.at(name);
        cin >> line >> line;
        int to = 0;
        if (line[0] == '-')
            to = n;
        name = line.substr(1, line.size() - 1);
        to += name_num.at(name);
        vec[from].push_back(to);
        vec[(to + n)%(2*n)].push_back((from + n)%(2*n));
        rev[to].push_back(from);
        rev[(from + n)%(2*n)].push_back((to + n)%(2*n));
    }
    vector<bool> used(2*n, 0);
    vector<int> tm_out(2*n);
    timer = 0;
    for (int i = 0; i < 2*n; i++) {
        if(!used[i]) {
            dfs(i, used, tm_out, vec);
        }
    }
    vector<int> topsort(2*n);
    for (int i = 0; i < 2*n; i++) {
        topsort[tm_out[i]] = i;
    }
    used.assign(2*n, 0);
    vector<int> colors(2*n);
    int color = 0;
    for (int i = 0; i < 2*n; i++) {
        int v = topsort[2*n - 1 - i];
        if (!used[v]) {
            paint(v, color, used, colors, rev);
            color++;
        }
    }
    vector<bool> invite(n);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (colors[i] == colors[i + n]) {
            cout << -1;
            return 0;
        }
        invite[i] = (colors[i] > colors[i + n]);
        cnt += invite[i];
    }
    cout << cnt << endl;
    for (int i = 0; i < n; i++) {
        if (invite[i])
            cout << num_name.at(i) << endl;
    }
    return 0;
}
