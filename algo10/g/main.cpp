#include <bits/stdc++.h>

using namespace std;

int m, k, n;
vector<vector<bool> > leftToRight;
vector<int> rightToLeft;
vector<bool> mark;
set<pair<int, int> > match;

bool dfs(int v) {
    if(mark[v]) {
        return 0;
    }
    mark[v] = 1;
    for (int u = 0; u < leftToRight[v].size(); u++) {
        if(leftToRight[v][u]) {
            if (rightToLeft[u] == -1 || dfs(rightToLeft[u])) {
                rightToLeft[u] = v;
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    cin >> m >> k >> n;
    leftToRight.resize(m + k - n, vector<bool>(m + k - n, 1));
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        int a, b;
        cin >> a >> b;
        leftToRight[a - 1][b - m - 1] = 0;
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int a;
        cin >> a;
        if (a - 1 < m) {
            for(int j = k; j < m + k - n; j++) {
                leftToRight[a - 1][j] = 0;
            }
        } else {
            for(int j = m; j < m + k - n; j++) {
                leftToRight[j][a - m - 1] = 0;
            }
        }
    }
    rightToLeft.resize(m + k - n, -1);
    mark.resize(m + k - n, 0);
    for(int i = 0; i < m + k - n; i++){
        fill(mark.begin(), mark.end(), 0);
        dfs(i);
    }
    for (int i = 0; i < m + k - n; i++) {
        if(rightToLeft[i] == -1) {
            cout << "NO";
            return 0;
        }
    }
    for(int i = 0; i < k; i++) {
        if(rightToLeft[i] < m) {
            match.insert({rightToLeft[i], i});
        }
    }
    if (match.size() != n) {
        cout << "NO";
        return 0;
    }
    cout << "YES" << endl;
    for(set<pair<int, int> >::iterator now = match.begin(); now != match.end(); ++now) {
        cout << now->first + 1 << " " << now->second + m + 1 << endl;
    }
    return 0;
}
