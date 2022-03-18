#include <bits/stdc++.h>

using namespace std;

struct point {
    int x;
    int y;
};

istream& operator>>(istream& is, point& p) {
      is >> p.x >> p.y;
      return is;
}

const int N = 10050;
double inf = -1;
int n;
point a[N];
bool used[N];
double SUM;
double minedge[N];

void search_tree () {
    for (int i = 1; i < n; i++) {
        int v = 1;
        for (int j = 1; j <= n; j++) {
            if (!used[j] && minedge[j] != inf && (v == 1 || minedge[j] < minedge[v]))
                v = j;
        }
        used[v] = 1;
        for (int j = 1; j <= n; j++) {
            if (v != j) {
                double W = sqrt((a[v].x - a[j].x) * (a[v].x - a[j].x) + (a[v].y - a[j].y) * (a[v].y - a[j].y));
                if (!used[j] && (minedge[j] > W || minedge[j] == inf)) {
                    minedge[j] = W;
                }
            }
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        minedge[i] = inf;
    }
    for (int i = 2; i <= n; i++) {
        double W = sqrt((a[1].x - a[i].x) * (a[1].x - a[i].x) + (a[1].y - a[i].y) * (a[1].y - a[i].y));
        if (minedge[i] == inf || minedge[i] > W)
            minedge[i] = W;
    }
    minedge[1] = 0;
    used[1] = 1;
    search_tree();
    for (int i = 1; i <= n; i++) {
        SUM += minedge[i];
    }
    cout.precision(8);
    cout << fixed << SUM;
    return 0;
}
