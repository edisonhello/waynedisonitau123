#include <bits/stdc++.h>
using namespace std;



int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, w, u, v, t1, t2; cin >> n >> w >> u >> v >> t1 >> t2;
    set<pair<double, double>> no;
    no.insert(make_pair(-10000000, t1));
    no.insert(make_pair(t2, 10000000));
    for (int i = 1; i <= n; ++i) {
        char c; cin >> c;
        int m; cin >> m;
        for (int j = 1; j <= m; ++j) {
            int l, p; cin >> l >> p;
            if (c == 'E') p *= -1;
            auto np = make_pair((double)p / u - (double)w / v * i,
                                (double)(p + l) / u - (double)w / v * (i - 1));
            no.insert(np);
        }
    }

    double now = -5000000;
    double mx = 0;
    for (auto p : no) {
        if (p.first <= now) now = max(now, p.second);
        else {
            mx = max(mx, p.first - now);
            now = p.second;
        }
    }

    cout << fixed << setprecision(10) << mx << endl;
}

