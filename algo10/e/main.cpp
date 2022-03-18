#include <bits/stdc++.h>

using namespace std;

long long n, m, a, b;
vector<vector<bool> > table;
vector<vector<long long> > leftToRight;
vector<long long> rightToLeft;
vector<bool> mark;

bool dfs(long long v) {
    if(mark[v]) {
        return 0;
    }
    mark[v] = 1;
    for (long long i = 0; i < leftToRight[v].size(); i++) {
        long long u = leftToRight[v][i];
        if (rightToLeft[u] == -1 || dfs(rightToLeft[u])) {
            rightToLeft[u] = v;
            return 1;
        }
    }
    return 0;
}

int main()
{
    cin >> n >> m >> a >> b;
    table.resize(n, vector<bool>(m));
    long long cntEmpty = 0;
    for(long long i = 0; i < n; i++) {
        for(long long j = 0; j < m; j++) {
            char mark;
            cin >> mark;
            if(mark == '.') {
                table[i][j] = 0;
            } else {
                table[i][j] = 1;
                cntEmpty++;
            }
        }
    }
    if (2*b <= a) {
        cout << b*cntEmpty;
        return 0;
    }
    leftToRight.resize(n*m);
    rightToLeft.resize(n*m, -1);
    for(long long i = 0; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            if(table[i][j] && (i + j)%2){
                if (i > 0 && table[i - 1][j]) {
                    leftToRight[i*m + j].push_back((i-1)*m + j);
                }
                if(i + 1 < n && table[i + 1][j]) {
                    leftToRight[i*m + j].push_back((i+1)*m + j);
                }
                if(j > 0 && table[i][j - 1]) {
                    leftToRight[i*m + j].push_back(i*m + j - 1);
                }
                if(j + 1 < m && table[i][j + 1]) {
                    leftToRight[i*m + j].push_back(i*m + j + 1);
                }
            }
        }
    }
    mark.resize(n*m);
    for(long long i = 0; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            if((i + j)%2 && table[i][j]) {
                fill(mark.begin(), mark.end(), 0);
                dfs(i*m + j);
            }
        }
    }
    long long ans = 0;
    long long cnt = 0;
    for(long long i = 0; i < n; i++) {
        for (long long j = 0; j < m; j++) {
            if((!((i + j)%2)) && table[i][j]) {
                if(rightToLeft[i*m + j] != -1) {
                    ans += a;
                    cnt++;
                }
            }
        }
    }
    ans += ((cntEmpty - cnt*2)*b);
    cout << ans;
    return 0;
}
