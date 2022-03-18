#include <bits/stdc++.h>

using namespace std;

int n;
double v;

class Event {
public:
    double m_x, m_y;
    int m_time;
    Event(int time, double x, double y): m_x(x), m_y(y), m_time(time){}
    Event(const Event &event): m_x(event.m_x), m_y(event.m_y), m_time(event.m_time) {}
    Event() {}
    Event& operator= (const Event &event) {
        m_x = event.m_x;
        m_y = event.m_y;
        m_time = event.m_time;
        return *this;
    }

    bool achievable(Event event) {
        if (m_time >= event.m_time) {
            return 0;
        }
        double distance = sqrt((m_x - event.m_x)*(m_x - event.m_x) + (m_y - event.m_y)*(m_y - event.m_y));
        if ((distance/v)*60 > (event.m_time - m_time)) {
            return 0;
        }
        return 1;
    }
};

vector<Event> vec;
vector<vector<int> > leftToRight;
vector<int> rightToLeft;
vector<bool> mark;
set<int> freeLeft, freeRight;

bool dfs(int v) {
    if(mark[v]) {
        return 0;
    }
    mark[v] = 1;
    for (int i = 0; i < leftToRight[v].size(); i++) {
        int u = leftToRight[v][i];
        if (rightToLeft[u] == -1 || dfs(rightToLeft[u])) {
            rightToLeft[u] = v;
            return 1;
        }
    }
    return 0;
}

void dfs2(int v) {
    if(mark[v]){
        return;
    }
    mark[v] = 1;
    freeLeft.insert(v);
    for (int i = 0; i < leftToRight[v].size(); i++) {
        int u = leftToRight[v][i];
        freeRight.erase(u);
        if (rightToLeft[u] != -1) {
            dfs2(rightToLeft[u]);
        }
    }
}

int main()
{
    cin >> n >> v;
    for (int i = 0; i < n; i++) {
        string s;
        double x, y;
        cin >> s >> x >> y;
        vec.push_back(Event(((s[0] - '0')*10 + s[1] - '0')*60 + (s[3] - '0')*10 + s[4] - '0', x, y));
    }
    leftToRight.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (vec[i].achievable(vec[j])) {
                leftToRight[i].push_back(j);
            }
        }
    }
    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < leftToRight[i].size(); j++) {
            cout << leftToRight[i][j] << " ";
        }
        cout << endl;
    }*/
    rightToLeft.resize(n, -1);
    mark.resize(n);
    set<int> freeLeftVer;
    for(int i = 0; i < n; i++) {
        freeLeftVer.insert(i);
        fill(mark.begin(), mark.end(), 0);
        dfs(i);
    }
    for (int i = 0; i < n; i++){
        //cout << rightToLeft[i] << " ";
        freeRight.insert(i);
        if (rightToLeft[i] != -1) {
            freeLeftVer.erase(rightToLeft[i]);
        }
    }
    //cout << endl;
    fill(mark.begin(), mark.end(), 0);
    for (set<int>::iterator now = freeLeftVer.begin(); now != freeLeftVer.end(); ++now) {
        dfs2(*now);
    }
    cout << freeLeft.size() + freeRight.size() - n;
    return 0;
}
