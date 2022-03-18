#include <bits/stdc++.h>

using namespace std;

const long long N = 1e5 + 10;
const long long inf = 5*1e9;
long long n, k, a[N], b;

long long f (long long x){
    long long l = 0, r = n;
    while (r - l > 1) {
        long long m = (r + l)/2;
        if (a[m] > x)
            r = m;
        else
            l = m;
    }
    return l;
}

int main()
{
    cin >> n >> k;
    for (long long i = 0; i < n; i++)
        cin >> a[i];
    for (long long i = 0; i < k; i++){
        cin >> b;
        long long ind = f(b);
        long long r1, r2, r3;
        if ((ind - 1) >= 0)
            r1 = abs(a[ind-1]-b);
        else
            r1 = inf;
        r2 = abs(a[ind]-b);
        if ((ind + 1) < n)
            r3 = abs(a[ind+1]-b);
        else
            r3 = inf;
        if (r1 <= r2){
            if (r1 <= r3){
                cout << a[ind - 1] << endl;
            } else {
                cout << a[ind + 1] << endl;
            }
        } else {
            if (r2 <= r3){
                cout << a[ind] << endl;
            } else {
                cout << a[ind + 1] << endl;
            }
        }
    }
    return 0;
}
