#include <bits/stdc++.h>

using namespace std;

const int inf = numeric_limits<int>::max();

int main()
{
    int n;
    cin >> n;
    vector<vector<long long> > m(n, vector<long long>(n));
    vector<vector<int> > pr(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
            if (m[i][j] == 1e5) {
                m[i][j] = inf;
            }
            pr[i][j] = i;
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (m[i][j] > m[i][k] + m[k][j]) {
                    m[i][j] = m[i][k] + m[k][j];
                    pr[i][j] = pr[k][j];
                }
            }
        }
        for(int i = 0; i < n; i++) {
            if (m[i][i] < 0) {
                cout << "YES" << endl;
                int cur = i;
                vector<int> ans;
                ans.push_back(cur + 1);
                cur = pr[i][cur];
                while(cur != i) {
                    ans.push_back(cur + 1);
                    cur = pr[i][cur];
                }
                cout << ans.size() << endl;
                for (int j = ans.size() - 1; j >= 0; j--) {
                    cout << ans[j] << ' ';
                }
                return 0;
            }
        }
    }
    cout << "NO";
    return 0;
}
