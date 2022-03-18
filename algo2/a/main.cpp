#include <bits/stdc++.h>

using namespace std;

int n;
vector <pair<int, int> > st;

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++){
        int f, a;
        cin >> f;
        if (f == 1){
            cin >> a;
            if (st.size() == 0){
                st.push_back({a, a});
            } else {
                st.push_back({a, min(a, st[st.size() - 1].second)});
            }
        }
        if (f == 2){
            st.erase(st.end());
        }
        if (f == 3){
            cout << st[st.size() - 1].second << endl;
        }
    }
    return 0;
}
