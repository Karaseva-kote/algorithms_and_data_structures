#include <bits/stdc++.h>

using namespace std;

const int B = 2e6 + 10;
int a[B], l, r, f, n, N;
string S, s1, s2;

int z (int x)
{
    if (l <= x && x < r)
    {
        int j = min(a[x - l], r - x);
        int k = r;
        if (a[x - l] < r - x)
            return j;
        while (S[j] == S[k] && k < N && j < N)
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
        while (S[j] == S[j + x] && j + x < N)
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
    cin >> s2 >> s1;
    S = s2 + "#" + s1;
    n = s2.size();
    N = S.size();
    l = 0;
    r = 1;
    for (int i = 1; i < N; i++)
        a[i] = z(i);
    vector<int> ans;
    for (int i = n + 1; i < N; i++)
    {
        if (a[i] >= n)
        {
            f = 1;
            ans.push_back(i - n);
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
