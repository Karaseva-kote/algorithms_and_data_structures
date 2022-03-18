#include <bits/stdc++.h>

using namespace std;

const int B = 1e6 + 10;
int a[B], l, r, n;
string s;

int z (int x)
{
    if (l <= x && x < r)
    {
        int j = min(a[x - l], r - x);
        int k = r;
        if (a[x - l] < r - x)
            return j;
        while (s[j] == s[k] && k < n && j < n)
        {
            k++;
            j++;
        }
        if (k > r)
        {
            l = x;
            r = k;
        }
        return j;
    }
    else
    {
        int j = 0;
        while (s[j] == s[j + x] && j + x < n)
            j++;
        if (j + x > r)
        {
            l = x;
            r = j + x;
        }
        return j;
    }
}

int main()
{
    cin >> s;
    n = s.size();
    l = 0;
    r = 1;
    for (int i = 1; i <= n; i++)
        a[i] = z(i);
    for (int i = 0; i <= n; i++)
    {
        if (a[i] > 0)
        {
            if (a[i]%i == 0 && a[i] == n - i) {
                cout << i;
                return 0;
            }
        }
    }
    cout << n;
    return 0;
}
