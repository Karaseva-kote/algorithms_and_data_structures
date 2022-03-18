#include <bits/stdc++.h>

using namespace std;

int n, b, c = 0;
vector <int> a;

void Merge(int l1, int r1, int l2, int r2){
    vector <int> result;
    int i = l1, j = l2;
    while(i + j < r1 + r2){
        if (j == r2 || (i < r1 && a[i] <= a[j])){
            result.push_back(a[i]);
            i++;
        }
        if (i == r1 || (j < r2 && a[j] < a[i])){
            c += r1 - i;
            result.push_back(a[j]);
            j++;
        }
    }
    for (int g = l1; g < r2; g++) {
        a[g] = result[g - l1];
    }
}

void mergesort (int l, int r){
    if (r - l == 1){
        return;
    }
    int m = (r+l)/2;
    mergesort(l, m);
    mergesort(m, r);
    Merge(l, m, m, r);
}

int main()
{
    cin >>  n;
    for (int i = 0; i < n; i++){
        cin >> b;
        a.push_back(b);
    }
    mergesort(0, n);
    cout << c;
    return 0;
}
