#include <bits/stdc++.h>

using namespace std;

const int N = 110;
int n;
string dp[N][N];
string s, buf, Max;

int main()
{
    cin >> s;
    n = s.size();
    for (int j = 2; j <= n; j++) {
        for (int i = 1; i <= n; i++) {
            if (j <= n - i + 1) {
                if ((s[i - 1] == '(') && (s[i + j - 2] == ')') && (dp[i + 1][j - 2].size() + 2 > dp[i][j].size())) {
                    dp[i][j] = "(" + dp[i + 1][j - 2] + ")";
                }
                if ((s[i - 1] == '{') && (s[i + j - 2] == '}') && (dp[i + 1][j - 2].size() + 2 > dp[i][j].size())) {
                    dp[i][j] = "{" + dp[i + 1][j - 2] + "}";
                }
                if ((s[i - 1] == '[') && (s[i + j - 2] == ']') && (dp[i + 1][j - 2].size() + 2 > dp[i][j].size())) {
                    dp[i][j] = "[" + dp[i + 1][j - 2] + "]";
                }
                for (int k = i + 1; k < i + j; k++) {
                    buf = dp[i][k - i] + dp[k][j + i - k];
                    if (dp[i][j].size() < buf.size())
                        dp[i][j] = buf;
                }
            }
            if (dp[i][j].size() > Max.size())
                Max = dp[i][j];
        }
    }
    cout << Max;
    return 0;
}
