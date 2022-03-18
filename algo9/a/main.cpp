#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7, p = 37, N = 1e5;
vector<long long> strhash(N + 1), power(N + 1);

int hashsubstr(int l, int r) {
    //cout << "/" << l << " " << r << "/" << endl << (strhash[r] - (strhash[l - 1]*power[r - l + 1])%mod + mod)%mod << endl;
    return (strhash[r] - (strhash[l - 1]*power[r - l + 1])%mod + mod)%mod;
}

int main()
{
    string s;
    cin >> s;
    int n = s.size();
    strhash[0] = 0;
    power[0] = 1;
    for (int i = 0; i < n; i++) {
        strhash[i + 1] = (strhash[i]*p + s[i] - 'a')%mod;
        power[i + 1] = (power[i]*p)%mod;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if ((r1 - l1) != (r2 - l2)) {
            cout << "No" << endl;
            continue;
        }
        if (hashsubstr(l1, r1) != hashsubstr(l2, r2)) {
            cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;
    }
    return 0;
}
