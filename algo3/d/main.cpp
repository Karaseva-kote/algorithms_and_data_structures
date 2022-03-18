#include <bits/stdc++.h>

using namespace std;

const int N = 110, mod = 1e9;
long long n, dp[10][N];
vector <int> v[10];

int main()
{
    v[0].push_back(4), v[0].push_back(6);
    v[1].push_back(6), v[1].push_back(8);
    v[2].push_back(7), v[2].push_back(9);
    v[3].push_back(4), v[3].push_back(8);
    v[4].push_back(0), v[4].push_back(3), v[4].push_back(9);
    v[6].push_back(0), v[6].push_back(1), v[6].push_back(7);
    v[7].push_back(2), v[7].push_back(6);
    v[8].push_back(1), v[8].push_back(3);
    v[9].push_back(2), v[9].push_back(4);
    dp[0][1] = 0;
    dp[1][1] = 1;
    dp[2][1] = 1;
    dp[3][1] = 1;
    dp[4][1] = 1;
    dp[5][1] = 1;
    dp[6][1] = 1;
    dp[7][1] = 1;
    dp[8][1] = 0;
    dp[9][1] = 1;
    cin >> n;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < 10; j++) {
            long long sum = 0;
            for (int k = 0; k < v[j].size(); k++)
                sum = (sum + dp[v[j][k]][i - 1])%mod;
            dp[j][i] = sum;
        }
    }
    int ans = 0;
    for (int i = 0; i < 10; i++) {
        ans = (ans + dp[i][n])%mod;
    }
    cout << ans;
    return 0;
}
