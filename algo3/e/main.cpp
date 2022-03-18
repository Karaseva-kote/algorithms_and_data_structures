#include <bits/stdc++.h>

using namespace std;

const int N = 1010;
int dp[N][N];
string s1, s2;

int main()
{
    cin >> s1 >> s2;
    int n = s1.size(), m = s2.size();
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        dp[i][0] = i;
    for (int i = 1; i <= m; i++)
        dp[0][i] = i;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else {
                dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
            }
        }
    }
    cout << dp[n][m];
    return 0;
}
