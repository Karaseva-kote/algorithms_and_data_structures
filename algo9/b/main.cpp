#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    cin >> s;
    int n = s.size();
    vector<int> prev(n + 1);
    prev[0] = -1;
    for (int i = 1; i <= n; i++) {
        int k = prev[i - 1];
        while(k >= 0) {
            if (s[k] == s[i - 1]) {
                break;
            }
            k = prev[k];
        }
        prev[i] = k + 1;
    }
    for (int i = 1; i <= n; i++) {
        cout << prev[i] << ' ';
    }
    return 0;
}
