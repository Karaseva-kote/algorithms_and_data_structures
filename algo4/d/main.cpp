#include <bits/stdc++.h>

using namespace std;

struct p {
    int l;
    int r;
    int len;
    int colleft;
    int colright;
    int cntBlack;
    int cntLine;
    bool change;
};

const int N = 4194303, t = 2097152, mn = -1000010;
p tree[N];

void paint (int v, int l, int r, int col) {
    //cout << "// " << tree[v].l << ' ' << tree[v].r << ' ' << tree[v].len << endl;
    if (r < tree[v].l || tree[v].r < l) {
        return;
    }
    if (v >= t) {
        tree[v].cntBlack = col;
        tree[v].cntLine = col;
        tree[v].colleft = col;
        tree[v].colright = col;
        //cout << "in " << tree[v].cntBlack << endl;
        return;
    }
    if (l <= tree[v].l && tree[v].r <= r) {
        tree[v].colleft = col;
        tree[v].colright = col;
        if (col == 1) {
            tree[v].cntBlack = tree[v].len;
            tree[v].cntLine = 1;
        } else {
            tree[v].cntBlack = 0;
            tree[v].cntLine = 0;
        }
        tree[v].change = 1;
        //cout << "in " << tree[v].cntBlack << endl;
        return;
    }
    if (tree[v].change) {
        tree[2*v].change = 1;
        tree[2*v].colleft = tree[v].colleft;
        tree[2*v].colright = tree[v].colright;
        if (tree[2*v].colleft == 1) {
            tree[2*v].cntBlack = tree[2*v].len;
            tree[2*v].cntLine = 1;
        } else {
            tree[2*v].cntBlack = 0;
            tree[2*v].cntLine = 0;
        }
        tree[2*v + 1].change = 1;
        tree[2*v + 1].colleft = tree[v].colleft;
        tree[2*v + 1].colright = tree[v].colright;
        if (tree[2*v + 1].colleft == 1) {
            tree[2*v + 1].cntBlack = tree[2*v + 1].len;
            tree[2*v + 1].cntLine = 1;
        } else {
            tree[2*v + 1].cntBlack = 0;
            tree[2*v + 1].cntLine = 0;
        }
        tree[v].change = 0;
    }
    paint(2*v, l, r, col);
    paint(2*v + 1, l, r, col);
    tree[v].colleft = tree[v*2].colleft;
    tree[v].colright = tree[v*2 + 1].colright;
    tree[v].cntBlack = tree[v*2].cntBlack + tree[v*2 + 1].cntBlack;
    tree[v].cntLine = tree[v*2].cntLine + tree[v*2 + 1].cntLine;
    if (tree[v*2].colright == tree[v*2 + 1].colleft && tree[v*2].colright == 1)
        tree[v].cntLine--;
    //cout << tree[v].l << ' ' << tree[v].r << ' ' << tree[v].len << endl;
    //cout << "out " << tree[v].cntBlack << endl;
    return;
}

int main()
{
    int n;
    cin >> n;
    for (int i = t; i < 2*t; i++) {
        tree[i].l = mn + i - t;
        tree[i].r = mn + i - t;
        tree[i].len = 1;
        tree[i].colleft = 0;
        tree[i].colright = 0;
        tree[i].cntBlack = 0;
        tree[i].cntLine = 0;
        tree[i].change = 0;
    }
    for (int i = t - 1; i > 0; i--) {
        tree[i].l = tree[2*i].l;
        tree[i].r = tree[2*i + 1].r;
        tree[i].len = tree[2*i].len + tree[2*i + 1].len;
        tree[i].colleft = 0;
        tree[i].colright = 0;
        tree[i].cntBlack = 0;
        tree[i].cntLine = 0;
        tree[i].change = 0;
    }
    for (int i = 0; i < n; i++) {
        char c;
        int x, l, col = 0;
        cin >> c >> x >> l;
        if (c == 'B')
            col = 1;
        paint(1, x, x + l - 1, col);
        cout << tree[1].cntLine << ' ' << tree[1].cntBlack << endl;
    }
    return 0;
}
