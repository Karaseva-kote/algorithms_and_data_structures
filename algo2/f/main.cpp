#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;
int n, p1, p2, st1[N], st2[N];
vector <string> ans;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++){
        int a;
        cin >> a;
        if (p1 == 0){
            st1[p1] = a;
            p1++;
            ans.push_back("push");
        } else {
            if (st1[p1 - 1] >= a){
                st1[p1] = a;
                p1++;
                ans.push_back("push");
            } else {
                while (p1 > 0){
                    if (st1[p1 - 1] < a){
                        st2[p2] = st1[p1 - 1];
                        p2++;
                        p1--;
                        ans.push_back("pop");
                    } else {
                        break;
                    }
                }
                st1[p1] = a;
                p1++;
                ans.push_back("push");
            }
        }
    }
    while(p1 > 0){
        st2[p2] = st1[p1 - 1];
        p2++;
        p1--;
        ans.push_back("pop");
    }
    for(int i = 1; i < n; i++){
        if (st2[i] < st2[i - 1]){
            cout << "impossible";
            return 0;
        }
    }
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << endl;
    return 0;
}
