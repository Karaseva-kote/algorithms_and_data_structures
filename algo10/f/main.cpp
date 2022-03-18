#include <bits/stdc++.h>

using namespace std;

class Point {
public:
    int m_x, m_y;
public:
    Point(int x, int y): m_x(x), m_y(y){}
    Point(const Point &point): m_x(point.m_x), m_y(point.m_y) {
    }
    Point() {}
    Point& operator= (const Point &point) {
        m_x = point.m_x;
        m_y = point.m_y;
        return *this;
    }
    friend istream& operator >> (istream &in, Point &point);
};

istream& operator >> (istream &in, Point &point) {
    in >> point.m_x >> point.m_y;
    return in;
}

class Segment {
public:
    Point a, b;
    bool type;
public:
    Segment(int x1, int y1, int x2, int y2): a(x1, y1), b(x2, y2){
        type = (x1 == x2);
        /*if (type) {
            if (y1 <= y2) {
                a = Point(x1, y1);
                b = Point(x2, y2);
            } else {
                a = Point(x2, y2);
                b = Point(x1, y1);
            }
        } else {
            if (x1 <= x2) {
                a = Point(x1, y1);
                b = Point(x2, y2);
            } else {
                a = Point(x2, y2);
                b = Point(x1, y1);
            }
        }*/
    }
    Segment(const Segment &seg): a(seg.a), b(seg.b), type(seg.type) {
    }
    Segment() {}
    bool cross(Segment other) {
        if(type == other.type) {
            return 0;
        }
        if (type) {
            int minOtherX = min(other.a.m_x, other.b.m_x);
            int maxOtherX = max(other.a.m_x, other.b.m_x);
            int minThisY = min(a.m_y, b.m_y);
            int maxThisY = max(a.m_y, b.m_y);
            if(minOtherX <= a.m_x && a.m_x <= maxOtherX &&
               minThisY <= other.a.m_y && other.a.m_y <= maxThisY) {
                return 1;
            }
        } else {
            int minOtherY = min(other.a.m_y, other.b.m_y);
            int maxOtherY = max(other.a.m_y, other.b.m_y);
            int minThisX = min(a.m_x, b.m_x);
            int maxThisX = max(a.m_x, b.m_x);
            if(minOtherY <= a.m_y && a.m_y <= maxOtherY &&
               minThisX <= other.a.m_x && other.a.m_x <= maxThisX) {
                return 1;
            }
        }
        return 0;
    }

    Segment& operator= (const Segment &seg) {
        a = seg.a;
        b = seg.b;
        type = seg.type;
        return *this;
    }

    friend istream& operator >> (istream &in, Segment &seg);
};

istream& operator >> (istream &in, Segment &seg) {
    /*Point a1, b1;
    in >> a1 >> b1;
    seg.type = (a1.m_x == b1.m_x);
    if (seg.type) {
        if (a1.m_y <= b1.m_y) {
            seg.a = a1;
            seg.b = b1;
        } else {
            seg.a = b1;
            seg.b = a1;
        }
    } else {
        if (a1.m_x <= b1.m_x) {
            seg.a = a1;
            seg.b = b1;
        } else {
            seg.a = b1;
            seg.b = a1;
        }
    }*/
    in >> seg.a >> seg.b;
    seg.type = (seg.a.m_x == seg.b.m_x);
    return in;
}

int n;
vector<Segment> vec;
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
    cin >> n;
    for (int i = 0; i < n; i++) {
        Segment current;
        cin >> current;
        vec.push_back(current);
    }
    leftToRight.resize(n);
    for (int i = 0; i < n; i++) {
        if (vec[i].type) {
            for (int j = 0; j < n; j++) {
                if (vec[i].cross(vec[j])) {
                    leftToRight[i].push_back(j);
                }
            }
        }
    }
    rightToLeft.resize(n, -1);
    mark.resize(n);
    set<int> freeLeftVer;
    for(int i = 0; i < n; i++) {
        if (vec[i].type) {
            freeLeftVer.insert(i);
            fill(mark.begin(), mark.end(), 0);
            dfs(i);
        }
    }
    for (int i = 0; i < n; i++){
        if(!vec[i].type) {
            freeRight.insert(i);
            //cout << "right " << i << endl;
            if (rightToLeft[i] != -1) {
                freeLeftVer.erase(rightToLeft[i]);
            }
        }
    }
    fill(mark.begin(), mark.end(), 0);
    for (set<int>::iterator now = freeLeftVer.begin(); now != freeLeftVer.end(); ++now) {
        //cout << *now << " ";
        dfs2(*now);
    }
    //cout << endl;
    cout << freeLeft.size() + freeRight.size();
    return 0;
}
/*
2
1 1 2 1
3 2 3 3
*/
