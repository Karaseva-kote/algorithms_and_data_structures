#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10;
int n, k, a[N], dp[N], pr[N];

int main()
{
    //freopen ("input.txt", "r", stdin);
    //freopen ("output.txt", "w", stdout);
    cin >> n >> k;
    for (int i = 2; i <= n - 1; i++) {
        cin >> a[i];
    }
    dp[1] = a[1];
    pr[1] = -1;
    for (int i = 2; i <= n; i++) {
        int indMax = max(1, i - k);
        for (int j = max(1, i - k); j < i; j++) {
            if (dp[j] > dp[indMax])
                indMax = j;
        }
        dp[i] = dp[indMax] + a[i];
        pr[i] = indMax;
    }
    cout << dp[n] << endl;
    vector <int> ans;
    ans.push_back(n);
    int prev = pr[n];
    while (prev != -1) {
        ans.push_back(prev);
        prev = pr[prev];
    }
    cout << ans.size() - 1 << endl;
    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << ' ';
    }
    return 0;
}
