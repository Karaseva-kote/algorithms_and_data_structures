#include <bits/stdc++.h>

using namespace std;

bool dfs(int v, vector<vector<bool> > &table, vector<bool> &mark, vector<int> &rightToLeft) {
    if(mark[v]) {
        return 0;
    }
    mark[v] = 1;
    for (int u = 0; u < table[v].size(); u++) {
        if(table[v][u]) {
            if (rightToLeft[u] == -1 || dfs(rightToLeft[u], table, mark, rightToLeft)) {
                rightToLeft[u] = v;
                return 1;
            }
        }
    }
    return 0;
}

void dfs2(int v, vector<vector<bool> > &table, vector<bool> &mark, vector<int> &rightToLeft, set<int> &freeBoys, set<int> &freeGirls) {
    if(mark[v]){
        return;
    }
    mark[v] = 1;
    freeBoys.insert(v);
    for (int u = 0; u < table[v].size(); u++) {
        if(table[v][u]) {
            freeGirls.erase(u);
            if (rightToLeft[u] != -1) {
                dfs2(rightToLeft[u], table, mark, rightToLeft, freeBoys, freeGirls);
            }
        }
    }
}

int main()
{
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int m, n;
        cin >> m >> n;
        vector<vector<bool> > table(m, vector<bool>(n, 1));
        for (int j = 0; j < m; j++) {
            int a;
            while(cin >> a) {
                if(a == 0) {
                    break;
                }
                table[j][a - 1] = 0;
            }
        }
        vector<int> match(n, -1);
        set<int> freeV;
        for (int j = 0; j < m; j++) {
            freeV.insert(j);
            vector<bool> used(m, 0);
            dfs(j, table, used, match);
        }
        set<int> freeGirls;
        set<int> freeBoys;
        for (int j = 0; j < n; j++) {
            freeGirls.insert(j);
            if(match[j] != -1) {
                freeV.erase(match[j]);
            }
        }
        vector<bool> used2(m, 0);
        for(set<int>::iterator now = freeV.begin(); now != freeV.end(); ++now) {
            dfs2(*now, table, used2, match, freeBoys, freeGirls);
        }
        cout << freeBoys.size() + freeGirls.size() << endl;
        cout << freeBoys.size() << " " << freeGirls.size() << endl;
        for(set<int>::iterator now = freeBoys.begin(); now != freeBoys.end(); ++now) {
            cout << *now + 1 << " ";
        }
        cout << endl;
        for(set<int>::iterator now = freeGirls.begin(); now != freeGirls.end(); ++now) {
            cout << *now + 1 << " ";
        }
        cout << endl << endl;
    }
    return 0;
}
