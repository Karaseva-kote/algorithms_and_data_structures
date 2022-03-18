#include <bits/stdc++.h>

using namespace std;

long long n, x, y;

long long f (long long c){
    return min(x, y) + max(x*c, y*(n - 1 - c));
}

long long find_min () {
    long long l = 0, r = n;
    for (long long i = 0; i < 100; i++) {
    long long m1 = l + (r - l)/3, m2 = r - (r - l)/3;
    //cout << l << ' ' << m1 << ' ' << m2 << ' ' << r << endl;
    //cout << f(m1) << ' ' << f(m2) << endl;
    if (f(m1) < f(m2))
        r = m2;
    else
        l = m1;
    }
    return min(f(l), min(f(r), f((r+l)/2)));
}

int main()
{
    cin >> n >> x >> y;
    cout << find_min();
    return 0;
}
