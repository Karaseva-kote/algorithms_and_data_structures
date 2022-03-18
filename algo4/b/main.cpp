#include <bits/stdc++.h>

using namespace std;

struct p{
    int l;
    int r;
    long long sum;
};

const int N = 1050000;
int n, L, R, t;
long long SUM;
string m;
p sum[N];

void set1 (int v){
    if (v >= 1){
        sum[v].sum = sum[v * 2].sum + sum[v * 2 + 1].sum;
        set1(v / 2);
    }
}

void getSum (int v){
    if (v > 2 * t)
        return;
    if (sum[v].l >= L && sum[v].r <= R)
        SUM += sum[v].sum;
    else{
        if (!(sum[v].r < L || sum[v].l > R)){
            getSum(v * 2);
            getSum(v * 2 + 1);
        }
    }
}

int main()
{
    cin >> n;
    t = 1;
    while (t < n)
        t *= 2;
    for (int i = t; i < t * 2; i++){
        sum[i].l = i - t + 1;
        sum[i].r = i - t + 1;
    }
    for (int i = t - 1; i > 0; i--){
        sum[i].l = sum[i * 2].l;
        sum[i].r = sum[i * 2 + 1].r;
    }
    for (int i = 0; i < n; i++){
        int c;
        cin >> c;
        sum[i + 1 + t - 1].sum = c;
        set1((i + 1 + t - 1) / 2);
    }
    while (cin >> m){
        cin >> L >> R;
        if (m == "set"){
            sum[L + t - 1].sum = R;
            set1((L + t - 1) / 2);
        }
        if (m == "sum"){
            SUM = 0;
            getSum(1);
            cout << SUM << endl;
        }
    }
    return 0;
}
