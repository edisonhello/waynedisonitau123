#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-10;

bool same(double a, double b) {
    return abs(a - b) < eps;
}

struct P {
    double x, y;
    P operator+ (P b) { return P{x + b.x, y + b.y}; }
    P operator- (P b) { return P{x - b.x, y - b.y}; }
    P operator* (double b) { return P{x * b, y * b}; }
    P operator/ (double b) { return P{x / b, y / b}; }
    double operator* (P b) { return x * b.x + y * b.y; }
    double operator^ (P b) { return x * b.y - y * b.x; }
    double abs() { return hypot(x, y); }
    double angle() { return atan2(y, x); }
    P unit() { return *this / abs(); }
};

struct L {
    double a, b, c;
    P pa, pb;
    L() = default;
    L(P &pa, P &pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
    P project(P p) { return pa + (pb - pa).unit() * ((pb - pa) * (p - pa) / (pb - pa).abs()); }
    double get_ratio(P p) { return (p - pa) * (pb - pa) / ((pb - pa).abs() * (pb - pa).abs()); }
    bool inside(P p) { double z = get_ratio(p); return 0 <= z && z <= 1; }
};

const double pi = acos(-1);

vector<pair<double, double>> Cover(P p, L l) {
    P prop = l.project(p);
    if ((p - prop).abs() < eps && l.inside(prop)) {
        return vector<pair<double, double>>{{-1e18, 1e18}};
    }
    vector<double> o{(l.pa - p).angle(), (l.pb - p).angle()};
    // cerr <<" lb = " << (l.pb - p).x << ' ' << (l.pb - p).y << endl;
    // cerr << "o = " << o[0] << ' ' << o[1] << endl;
    sort(o.begin(), o.end());
    // o[0] = max(o[0], -pi + eps);
    // o[1] = min(o[1], (double)0 - eps);
    // if (o[0] >= o[1]) return vector<pair<double, double>>();
    if (o[0] >= 0) return vector<pair<double, double>>();
    if (o[1] >= 0) {
        if (prop.x > p.x) {
            o[1] = -eps;
        } else {
            o[1] = o[0];
            o[0] = -pi + eps;
        }
    }
    // cerr << "o = " << o[0] << ' ' << o[1] << endl;
    for (auto &z : o) {
        if (same(z, -pi / 2)) z = p.x;
        else z = p.x - p.y / tan(z);
    }
    return vector<pair<double, double>>{{o[0], o[1]}};
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        vector<P> ps(n);
        for (int i = 0; i < n; ++i) {
            cin >> ps[i].x >> ps[i].y;
        }

        vector<L> ls;
        while (m--) {
            P pa, pb;
            cin >> pa.x >> pa.y >> pb.x >> pb.y;
            ls.emplace_back(pa, pb);
        }

        vector<pair<double, int>> evs;
        for (auto &p : ps) {
            // cerr << "for p " << p.x << ' ' << p.y << endl;
            vector<pair<double, double>> st, nst;
            for (auto &l : ls) {
                auto rt = Cover(p, l);
                for (auto i : rt) st.push_back(i);
            }
            sort(st.begin(), st.end());

            if (st.size()) {
                double l = st[0].first, r = st[0].second;
                for (auto &p : st) {
                    if (p.first <= r + eps) {
                        r = max(r, p.second);
                    } else {
                        nst.emplace_back(l, r);
                        tie(l, r) = p;
                    }
                }
                nst.emplace_back(l, r);

                for (auto &p : nst) {
                    evs.emplace_back(p.first, 1);
                    evs.emplace_back(p.second, -1);
                    // cerr << "nst : [" << p.first << ", " << p.second << endl;
                }
            }
        }

        sort(evs.begin(), evs.end());
        double cur = -1e19;
        int cnt = 0;
        double ans = 0;
        for (auto &p : evs) {
            if (cnt == n) {
                ans += p.first - cur;
            }
            cnt += p.second;
            cur = p.first;

        }
        if (ans < 0) {
            cout << "0" << '\n';
        } else if (ans > 1e9) {
            cout << -1 << '\n';
        } else {
            cout << fixed << setprecision(12) << ans << '\n';
        }
    }
}

