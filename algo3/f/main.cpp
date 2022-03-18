#include <bits/stdc++.h>

using namespace std;

const int N = 110, inf = 1e8 + 7;
int n, dp[N][N], cost[N], pr[N][N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> cost[i];
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        dp[0][i] = inf;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (cost[i] > 100) {
                int useTicket, notUseTicket;
                if (j > 0)
                    notUseTicket = dp[i - 1][j - 1] + cost[i];
                else
                    notUseTicket = inf;
                if (j < n)
                    useTicket = dp[i - 1][j + 1];
                else
                    useTicket = inf;
                if (useTicket < notUseTicket) {
                    pr[i][j] = j + 1;
                    dp[i][j] = useTicket;
                } else {
                    pr[i][j] = j - 1;
                    dp[i][j] = notUseTicket;
                }
            } else {
                int useTicket, notUseTicket;
                notUseTicket = dp[i - 1][j] + cost[i];
                if (j < n)
                    useTicket = dp[i - 1][j + 1];
                else
                    useTicket = inf;
                if (useTicket < notUseTicket) {
                    pr[i][j] = j + 1;
                    dp[i][j] = useTicket;
                } else {
                    pr[i][j] = j;
                    dp[i][j] = notUseTicket;
                }
            }
        }
    }
    int remains = 0;
    for (int i = 0; i <= n; i++) {
        if (dp[n][i] <= dp[n][remains])
            remains = i;
    }
    vector <int> ans;
    int k = remains;
    for (int i = n; i > 1; i--) {
        if (pr[i][k] == k + 1)
            ans.push_back(i);
        k = pr[i][k];
    }
    cout << dp[n][remains] << endl << remains << " " << ans.size() << endl;
    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i] << endl;
    return 0;
}
