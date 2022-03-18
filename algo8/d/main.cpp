#include <bits/stdc++.h>

using namespace std;

const int inf = numeric_limits<int>::max();

int main()
{
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<vector<pair<int, int> > > vec(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        vec[a - 1].push_back({b - 1, c});
    }
    vector<vector<int> > dp(k + 1, vector<int>(n, inf));
    dp[0][s - 1] = 0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            if(dp[i][j] != inf) {
                for (int h = 0; h < vec[j].size(); h++) {
                    int v = vec[j][h].first, w = vec[j][h].second;
                    dp[i + 1][v] = min(dp[i + 1][v], dp[i][j] + w);
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if (dp[k][i] == inf)
            cout << -1 << endl;
        else
            cout << dp[k][i] << endl;
    }
    return 0;
}
