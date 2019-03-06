#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;

struct point {
    int x, y;
    point(int x = 0, int y = 0): x(x), y(y) {}
};

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, m; scanf("%d%d", &n, &m);
        vector<point> p(n), light(m);
        for (int i = 0; i < n; ++i) scanf("%d%d", &p[i].x, &p[i].y);
        for (int i = 0; i < m; ++i) scanf("%d%d", &light[i].x, &light[i].y);
        vector<pair<int, int>> seg;
        for (int i = 0; i < m; ++i) {
            /* vector<double> ang(n);
            for (int j = 0; j < n; ++j) {
                ang[j] = atan2(light[i].y - p[j].y, light[i].x - p[j].x); 
            }
            vector<int> ord(n);
            for (int i = 0; i < n; ++i) ord[i] = i;
            sort(ord.begin(), ord.end(), [&](int a, int b) {
                return ang[a] < ang[b];
            }); */
            vector<double> angle;
            for (int j = 0; j < n; ++j) {
                int dx = p[j].x - light[i].x;
                int dy = p[j].y - light[i].y;
                double ang = atan2(dy, dx);
                angle.push_back(ang);
            }
            double mx = -100, mn = 100;
            for (auto d : angle) mx = max(mx, d), mn = min(mn, d);
            if (mx - mn > acos(-1)) {
                for (auto &d : angle) if (d < 0) d += acos(-1) * 2;
            }
            mx = -100, mn = 100;
            for (auto d : angle) mx = max(mx, d), mn = min(mn, d);
            int mxi = -1, mni = -1;
            for (int i = 0; i < n; ++i) if (fabs(angle[i] - mx) < 1e-9) mxi = i; else if (fabs(angle[i] - mn) < 1e-9) mni = i;
            seg.emplace_back(mxi, mni);
        }
        vector<int> sorted(m);
        for (int i = 0; i < m; ++i) sorted[i] = i;
        sort(sorted.begin(), sorted.end(), [&](int i, int j) {
            return seg[i] < seg[j];
        });
        sort(seg.begin(), seg.end());
        int ans = INT_MAX;
        vector<int> fin;
        for (int i = 0; i < m; ++i) {
            int k = (i + 1) % m, res = 1;
            vector<pair<int, int>> v(seg.begin(), seg.end());
            int l = seg[i].first;
            for (int j = 0; j < (int)v.size(); ++j) {
                v[j].first -= l;
                v[j].second -= l;
                if (v[j].first < 0) v[j].first += n;
                if (v[j].second < 0) v[j].second += n;
                if (v[j].second < v[j].first) v[j].second += n;
            }
            /* printf("i = %d\n", i);
            for (int j = 0; j < m; ++j) {
                printf("(%d, %d)\n", v[j].first, v[j].second);
            } */
            int f = v[i].second, covered = v[i].second - v[i].first;
            vector<int> take = {sorted[i]};
            bool good = true;
            while (covered < n && k != i) {
                int nxt = f;
                ++res;
                int which = -1;
                while (k != i && v[k].first <= f) {
                    if (v[k].second > nxt) {
                        nxt = v[k].second;
                        which = k;
                    }
                    if (++k >= m) k -= m;
                }
                if (which == -1) {
                    good = false;
                    break;
                }
                covered += nxt - f;
                take.push_back(sorted[which]);
                f = nxt;
            }
            if (!good) continue;
            if (covered < n) {
                puts("-1");
                goto asd;
            }
            if (res < ans) {
                ans = res;
                fin = take;
            }
        }
        if (ans == INT_MAX) {
            puts("-1");
            continue;
        }
        printf("%d\n", ans);
        assert((int)fin.size() == ans);
        for (int i = 0; i < ans; ++i) printf("%d%c", fin[i] + 1, " \n"[i + 1 == ans]);
asd:;
    }
}
