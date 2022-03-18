#include <bits/stdc++.h>

using namespace std;

const int N = 10000, T = 15;
const long long INF = 3000000000;
long long n, dp[N][T], pr[N][T], mat[T][T], ind, ans[T], mask;

int main()
{
    cin >> n;
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
            cin >> mat[i][j];
    long long t = 0;
    t = (t | (1 << n));
    for (mask = 0; mask < t; mask++)
        for (long long i = 0; i < n; i++) {
            dp[mask][i] = INF;
            pr[mask][i] = -1;
        }
    for (long long i = 0; i < n; i++)
        dp[(0 | (1 << i))][i] = 0;
    for (mask = 0; mask < t - 1; mask++) {
        int buf = mask;
        for (long long j = 0; j < n; j++) {
            if (buf % 2 == 1) {
                for (long long k = 0; k < n; k++) {
                    if (!(mask & (1 << k))) {
                        if (dp[mask][j] + mat[j][k] < dp[mask | (1 << k)][k]) {
                            dp[mask | (1 << k)][k] = dp[mask][j] + mat[j][k];
                            pr[mask | (1 << k)][k] = j;
                        }
                    }
                }
            }
            buf = buf / 2;
        }
    }
    ind = 0;
    for (long long i = 0; i < n; i++) {
        if (dp[t - 1][i] < dp[t - 1][ind])
            ind = i;
    }
    cout << dp[t - 1][ind] << endl;
    mask = t - 1;
    int g = 0;
    while (ind != -1) {
        ans[g] = ind + 1;
        g++;
        int Mask = mask;
        Mask = (Mask ^ (1 << ind));
        ind = pr[mask][ind];
        mask = Mask;
    }
    for (long long i = g - 1; i >= 0; i--)
        cout << ans[i] << ' ';
    return 0;
}
