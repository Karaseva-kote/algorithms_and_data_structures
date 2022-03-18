#include <bits/stdc++.h>

using namespace std;

long long n, b, k;
vector <long long> a;

void Merge(long long l1, long long r1, long long l2, long long r2){
    vector <long long> result;
    long long i = l1, j = l2;
    while(i + j < r1 + r2){
        if (j == r2 || (i < r1 && a[i] <= a[j])){
            result.push_back(a[i]);
            i++;
        }
        if (i == r1 || (j < r2 && a[j] < a[i])){
            result.push_back(a[j]);
            j++;
        }
    }
    for (long long g = l1; g < r2; g++) {
        a[g] = result[g - l1];
    }
}

void mergesort (long long l, long long r){
    if (r - l == 1){
        return;
    }
    long long m = (r+l)/2;
    mergesort(l, m);
    mergesort(m, r);
    Merge(l, m, m, r);
}

long long findleft (long long x){
    long long l = -1, r = n - 1;
    while (r - l > 1) {
        long long m = (r + l)/2;
        if (a[m] >= x)
            r = m;
        else
            l = m;
    }
    if (a[r] < x && r == n - 1)
        r++;
    return r;
}

long long findright (long long x){
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
    cin >>  n;
    //srand(time(0));
    for (long long i = 0; i < n; i++){
        cin >> b;
        //b = rand()%30 - 20;
        a.push_back(b);
    }
    mergesort(0, n);
    /*for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;*/
    cin >> k;
    for (long long i = 0 ; i < k; i++){
        long long l, r, q, p;
        cin >> l >> r;
        /*p = rand()%70 - 30;
        q = rand()%70 - 30;
        l = min(p,q);
        r = max(p,q);
        cout << l << ' ' << r << endl;*/
        long long L = findleft(l), R = findleft(r);
        if (a[R] == r)
            R = findright(r) + 1;
        //cout << endl << L << ' ' << R << endl << R - L << ' ' << endl << endl;
        cout << R - L << ' ';
    }
    return 0;
/*8
-16 -14 -10 -8 -4 -1 2 9
1
-2 38*/
}
