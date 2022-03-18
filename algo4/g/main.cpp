#include <bits/stdc++.h>

using namespace std;

struct point {
    int x;
    int y;
    bool open;
    point(int x1, int y1, bool op) {
        x = x1;
        y = y1;
        open = op;
    }
};

void print(point a) {
    if (a.open)
        cout << "(" << a.x << ", " << a.y << ") ";
    else
        cout << "[" << a.x << ", " << a.y << "] ";
}

bool cmp(point a, point b) {
    if (a.x < b.x)
        return 1;
    if (a.x == b.x)
        return !a.open;
    return 0;
}

const int N = 8;
int n;
vector<point> v;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x1, y1;
        cin >> x1 >> y1;
        v.push_back(point(x1, y1, 1));
        cin >> x1 >> y1;
        v.push_back(point(x1, y1, 0));
    }
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < v.size(); i++) {
        print(v[i]);
    }
    return 0;
}
