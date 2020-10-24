#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int sx, sy, tx, ty; cin >> sx >> sy >> tx >> ty;
        int vf, vp, vh; cin >> vf >> vp >> vh;
        int n; cin >> n;
        vector<tuple<int, int, int>> pt;
        for (int i = 0; i < n + 1; ++i) {
            int x, y, v; cin >> x >> y >> v;
            if (v <= vp) continue;
            if (pt.size() && v <= get<0>(pt[0])) continue;
            pt.emplace_back(v, x, y);
        }
        pt.emplace_back(10004, tx, ty);
        sort(pt.begin(), pt.end());

        vector<double> d(pt.size(), 1e18);
        d[0] = 0;

        for (int i = 1; i < (int)pt.size(); ++i) {
            int v, x, y; tie(v, x, y) = pt[i];
            for (int j = 0; j < i; ++j) {
                // j to i
                int vv, xx, yy; tie(vv, xx, yy) = pt[j];
                double dist = hypot(xx - x, yy - y);
                double t = dist / vh * vv / (vv - vp);
                d[i] = min(d[i], d[j] + t);
            }
        }

        cout << fixed << setprecision(12);
        cout << d.back() << '\n';
    }
}

