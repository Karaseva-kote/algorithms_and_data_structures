#include <bits/stdc++.h>

using namespace std;

const int N = 3*1e5 + 10;
int n, pr[N], sz[N], mx[N], mn[N];

int find_x (int x){
    int X = x;
    while (pr[X] != X){
        X = pr[X];
    }
    return X;
}

void union_x_y (int x, int y){
    int X = find_x(x), Y = find_x(y);
    if (X == Y)
        return;
    if (sz[X] > sz[Y])
        swap(X, Y);
    pr[X] = Y;
    sz[Y] += sz[X];
    mx[Y] = max(mx[Y], mx[X]);
    mn[Y] = min(mn[Y], mn[X]);
}

void get (int x){
    int X = find_x(x);
    cout << mn[X] << ' ' << mx[X] << ' ' << sz[X] << endl;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++){
        pr[i] = i;
        sz[i] = 1;
        mx[i] = i;
        mn[i] = i;
    }
    string f;
    while(cin >> f){
        if (f == "union"){
            int x, y;
            cin >> x >> y;
            union_x_y(x, y);
        }
        if (f == "get"){
            int x;
            cin >> x;
            get(x);
        }
    }
    return 0;
}
