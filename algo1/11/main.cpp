#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, inf = 1e9 + 7;
const long double eps = 1e-9;

vector < pair <long double, int> > a;
int n, k;
long double v[N], w[N], q[N], MAX;

long double getsumk (long double x) {
    for (int i = 0; i < n; i++) {
        q[i] = v[i] - x * w[i];
    }
    sort(q, q + n);
    long double sum = 0;
    for (int i = n - 1; i >= n - k; i--) {
        sum += q[i];
    }
    return sum;
}

long double f(){
    long double l = 0, r = inf;
    while (r - l > eps){
        long double m = (l+r)/2;
        if (getsumk(m) >= 0)
            l = m;
        else
            r = m;
    }
    return l;
}

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> v[i] >> w[i];
    }
    MAX = f();
    for (int i = 0; i < n; i++){
        a.push_back(make_pair(v[i] - MAX*w[i], i + 1));
    }
    sort(a.begin(), a.end());
    for(int i = n - 1; i >= n - k; i--)
        cout << a[i].second << endl;
    return 0;
}
