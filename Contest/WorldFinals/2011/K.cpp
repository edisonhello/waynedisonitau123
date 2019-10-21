#include <bits/stdc++.h>
using namespace std;
 
const double eps = 1e-9;
bool same(double x, double y) { return abs(x - y) < eps; }
 
struct P {
    double x, y;
    P operator + (const P b) const { return {x + b.x, y + b.y}; }
    P operator - (const P b) const { return {x - b.x, y - b.y}; }
    P operator * (const double b) const { return {x * b, y * b}; }
    double operator * (const P b) const { return x * b.x + y * b.y; }
    double operator ^ (const P b) const { return x * b.y - y * b.x; }
    double abs() const { return hypot(x, y); }
    P unit() const { return {x / abs(), y / abs()}; }
};
struct L {
    double a, b, c;
    P pa, pb;
    L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
    P project(P p) { return pa + (pb - pa).unit() * ((pb - pa) * (p - pa) / (pb - pa).abs()); }
};
 
#define crx(a, b, c) ((b - a) ^ (c - a))
 
vector<P> convex(vector<P> ps) {
    vector<P> p;
    sort(ps.begin(), ps.end(), [&] (P a, P b) { return same(a.x, b.x) ? a.y < b.y : a.x < b.x; });
    for (int i = 0; i < (int)ps.size(); ++i) {
        while (p.size() >= 2u && crx(p[p.size() - 2], ps[i], p[p.size() - 1]) >= 0) p.pop_back();
        p.push_back(ps[i]);
    }
    int t = p.size();
    for (int i = (int)ps.size() - 2; i >= 0; --i) {
        while (p.size() > t && crx(p[p.size() - 2], ps[i], p[p.size() - 1]) >= 0) p.pop_back();
        p.push_back(ps[i]);
    }
    p.pop_back();
    return p;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int ks = 0;
    int n; while (cin >> n) {
        if (n == 0) break;
        ++ks;
        vector<P> ps(n);
        for (int i = 0; i < n; ++i) cin >> ps[i].x >> ps[i].y;
        double mn = 1e9;
        ps = convex(ps);
        n = ps.size();
        for (int i = 0; i < n; ++i) /* for (int j = 0; j < n; ++j) if (j != i) */ {
            int j = (i == n - 1 ? 0 : i + 1);
            L l(ps[i], ps[j]);
            double L = 0, R = 0;
            for (int z = 0; z < n; ++z) if (z != i && z != j) {
                P dir = ps[z] - l.project(ps[z]);
                bool neg = false;
                if ((same(dir.x, 0) && dir.y > 0) || (!same(dir.x, 0) && dir.x > 0));
                else neg = true;
                double d = dir.abs() * (neg ? -1 : 1);
                L = min(L, d);
                R = max(R, d);
            }
            // cout << "L = " << L << " R = " << R << endl;
            mn = min(mn, R - L);
        }
 
        cout << "Case " << ks << ": " << fixed << setprecision(2) << ceil(mn * 100) / 100 << '\n';
    }
}
