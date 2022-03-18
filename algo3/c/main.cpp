#include <iostream>

using namespace std;

const int N = 2050;
int a[N], pr[N], dp[N], ans[N];
int n, m, s, k, l;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        dp[i] = 1;
    for ( int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 2; i <= n; i++) {
        m = 0;
        for (int j = 1; j < i; j++) {
            if (a[i] > a[j] && dp[j] > m) {
                m = dp[j];
                pr[i] = j;
            }
        }
        dp[i] += m;
    }
    m = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] > m) {
            m = dp[i];
            l = i;
        }
    }
    cout << m << endl;
    s = 1;
    k = l;
    while (k != 0) {
        ans[s] = a[k];
        s++;
        k = pr[k];
    }
    for (int i = s - 1; i >= 1; i--)
        cout << ans[i] << ' ';
    return 0;
}
