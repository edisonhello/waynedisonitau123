#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);
const double eps = 1e-8;

int pos[100005][3][2];

void center(double ax, double ay, double bx, double by, double cx, double cy, double &x, double &y) {
    double a1 = atan2(by - ay, bx - ax) + pi / 2;
    double a2 = atan2(cy - by, cx - bx) + pi / 2;
    ax = (ax + bx) / 2;
    ay = (ay + by) / 2;
    bx = (cx + bx) / 2;
    by = (cy + by) / 2;
    double r1 = (sin(a2) * (ax - bx) + cos(a2) * (by - ay)) / (sin(a1) * cos(a2) - sin(a2) * cos(a1));
    x = ax + r1 * cos(a1), y = ay + r1 * sin(a1);
}

void check(int id, int px, int py) {
    int x[3] = {pos[id][0][0], pos[id][1][0], pos[id][2][0]};
    int y[3] = {pos[id][0][1], pos[id][1][1], pos[id][2][1]};
    double cx, cy;
    center(pos[id][0][0], pos[id][0][1], pos[id][1][0], pos[id][1][1], pos[id][2][0], pos[id][2][1], cx, cy);
    double r = hypot(x[0] - cx, y[0] - cy);
    if (hypot(px - cx, py - cy) < r - eps) {
        cout << "NO" << endl;
        exit(0);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n; 
    vector<pair<int, int>> v;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> pos[i][j][0] >> pos[i][j][1];
            v.emplace_back(pos[i][j][0], pos[i][j][1]);
        }
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    for (int i = 1; i <= n; ++i) {
        for (auto p : v) check(i, p.first, p.second);
    }
    cout << "YES" << endl;
}
