#include <bits/stdc++.h>

using namespace std;

const int N = 2*1e5 + 10;
int n, m, main_in_set[N], points[N];
vector <int> sets[N], s;

int find_ (int x){
    return main_in_set[x];
}

void union_ (int x, int y){
    x = find_(x);
    y = find_(y);
    if (x == y)
        return;
    if (sets[x].size() < sets[y].size()){
        swap(x, y);
    }
    for (int i = 0; i < sets[y].size(); i++){
        sets[x].push_back(sets[y][i]);
        main_in_set[sets[y][i]] = x;
    }
    sets[y].clear();
}

void add (int x, int v){
    x = find_(x);
    for (int i = 0; i < sets[x].size(); i++){
        points[sets[x][i]] += v;
    }
}

void get (int x){
    cout << points[x] << endl;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++){
        main_in_set[i] = i;
        sets[i].push_back(i);
    }
    cin >> m;
    for (int i = 0; i < m; i++){
        string s;
        cin >> s;
        if (s == "join"){
            int x, y;
            cin >> x >> y;
            union_(x, y);
        }
        if (s == "add"){
            int x, v;
            cin >> x >> v;
            add(x, v);
        }
        if (s == "get"){
            int x;
            cin >> x;
            get(x);
        }
    }
    return 0;
}
