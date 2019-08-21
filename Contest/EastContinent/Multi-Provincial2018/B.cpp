#include <bits/stdc++.h>
using namespace std;


int main() {
    int t; cin >> t; for (int tt = 1; tt <= t; ++tt) {
        vector<pair<int, int>> v;
        int n; cin >> n;
        v.resize(n);
        for (int i = 0; i < n; ++i) cin >> v[i].first >> v[i].second;
        int x, y; cin >> x >> y;
        double sum = 0;
        for (int i = 0; i < n; ++i) {
            int a = (i - 1 + n) % n;
            int b = i;
            int c = (i + 1) % n;
            int x1 = v[a].first - v[b].first;
            int y1 = v[a].second - v[b].second;
            int x2 = v[c].first - v[b].first;
            int y2 = v[c].second - v[b].second;
            double ang = acos((x1 * x2 + y1 * y2) / hypot((double)x1, (double)y1) / hypot((double)x2, (double)y2));
            ang = acos(-1) - ang;
            sum += ang * hypot((double)x - v[b].first, (double)y - v[b].second);
            // cerr << "ang = " << ang << endl;
        }


        cout << "Case #" << tt << ": ";
        cout << fixed << setprecision(3) << sum << endl;
    }
}
