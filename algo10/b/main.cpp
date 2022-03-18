#include <bits/stdc++.h>

using namespace std;

long long n, m, e;
vector<long long> wn, wm;
vector<vector<long long> > leftToRight, boofer, rev;
vector<long long> rightToLeft, try1, try2;
vector<bool> mark;
vector<long long> ans;
vector<pair<long long, long long> > orderL, orderR;
map<pair<long long, long long>, long long> edge;

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
    cin >> n >> m >> e;
    wn.resize(n);
    for (long long i = 0; i < n; i++) {
        cin >> wn[i];
        orderL.push_back({wn[i], i});
    }
    sort(orderL.begin(), orderL.end());
    wm.resize(m);
    for (long long i = 0; i < m; i++) {
        cin >> wm[i];
        orderR.push_back({wm[i], i});
    }
    sort(orderR.begin(), orderR.end());
    leftToRight.resize(n);
    boofer.resize(n);
    rev.resize(m);
    for(long long i = 0; i < e; i++) {
        long long a, b;
        cin >> a >> b;
        edge.insert({{a - 1, b - 1}, i + 1});
        leftToRight[a - 1].push_back(b - 1);
        rev[b - 1].push_back(a - 1);
        boofer[a - 1].push_back(b - 1);
    }
    rightToLeft.resize(m, -1);
    mark.resize(n);
    for (long long v = n - 1; v >= 0; v--) {
        fill(mark.begin(), mark.end(), 0);
        dfs(orderL[v].second);
    }
    copy(rightToLeft.begin(), right.end(),
              std::back_inserter(to_vector));try1 = rightToLeft;
    leftToRight.clear();
    leftToRight = rev;
    cout << W << endl;
    cout << ans.size() << endl;
    for (long long i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
