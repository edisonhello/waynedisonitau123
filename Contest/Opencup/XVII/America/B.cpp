#include <bits/stdc++.h>
using namespace std;

double pi = acos(-1);
double eps = 1e-9;
bool same(double x, double y) {
    return abs(x - y) < eps;
}

struct P {
    double x, y, z;
    P() : x(0), y(0), z(0) {}
    P(double x, double y, double z) : x(x), y(y), z(z) {}
    double abs() {
        return sqrt(x * x + y * y + z * z);
    }
    double abs2() {
        return x * x + y * y + z * z;
    }
    P unit() {
        double u = abs();
        return P(x / u, y / u, z / u);
    }
};

P operator+ (const P &a, const P &b) { return P(a.x + b.x, a.y + b.y, a.z + b.z); }
P operator- (const P &a, const P &b) { return P(a.x - b.x, a.y - b.y, a.z - b.z); }
P operator* (const P &a, const double b) { return P(a.x * b, a.y * b, a.z * b); }
P operator/ (const P &a, const double b) { return P(a.x / b, a.y / b, a.z / b); }
double operator* (const P &a, const P &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
P operator^ (const P &a, const P &b) { return P(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

double absvol(const P a, const P b, const P c, const P d) {
    return abs(((b - a) ^ (c - a)) * (d - a)) / 6;
}

struct convex3D {
    static const int maxn = 1010;
    struct T {
        int a, b, c;
        bool res;
        T() {}
        T(int a, int b, int c, bool res = 1) : a(a), b(b), c(c), res(res) {}
    };

    int n, m;
    P p[maxn];
    T f[maxn * 8];
    int id[maxn][maxn];
    bool on(T &t, P &q) {
        return ((p[t.c] - p[t.b]) ^ (p[t.a] - p[t.b])) * (q - p[t.a]) > eps;
    }
    void meow(int q, int a, int b) {
        int f2 = id[a][b];
        if (f[f2].res) {
            if (on(f[f2], p[q])) dfs(q, f2);
            else {
                id[q][b] = id[a][q] = id[b][a] = m;
                f[m++] = T(b, a, q, 1);
            }
        }
    }
    void dfs(int p, int i) {
        f[i].res = 0;
        meow(p, f[i].b, f[i].a);
        meow(p, f[i].c, f[i].b);
        meow(p, f[i].a, f[i].c); // bruh
    }
    void operator()() {
        for (int i = 0; i < 4; ++i) {
            T t((i + 1) % 4, (i + 2) % 4, (i + 3) % 4, 1);
            if (on(t, p[i])) swap(t.b, t.c);
            id[t.a][t.b] = id[t.b][t.c] = id[t.c][t.a] = m;
            f[m++] = t;
        }
        for (int i = 4; i < n; ++i) for (int j = 0; j < m; ++j) if (f[j].res && on(f[j], p[i])) {
            dfs(i, j);
            break;
        }
        int mm = m; m = 0;
        for (int i = 0; i < mm; ++i) if (f[i].res) f[m++] = f[i];
    }
    bool same(int i, int j) {
        return !(absvol(p[f[i].a], p[f[i].b], p[f[i].c], p[f[j].a]) > eps || absvol(p[f[i].a], p[f[i].b], p[f[i].c], p[f[j].b]) > eps || absvol(p[f[i].a], p[f[i].b], p[f[i].c], p[f[j].c]) > eps);
    }
    int faces() {
        int r = 0;
        for (int i = 0; i < m; ++i) {
            int iden = 1;
            for (int j = 0; j < i; ++j) if (same(i, j)) iden = 0;
            r += iden;
        }
        return r;
    }
} tb;


int main() {
    int n; cin >> n;
    vector<P> ps(n);
    for (int i = 0; i < n; ++i) cin >> ps[i].x >> ps[i].y >> ps[i].z;

    tb.n = n;
    for (int i = 0; i < n; ++i) tb.p[i] = ps[i];
    tb();

    double mx = 1e20;
    for (int i = 0; i < tb.m; ++i) {
        auto CalcVol = [&] (P &a, P &b, P &c) -> double {
            P dir = ((b - a) ^ (c - a)).unit();
            P x = (b - a).unit();
            P y = dir ^ x;
            assert(same(1, y.abs()));

            vector<P> pss;
            double mn = 1e20;
            double mx = -1e20;
            for (auto &p : ps) {
                double xo = (p - a) * x;
                double yo = (p - a) * y;
                double zo = (p - a) * dir;
                pss.emplace_back(xo, yo, 0);
                mn = min(mn, zo);
                mx = max(mx, zo);
            }

            // cerr << "mn mx " << mn << ' ' << mx << endl;

            auto Center3 = [&] (P &a, P &b, P &c) {
                P p0 = b - a, p1 = c - a;
                double c1 = p0.abs2() * 0.5, c2 = p1.abs2() * 0.5;
                double d = (p0 ^ p1).z;
                double x = a.x + (c1 * p1.y - c2 * p0.y) / d;
                double y = a.y + (c2 * p0.x - c1 * p1.x) / d;
                return P(x, y, 0);
            };

            random_shuffle(pss.begin(), pss.end());
            double r = 0;
            P cen;
            for (int i = 0; i < (int)pss.size(); ++i) {
                if ((cen - pss[i]).abs2() <= r) continue;
                cen = pss[i]; r = 0;
                for (int j = 0; j < i; ++j) {
                    if ((cen - pss[j]).abs2() <= r) continue;
                    cen = (pss[i] + pss[j]) / 2;
                    r = (pss[j] - cen).abs2();
                    for (int k = 0; k < j; ++k) {
                        if ((cen - pss[k]).abs2() <= r) continue;
                        cen = Center3(pss[i], pss[j], pss[k]);
                        r = (pss[k] - cen).abs2();
                    }
                }
            }

            return (mx - mn) * pi * r;
        };
        auto t = tb.f[i];
        mx = min(mx, CalcVol(tb.p[t.a], tb.p[t.b], tb.p[t.c]));
    }

    cout << fixed << setprecision(12) << mx << endl;
}

