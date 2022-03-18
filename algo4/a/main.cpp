#include <iostream>
#include <vector>

using namespace std;

int main()
{
    long long n, x, y, a, m, z, t, b;
    cin >> n >> x >> y >> a >> m >> z >> t >> b;
    if (m == 0) {
        cout << 0;
        return 0;
    }
    vector <long long> A(n + 1);
    A[0] = 0;
    A[1] = a;
    for (int i = 2; i <= n; i++) {
        A[i] = (x*A[i - 1] + y)%(1 << 16);
    }
    for (int i = 2; i <= n; i++) {
        A[i] += A[i - 1];
    }
    vector <long long> C(2*m);
    C[0] = b;
    for (int i = 1; i < 2*m; i++) {
        C[i] = (z*C[i - 1] + t)%(1 << 30);
        if (C[i] < 0)
            C[i] += (1 << 30);
    }
    for (int i = 0; i < 2*m; i++) {
        C[i] %= n;
    }
    long long ANS = 0;
    for (int i = 0; i < m; i++){
        long long l = min(C[i*2], C[i*2 + 1]);
        long long r = max(C[i*2], C[i*2 + 1]) + 1;
        ANS += (A[r] - A[l]);
    }
    cout << ANS;
    return 0;
}
