#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
const double pi = acos(-1);

bool same(double x, double y) { return abs(x - y) < eps; }

struct P {
    double x, y; 
    P() = default;
    P(double x, double y) : x(x), y(y) {}
    P operator + (const P b) const { return P(x + b.x, y + b.y); }
    P operator - (const P b) const { return P(x - b.x, y - b.y); }
    P operator * (const double b) const { return P(x * b, y * b); }
    P operator / (const double b) const { return P(x / b, y / b); }
    double operator * (const P b) const { return x * b.x + y * b.y; }
    double operator ^ (const P b) const { return x * b.y - y * b.x; }
    double abs() { return hypot(x, y); }
    P unit() { return P(x / abs(), y / abs()); }
};

struct L {
    double a, b, c, o;
    P pa, pb;
    L() = default;
    L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), o(atan2(-a, b)), pa(pa), pb(pb) {}
    P project(P p) { return pa + (pb - pa).unit() * ((pb - pa) * (p - pa) / (pb - pa).abs()); }
};


bool parallel(L x, L y) {
    return same(x.a * y.b, x.b * y.a);
}


P intersect(L x, L y) { return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a); }

struct C {
    P c; double r;
    C(P c, double r) : c(c), r(r) {}
};


L l[105];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        P a, b;
        cin >> a.x >> a.y >> b.x >> b.y;
        l[i] = L(a, b);
    }
    if (n <= 2) {
        cout << "Many" << endl;
        exit(0);
    }
    vector<P> aps;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (parallel(l[i], l[j]) && parallel(l[i], l[k])) {
                    cout << "None" << endl;
                    exit(0);
                }
                if (aps.size()) continue;

                int x = i, y = j, z = k;
                if (parallel(l[y], l[z])) swap(x, z);
                if (parallel(l[x], l[z])) swap(y, z);
                vector<P> ps;
                if (parallel(l[x], l[y])) {
                    P a = intersect(l[x], l[z]);
                    P b = intersect(l[y], l[z]);
                    P c = P((a.x + b.x) / 2, (a.y + b.y) / 2);
                    double d = (a - c).abs();
                    P dir = (l[y].pb - l[y].pa).unit() * d;
                    ps.push_back(c + dir);
                    ps.push_back(c - dir);
                } else {
                    P A = intersect(l[x], l[y]);
                    P B = intersect(l[x], l[z]);
                    P C = intersect(l[y], l[z]);
                    if ((A - B).abs() < eps && (B - C).abs() < eps) {
                        ps.push_back(A);
                    } else {
                        double a = (B - C).abs();
                        double b = (A - C).abs();
                        double c = (A - B).abs();
                        ps.push_back((A * a + B * b + C * c) / (a + b + c));
                        ps.push_back((A * (-a) + B * b + C * c) / (-a + b + c));
                        ps.push_back((A * a - B * b + C * c) / (a - b + c));
                        ps.push_back((A * a + B * b - C * c) / (a + b - c));
                    }
                }
                aps = ps;
            }
        }
    }

    vector<P> ans;

    for (auto p : aps) {
        // cerr << "check p = " << p.x << " " << p.y << endl;
        double dis = (p - l[0].project(p)).abs();
        bool ok = true;
        for (int i = 1; i < n; ++i) {
            if (!same(dis, (p - l[i].project(p)).abs())) ok = false;
        }
        if (ok )ans.push_back(p);
    }

    if (ans.empty()) cout << "None" << endl;
    else if (ans.size() > 1u) cout << "Many" << endl;
    else cout << fixed << setprecision(10) << ans[0].x << " " << ans[0].y << endl;
}
