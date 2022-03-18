#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
int n, num_in_q[N], q[N], head, tail;


int main()
{
    cin >> n;
    for (int i = 0; i < n; i++){
        int f;
        cin >> f;
        if (f == 1){
            int id;
            cin >> id;
            q[tail] = id;
            num_in_q[id] = tail;
            tail++;
        }
        if (f == 2){
            head++;
        }
        if (f == 3){
            tail--;
        }
        if (f == 4){
            int id;
            cin >> id;
            cout << num_in_q[id] - head << endl;
        }
        if (f == 5){
            cout << q[head] << endl;
        }
    }
    return 0;
}
