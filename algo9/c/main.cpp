#include <bits/stdc++.h>

using namespace std;

const int N = 1000050;
int n, a[N], l, r;
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
    for (int i = 1; i < n; i++)
    {
        a[i] = z(i);
        cout << a[i] << ' ';
    }
    return 0;
}
