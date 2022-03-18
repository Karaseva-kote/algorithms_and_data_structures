#include <bits/stdc++.h>

using namespace std;

int n, ans;
vector <pair< int, int> > st;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++){
        int a;
        cin >> a;
        if (st.size() == 0){
            st.push_back({a, 1});
        } else {
            if (st[st.size() - 1].first != a){
                if (st[st.size() - 1].second > 2){
                    ans += st[st.size() - 1].second;
                    st.erase(st.end());
                    if (st[st.size() - 1].first != a){
                        st.push_back({a, 1});
                    } else {
                        st[st.size() - 1].second++;
                    }
                } else {
                    st.push_back({a, 1});
                }
            } else {
                st[st.size() - 1].second++;
            }
        }
    }
    if (st[st.size() - 1].second > 2){
        ans += st[st.size() - 1].second;
    }
    cout << ans;
    return 0;
}
