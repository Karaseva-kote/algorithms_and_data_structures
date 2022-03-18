#include <bits/stdc++.h>

using namespace std;

const int N = 101;
int a[N], b;

int main()
{
     while(cin >> b){
        a[b]++;
     }
     for (int i = 0; i < 101; i++){
        for (int j = 0; j < a[i]; j++){
            cout << i << ' ';
        }
     }
    return 0;
}
