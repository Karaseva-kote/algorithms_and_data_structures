#include <bits/stdc++.h>

using namespace std;

long long n, w, h;

int main()
{
    cin >> w >> h >> n;
    long long l = 0, r = n*max(w, h);
    while (r - l > 1) {
        long long m = (r+l)/2;
        if ((m/h)*(m/w) >= n)
            r = m;
        else
            l = m;
    }
    cout << r;
    return 0;
}
