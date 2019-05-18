#include <bits/stdc++.h>
using namespace std;

long long sgn(long long x) {
    if (x > 0) return 1;
    return -1;
}

struct point {
    long long x, y;
};

point operator-(const point &a, const point &b) {
    return point{a.x - b.x, a.y - b.y};
}
point operator+(const point &a, const point &b) {
    return point{a.x + b.x, a.y + b.y};
}
long long operator*(const point a, const point b) {
    return a.x * b.x + a.y * b.y;
}
long long operator^(const point a, const point b) {
    return a.x * b.y - a.y * b.x;
}
long long abs(point p) {
    return p.x * p.x + p.y * p.y;
}

bool same_line(point a, point b, point c) {
    if ((c - a) ^ (b - a)) return false;
    if ((c - b) * (a - b) <= 0) return true;
    return false;
}

point wl[1005][2], pl[1005][2];

int main() {
    // cout << same_line(point{0,0}, point{2,0}, point{1,0}) << endl;
    ios_base::sync_with_stdio(0); cin.tie(0);
    int w, p; cin >> w >> p;
    point tr; cin >> tr.x >> tr.y;
    for (int i = 0; i < w; ++i) cin >> wl[i][0].x >> wl[i][0].y >> wl[i][1].x >> wl[i][1].y;
    for (int i = 0; i < p; ++i) cin >> pl[i][0].x >> pl[i][0].y >> pl[i][1].x >> pl[i][1].y;
    for (int i = 0; i < p; ++i) {
        if ((tr - pl[i][0]) * (pl[i][1] - pl[i][0]) < 0) { // if dot < 0, wrong direction
            cout << "not visible" << '\n';
            continue;
        }
        if (abs(tr - pl[i][0]) > abs(pl[i][1] - pl[i][0])) { // if treasure is to far
            cout << "not visible" << '\n';
            continue;
        }
        bool block = false;
        for (int j = 0; j < p; ++j) if (i != j) {
            if (same_line(pl[i][0], pl[j][0], tr)) block = true;
        }
        for (int j = 0; j < w; ++j) {
            if (same_line(pl[i][0], wl[j][0], tr) || same_line(pl[i][0], wl[j][1], tr)) block = true;
            // cerr << "crss: " << sgn((wl[j][0] - pl[i][0]) ^ (tr - pl[i][0])) << " , " << sgn((wl[j][1] - pl[i][0]) ^ (tr - pl[i][0])) << endl;
            if (sgn((pl[i][0] - wl[j][0]) ^ (tr - wl[j][0])) * sgn((pl[i][0] - wl[j][1]) ^ (tr - wl[j][1])) == -1 &&
                sgn((wl[j][0] - pl[i][0]) ^ (wl[j][1] - pl[i][0])) * sgn((wl[j][0] - tr) ^ (wl[j][1] - tr)) == -1) { // treasure between two wall
                long long area = abs((wl[j][0] - pl[i][0]) ^ (wl[j][1] - pl[i][0]));
                // cerr << "Area : " << area << endl;
                if (area) {
                    long long area1 = abs((wl[j][0] - tr) ^ (wl[j][1] - tr));
                    long long area2 = abs((wl[j][1] - tr) ^ (pl[i][0] - tr));
                    long long area3 = abs((pl[i][0] - tr) ^ (wl[j][0] - tr));
                    if (area1 + area2 + area3 != area) block = true;
                }
            }
        }
        if (block) cout << "not visible" << '\n';
        else cout << "visible" << '\n';
    }
}
