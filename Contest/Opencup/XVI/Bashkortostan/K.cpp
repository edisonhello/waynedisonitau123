#pragma GCC optimize("O3", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;
 
 
const double eps = 1e-9;
bool same(double a, double b) { return abs(a - b) < eps; }
 
int seg[1004][2][2];
 
bitset<1004> vis;
double mnd[1004];
 
inline int sign(int x) {
    return x == 0 ? 0 : x > 0 ? 1 : -1;
}
inline int crx(int a, int b, int c, int d) {
    return sign(a * d - b * c);
}
 
inline bool intersect(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y, int p4x, int p4y) {
    if (max(p1x, p2x) <= min(p3x, p4x) || max(p3x, p4x) <= min(p1x, p2x)) return false;
    if (max(p1y, p2y) <= min(p3y, p4y) || max(p3y, p4y) <= min(p1y, p2y)) return false;
    return crx(p3x - p1x, p3y - p1y, p4x - p1x, p4y - p1y) * crx(p3x - p2x, p3y - p2y, p4x - p2x, p4y - p2y) < 0 && crx(p1x - p3x, p1y - p3y, p2x - p3x, p2y - p3y) * crx(p1x - p4x, p1y - p4y, p2x - p4x, p2y - p4y) < 0;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
 
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> seg[i][0][0] >> seg[i][0][1] >> seg[i][1][0] >> seg[i][1][1];
    for (int i = 1; i < n; ++i) mnd[i] = 1e9;
 
    double ans = 0;
    int s = 0;
    while (s < n) {
        double mn = 1e9 + 87;
        int who = 0;
        for (int i = 0; i < n; ++i) if (!vis[i] && mnd[i] < mn) {
            mn = mnd[i];
            who = i;
        }
        ++s;
 
        vis[who] = 1;
        ans += mn;
        int now = who;
 
        vector<int> od(n);
        iota(od.begin(), od.end(), 0);
        random_shuffle(od.begin(), od.end());
 
        for (int i = 0; i < n; ++i) if (!vis[i]) {
            for (int y = 0; y < 2; ++y) { // seg[now][y]
                for (int z = 0; z < 2; ++z) { // seg[i][z]
                    bool ok = true;
                    for (int x : od) if (x != i && x != now) {
                        if (intersect(seg[now][y][0], seg[now][y][1], seg[i][z][0], seg[i][z][1],
                                    seg[x][0][0], seg[x][0][1], seg[x][1][0], seg[x][1][1])) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) mnd[i] = min(mnd[i], hypot((double)seg[now][y][0] - seg[i][z][0], (double)seg[i][z][1] - seg[now][y][1]));
                }
            }
        }
    }
 
    cout << fixed << setprecision(12) << ans << endl;
}
