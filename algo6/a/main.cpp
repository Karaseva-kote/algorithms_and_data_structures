#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int st = 1, logn = 0;
    while (st < n) {
        st *= 2;
        logn++;
    }
    vector< vector<int> > dp(n + 1, vector<int>(logn + 1, 0));
    for (int i = 1; i <= n; i++) {
        cin >> dp[i][0];
    }
    for (int i = 1; i <= logn; i++) {
        for (int j = 1; j <= n; j++) {
            dp[j][i] = dp[dp[j][i - 1]][i - 1];
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        int j = 0;
        while (dp[i][j] != 0) {
            cout << dp[i][j] << " ";
            j++;
        }
        cout << endl;
    }
    return 0;
}
