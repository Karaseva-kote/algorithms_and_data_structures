#include <bits/stdc++.h>

using namespace std;

const int N = 6e5;
int n, m, r, t = 1;
int Mul[N][6], mx[4];

void multiplyMatrix(int[]v, int[]u){
    int c11 = (mx[0]*Mul[v][2] + mx[1]*Mul[v][4])%r;
    int c12 = (mx[0]*Mul[v][3] + mx[1]*Mul[v][5])%r;
    int c21 = (mx[2]*Mul[v][2] + mx[3]*Mul[v][4])%r;
    int c22 = (mx[2]*Mul[v][3] + mx[3]*Mul[v][5])%r;
    mx[0] = c11;
    mx[1] = c12;
    mx[2] = c21;
    mx[3] = c22;
}

int[] getMul(int v, int l, int r, int lv, int rv){
    if (lv >= l && rv <= r){
        multiplyMatrix(v);
        return;
    }
    if (rv < l || lv > r) {
        return new int[1, 0, 0, 1];
    }
    return mulMatrix(getMul(v*2, l, r, lv, (rv + lv) / 2), getMul(v*2 + 1, l, r, (rv + lv) / 2, rv);
}

int main()
{
    //freopen("crypto.in", "r", stdin);
    //freopen("crypto.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> r >> n >> m;
    while (t < n)
        t *= 2;
    for (int i = t + n; i < t * 2; i++){
       // Mul[i][0] = i - t + 1;
       // Mul[i][1] = i - t + 1;
        Mul[i][2] = 1;
        Mul[i][3] = 0;
        Mul[i][4] = 0;
        Mul[i][5] = 1;
    }
    for (int i = 0; i < n; i++){
        cin >> Mul[i + t][2] >> Mul[i + t][3] >> Mul[i + t][4] >> Mul[i + t][5];
    }
    for (int i = t - 1; i > 0; i--){
        //Mul[i][0] = Mul[i * 2][0];
        //Mul[i][1] = Mul[i * 2 + 1][1];
        Mul[i][2] = (Mul[i * 2][2]*Mul[i * 2 + 1][2] + Mul[i * 2][3]*Mul[i * 2 + 1][4])%r;
        Mul[i][3] = (Mul[i * 2][2]*Mul[i * 2 + 1][3] + Mul[i * 2][3]*Mul[i * 2 + 1][5])%r;
        Mul[i][4] = (Mul[i * 2][4]*Mul[i * 2 + 1][2] + Mul[i * 2][5]*Mul[i * 2 + 1][4])%r;
        Mul[i][5] = (Mul[i * 2][4]*Mul[i * 2 + 1][3] + Mul[i * 2][5]*Mul[i * 2 + 1][5])%r;
    }
    for (int i = 0; i < m; i++){
        int l, r;
        mx[0] = 1;
        mx[1] = 0;
        mx[2] = 0;
        mx[3] = 1;
        cin >> l >> r;
        getMul(1, l, r);
        cout << mx[0] << " " << mx[1] << endl << mx[2] << " " << mx[3] << endl << endl;
    }
    return 0;
}
