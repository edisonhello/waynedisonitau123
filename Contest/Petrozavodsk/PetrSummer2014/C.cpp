#include <bits/stdc++.h>
using namespace std;
#define int long long

struct P {
    int x, y; 
    P operator+ (const P b) {
        return P{x + b.x, y + b.y};
    }
    P operator- (const P b) {
        return P{x - b.x, y - b.y};
    }
    P operator/ (const int b) {
        return P{x / b, y / b};
    }
    int operator^ (const P b) {
        return x * b.y - y * b.x;
    }
};


bool operator< (const P &a, const P &b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
}

bool sameside(pair<P, P> line, set<P> &ps) {
    P dir = line.second - line.first;
    int z = 0;
    for (auto p : ps) {
        P vec = p - line.first;
        int res = vec ^ dir;
        if (z * res < 0) {
            return false;
        }
        if (res) {
            z = res > 0 ? 1 : -1;
        }
    }
    return true;
}

set<P> input() {

    set<P> st;

    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    x1 *= 2;
    x2 *= 2;
    y1 *= 2;
    y2 *= 2;
    P dir = P{x2, y2} - P{x1, y1};
    dir = dir / 2;
    P ddir = P{dir.y, -dir.x};

    st.insert(P{x1, y1});
    st.insert(P{x2, y2});
    st.insert(P{x1, y1} + dir + ddir);
    st.insert(P{x1, y1} + dir - ddir);
    return st;
}

int32_t main() {
    freopen("equal-squares.in", "r", stdin);
    freopen("equal-squares.out", "w", stdout);

    set<P> s1 = input(), s2 = input();


    int same = 0;
    for (auto p : s2) {
        if (s1.count(p)) ++same;
    }

    if (same == 1) {
        cout << "Infinity" << endl;
        exit(0);
    }

    if (same == 2) {
        cout << 3 << endl;
        exit(0);
    }

    set<tuple<int, int, int>> lines;
    for (auto p1 : s1) {
        for (auto p2 : s2) {
            pair<P, P> line(p1, p2);
            
            if (sameside(line, s1) && sameside(line, s2)) {
                int a = p1.y - p2.y, b = p2.x - p1.x, c = p1 ^ p2;
                int g = __gcd(__gcd(a, b), c);
                a /= g; 
                b /= g;
                c /= g;
                if (a < 0) a *= -1, b *= -1, c *= -1;
                else if (a == 0 && b < 0) b *= -1, c *= -1;
                else if (a == 0 && b == 0 && c < 0) c *= -1;

                lines.insert(make_tuple(a, b, c));
            }
        }
    }

    cout << lines.size() << endl;

}

