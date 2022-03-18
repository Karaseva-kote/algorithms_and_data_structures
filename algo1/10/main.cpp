#include <bits/stdc++.h>

using namespace std;

const long double eps = 1e-9;
long double a, vp, vf;

long double f (long double x){
    return (x/(vp*sqrt(x*x + (1-a)*(1-a))) + (x-1)/(vf*sqrt((1-x)*(1-x) + a*a)));
}

long double find_point (){
    long double l = 0, r = 1;
    while (r - l > eps){
        long double m = (r+l)/2;
        if (f(m) > 0)
            r = m;
        else
            l = m;
    }
    return l;
}

int main()
{
    cin >> vp >> vf >> a;
    cout << find_point();
    return 0;
}
