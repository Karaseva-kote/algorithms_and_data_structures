#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int> > leftToRight;
vector<int> rightToLeft;
vector<bool> mark;
vector<pair<int, int> > match;

bool dfs(int v) {
    if(mark[v]) {
        return 0;
    }
    mark[v] = 1;
    for (int i = 0; i < leftToRight[v].size(); i++) {
        int u = leftToRight[v][i];
        if (rightToLeft[u] == -1 || dfs(rightToLeft[u])) {
            rightToLeft[u] = v;
            return 1;
        }
    }
    return 0;
}

int main()
{
    cin >> n >> m;
    leftToRight.resize(n);
    rightToLeft.resize(m, -1);
    mark.resize(n);
    for(int i = 0; i < n; i++) {
        int a;
        while(cin >> a) {
            if (a == 0) {
                break;
            }
            leftToRight[i].push_back(a - 1);
        }
    }
    for (int v = 0; v < n; v++) {
        fill(mark.begin(), mark.end(), 0);
        dfs(v);
    }
    for(int i = 0; i < m; i++) {
        if (rightToLeft[i] != -1) {
            match.push_back({rightToLeft[i] + 1, i + 1});
        }
    }
    cout << match.size() << endl;
    for (int i = 0; i < match.size(); i++) {
        cout << match[i].first << " " << match[i].second << endl;
    }
    return 0;
}
