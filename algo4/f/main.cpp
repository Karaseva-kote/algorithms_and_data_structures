#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
int n, m, a1, table[20][N];

int getPow (int len) {
    int k = 0, t = 1;
    while(2*t < len){
       t *= 2;
       k++;
    }
    return k;
}

int getMin (int u, int v) {
    int k = getPow(v - u + 1), t = (1 << k);
    return min(table[k][u], table[k][v - t + 1]);
}

int main() {
    cin >> n >> m >> a1;
    int t = 1, s = 0;
    while (2*t < n) {
        t *= 2;
        s++;
    }
    table[0][1] = a1;
    for (int i = 2; i <= n; i++) {
        table[0][i] = (23*table[0][i - 1] + 21563)% 16714589;
    }
    int h = 1, old = n;
    for (int i = 1; i <= s; i++) {
        for (int j = 1; j <= old - h; j++) {
            table[i][j] = min(table[i - 1][j], table[i - 1][j + h]);
        }
        old -= h;
        h *= 2;
    }
    int u1, v1, ans;
    cin >> u1 >> v1;
    ans = getMin(min(u1, v1), max(u1, v1));
    for (int i = 1; i < m; i++) {
        u1 = ((17*u1 + 751 + ans + 2*i)% n) + 1;
        v1 = ((13*v1 + 593 + ans + 5*i)% n) + 1;
        ans = getMin(min(u1, v1), max(u1, v1));
    }
    cout << u1 << " " << v1 << " " << ans;
}
