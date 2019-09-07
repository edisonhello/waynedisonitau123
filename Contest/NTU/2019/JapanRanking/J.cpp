#pragma GCC optimize("Ofast")
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
    double angle() { return atan2(y, x); }
};

struct L {
    double a, b, c, o;
    P pa, pb;
    L() = default;
    L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), o(atan2(-a, b)), pa(pa), pb(pb) {}
    P project(P p) { return pa + (pb - pa).unit() * ((pb - pa) * (p - pa) / (pb - pa).abs()); }
    double get_ratio(P p) { return (p - pa) * (pb - pa) / ((pb - pa).abs() * (pb - pa).abs()); }
    bool inside(P p) {
        double x = get_ratio(p);
        return x >= 0 && x <= 1;
    }
};


bool parallel(L x, L y) {
    return same(x.a * y.b, x.b * y.a);
}


P intersect(L x, L y) { return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a); }

struct C {
    P c; double r;
    C(P c, double r) : c(c), r(r) {}
};

struct Block {
    P a, b;
    vector<pair<P, P>> segs;
    void build() {
        segs.emplace_back(P(a.x, a.y), P(a.x, b.y));
        segs.emplace_back(P(a.x, b.y), P(b.x, b.y));
        segs.emplace_back(P(b.x, b.y), P(b.x, a.y));
        segs.emplace_back(P(b.x, a.y), P(a.x, a.y));
        // segs.emplace_back(P((a.x + b.x) / 2, a.y), P((a.x + b.y) / 2, b.y));
        // segs.emplace_back(P(a.x, (a.y + b.y) / 2), P(b.x, (a.y + b.y) / 2));
    }
};

int sign(double x) {
    if (abs(x) < eps) return 0;
    if (x < 0) return -1;
    return 1;
}
bool SegIntersect(P p1, P p2, P p3, P p4) {
    if (max(p1.x, p2.x) < min(p3.x, p4.x) || max(p3.x, p4.x) < min(p1.x, p2.x)) return false;
    if (max(p1.x, p2.x) < min(p3.x, p4.x) || max(p3.x, p4.x) < min(p1.x, p2.x)) return false;
    return sign((p3 - p1) ^ (p4 - p1)) * sign((p3 - p2) ^ (p4 - p2)) <= 0 && sign((p1 - p3) ^ (p2 - p3)) * sign((p1 - p4) ^ (p2 - p4)) <= 0;
}

const int TX = 50000;

P apos[104 * TX], bpos[104 * TX], adir[104 * TX], bdir[104 * TX];
double bdirang[104 * TX];
Block blk[25];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T, R; cin >> T >> R;
    T *= TX;
    vector<tuple<int, int, int>> atr, btr;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y, t; cin >> x >> y >> t;
        t *= TX;
        atr.emplace_back(x, y, t);
    }
    int m; cin >> m; 
    for (int i = 0; i < m; ++i) {
        int x, y, t; cin >> x >> y >> t;
        t *= TX;
        btr.emplace_back(x, y, t);
    }
    int b; cin >> b;
    for (int i = 0; i < b; ++i) {
        cin >> blk[i].a.x >> blk[i].a.y >> blk[i].b.x >> blk[i].b.y;
        blk[i].build();
    }

    for (int i = 1; i < n; ++i) {
        double dx = get<0>(atr[i]) - get<0>(atr[i - 1]);
        double dy = get<1>(atr[i]) - get<1>(atr[i - 1]);
        int ST = get<2>(atr[i - 1]), ED = get<2>(atr[i]);
        int tt = ED - ST;
        double udx = dx / tt, udy = dy / tt;
        for (int t = ST; t <= ED; ++t) {
            apos[t] = P(get<0>(atr[i - 1]) + udx * (t - ST), get<1>(atr[i - 1]) + udy * (t - ST));
            adir[t] = P(dx, dy);
        }
    }
    for (int i = 1; i < m; ++i) {
        double dx = get<0>(btr[i]) - get<0>(btr[i - 1]);
        double dy = get<1>(btr[i]) - get<1>(btr[i - 1]);
        int ST = get<2>(btr[i - 1]), ED = get<2>(btr[i]);
        int tt = ED - ST;
        double udx = dx / tt, udy = dy / tt;
        double ang = atan2(dy, dx);
        // cerr << "udx = " << udx << ", udy = " << udy << endl;
        // cerr << "ST = " << ST << ", ED = " << ED << endl;
        for (int t = ST; t <= ED; ++t) {
            bpos[t] = P(get<0>(btr[i - 1]) + udx * (t - ST), get<1>(btr[i - 1]) + udy * (t - ST));
            bdir[t] = P(dx, dy);
            bdirang[t] = ang;
            // cerr << "bpos[" << t << "] = " << bpos[t].x << " " << bpos[t].y << endl;
        }
    }

    int see = 0;
    // cerr << "T = " << T << endl;
    for (int i = 0; i < T; ++i) {
        P pdir = apos[i] - bpos[i];
        double dot = pdir * bdir[i];
        double ang = acos(dot / (pdir.abs() * bdir[i].abs()));
        if (ang <= pi / 4 + eps) {
            // in right direction
            double d = (apos[i] - bpos[i]).abs();
            if (d <= R) {
                // can see
                bool block = false;
                for (int j = 0; j < b && !block; ++j) {
                    for (auto &p : blk[j].segs) {
                        if (SegIntersect(apos[i], bpos[i], p.first, p.second)) {
                            // cerr << fixed << setprecision(10);
                            // cerr << "(" << apos[i].x << "," << apos[i].y << ")";
                            // cerr << "(" << bpos[i].x << "," << bpos[i].y << ")";
                            // cerr << "(" << p.first.x << "," << p.first.y << ")";
                            // cerr << "(" << p.second.x << "," << p.second.y << ")";
                            // cerr << "block" << endl;
                            block = true;
                            break;
                        }
                    }
                }
                if (!block) see++;
            }
            // else cerr << "too far" << endl;
        }
        // else cerr << "wrong direction" << endl;
    }

    cout << fixed << setprecision(10) << (double)see / TX << endl;
}
