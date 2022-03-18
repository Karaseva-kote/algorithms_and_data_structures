#include <bits/stdc++.h>

using namespace std;

const int N = 1010;
int n, m, a[N][N], dp[N][N];
char pr[N][N];

int main()
{
    freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    dp[1][1] = a[1][1];
    pr[1][1] = 'E';
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i == 1 && j == 1)
                continue;
            if (i == 1) {
                dp[i][j] = dp[i][j - 1] + a[i][j];
                pr[i][j] = 'R';
                continue;
            }
            if (j == 1) {
                dp[i][j] = dp[i - 1][j] + a[i][j];
                pr[i][j] = 'D';
                continue;
            }
            if (dp[i - 1][j] > dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j] + a[i][j];
                pr[i][j] = 'D';
            } else {
                dp[i][j] = dp[i][j - 1] + a[i][j];
                pr[i][j] = 'R';
            }
        }
    }
    cout << dp[n][m] << endl;
    vector <char> ans;
    int x = m, y = n;
    while (pr[y][x] != 'E') {
        ans.push_back(pr[y][x]);
        if (pr[y][x] == 'R')
            x--;
        else
            y--;
    }
    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i];
    }
    return 0;
}
