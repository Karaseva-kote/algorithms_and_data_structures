#include <bits/stdc++.h>

using namespace std;

struct p{
    int l;
    int r;
    long long add;
    long long change;
    long long value;
};

const int N = 3e5;
const long long inf = 1e18 + 10;
int n, t = 1;
p Min[N];

void Set(int v, int l, int r, long long x){
    if (v > 2*t)
        return;
    if (Min[v].l >= l && Min[v].r <= r){
        Min[v].value = x;
        Min[v].change = x;
        Min[v].add = 0;
    }else{
        if (!(Min[v].r < l || Min[v].l > r)){
            if (v < t && Min[v].change != inf) {
                Min[v*2].value = Min[v].change;
                Min[v*2].change = Min[v].change;
                Min[v*2].add = 0;
                Min[v*2 + 1].value = Min[v].change;
                Min[v*2 + 1].change = Min[v].change;
                Min[v*2 + 1].add = 0;
                Min[v].change = inf;
            }
            if (v < t && Min[v].add != 0) {
                Min[v*2].value += Min[v].add;
                if (v*2 < t)
                    Min[v*2].add += Min[v].add;
                Min[v*2 + 1].value += Min[v].add;
                if (v*2 + 1 < t)
                    Min[v*2 + 1].add += Min[v].add;
                Min[v].add = 0;
            }
            Set(v*2, l, r, x);
            Set(v*2 + 1, l, r, x);
            Min[v].value = min(Min[v*2].value, Min[v*2 + 1].value);
        }
    }
}

void add(int v, int l, int r, long long x){
    if (v > 2*t)
        return;
    if (Min[v].l >= l && Min[v].r <= r){
        Min[v].value += x;
        if (v < t)
            Min[v].add += x;
    }else{
        if (!(Min[v].r < l || Min[v].l > r)){
            if (v < t && Min[v].change != inf) {
                Min[v*2].value = Min[v].change;
                Min[v*2].change = Min[v].change;
                Min[v*2].add = 0;
                Min[v*2 + 1].value = Min[v].change;
                Min[v*2 + 1].change = Min[v].change;
                Min[v*2 + 1].add = 0;
                Min[v].change = inf;
            }
            if (v < t && Min[v].add != 0) {
                Min[v*2].value += Min[v].add;
                if (v*2 < t)
                    Min[v*2].add += Min[v].add;
                Min[v*2 + 1].value += Min[v].add;
                if (v*2 + 1 < t)
                    Min[v*2 + 1].add += Min[v].add;
                Min[v].add = 0;
            }
            add(v*2, l, r, x);
            add(v*2 + 1, l, r, x);
            Min[v].value = min(Min[v*2].value, Min[v*2 + 1].value);
        }
    }
}

long long getMin(int v, int l, int r){
    if (Min[v].l >= l && Min[v].r <= r)
        return Min[v].value;
    if (t <= v && v < 2*t)
        return inf;
    if (!(Min[v].r < l || Min[v].l > r)){
        if (v < t && Min[v].change != inf) {
            Min[v*2].value = Min[v].change;
            Min[v*2].change = Min[v].change;
            Min[v*2].add = 0;
            Min[v*2 + 1].value = Min[v].change;
            Min[v*2 + 1].change = Min[v].change;
            Min[v*2 + 1].add = 0;
            Min[v].change = inf;
        }
        if (v < t && Min[v].add != 0) {
            Min[v*2].value += Min[v].add;
            if (v*2 < t)
                Min[v*2].add += Min[v].add;
            Min[v*2 + 1].value += Min[v].add;
            if (v*2 + 1 < t)
                Min[v*2 + 1].add += Min[v].add;
            Min[v].add = 0;
        }
        return min(getMin(v*2, l, r), getMin(v*2 + 1, l, r));
    }
}

int main()
{
    cin >> n;
    while (t < n)
        t *= 2;
    for (int i = t; i < t * 2; i++){
        Min[i].l = i - t + 1;
        Min[i].r = i - t + 1;
        Min[i].value = inf;
    }
    for (int i = 0; i < n; i++){
        cin >> Min[i + t].value;
        Min[i + t].change = Min[i + t].value;
        Min[i + t].add = 0;
    }
    for (int i = t - 1; i > 0; i--){
        Min[i].l = Min[i * 2].l;
        Min[i].r = Min[i * 2 + 1].r;
        Min[i].add = 0;
        Min[i].change = inf;
        Min[i].value = min(Min[i * 2].value, Min[i * 2 + 1].value);
    }
    string m;
    while (cin >> m){
        cout << "before" << endl;
        for (int i = 1; i < 2*t; i++){
            if (Min[i].value == inf)
                cout << "inf,";
            else
                cout << Min[i].value << ',';
            if (Min[i].change == inf)
                cout << "inf,";
            else
                cout << Min[i].change << ',';
            if (Min[i].add == inf)
                cout << "inf   ";
            else
                cout << Min[i].add << "   ";
        }
        cout << endl << "after" << endl;
        int l, r;
        cin >> l >> r;
        if (m == "set"){
            long long x;
            cin >> x;
            Set(1, l, r, x);
        }
        if (m == "min"){
            cout << getMin(1, l, r) << endl;
        }
        if (m == "add"){
            long long x;
            cin >> x;
            add(1, l, r, x);
        }
        for (int i = 1; i < 2*t; i++){
            if (Min[i].value == inf)
                cout << "inf,";
            else
                cout << Min[i].value << ',';
            if (Min[i].change == inf)
                cout << "inf,";
            else
                cout << Min[i].change << ',';
            if (Min[i].add == inf)
                cout << "inf   ";
            else
                cout << Min[i].add << "   ";
        }
        cout << endl;
    }
    return 0;
}
