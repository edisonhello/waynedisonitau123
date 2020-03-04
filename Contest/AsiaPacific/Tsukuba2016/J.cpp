#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1);
const double eps = 1e-9;

struct P {
    double x, y;
    P() : x(0), y(0) {}
    P(double x, double y) : x(x), y(y) {}
    P operator+(const P &p) const { return P(x + p.x, y + p.y); }
    P operator-(const P &p) const { return P(x - p.x, y - p.y); }

    P operator*(double d) const { return P(x * d, y * d); }
    P operator/(double d) const { return P(x / d, y / d); }

    double operator*(const P &p) const { return x * p.x + y * p.y; }
    double operator^(const P &p) const { return x * p.y - y * p.x; }

    double abs() const { return sqrt(*this * *this); }
};

struct L {
    double a, b, c;
    P pa, pb;
    L() : a(0), b(0), c(0), pa(), pb() {}
    L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
};

int sign(double x) {
    if (fabs(x) < eps) return 0;
    return x > 0 ? 1 : -1;
}

bool SegmentIntersect(P p1, P p2, P p3, P p4) {
    if (max(p1.x, p2.x) < min(p3.x, p4.x) || max(p3.x, p4.x) < min(p1.x, p2.x)) return false;
    if (max(p1.y, p2.y) < min(p3.y, p4.y) || max(p3.y, p4.y) < min(p1.y, p2.y)) return false;
    return sign((p3 - p1) ^ (p4 - p1)) * sign((p3 - p2) ^ (p4 - p2)) <= 0 &&
        sign((p1 - p3) ^ (p2 - p3)) * sign((p1 - p4) ^ (p2 - p4)) <= 0;
}

P intersect(L x, L y) {
    return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a);
}

double sq(double x) { return x * x; }

vector<P> CircleCrossLine(P a, P b, P o, double r) {
    double x = b.x - a.x, y = b.y - a.y, A = sq(x) + sq(y), B = 2 * x * (a.x - o.x) + 2 * y * (a.y - o.y), C = sq(a.x - o.x) + sq(a.y - o.y) - sq(r), d = B * B - 4 * A * C;
    vector<P> t;
    if (d >= -eps) {
        double i = (-B - sqrt(max(0., d))) / (2 * A);
        double j = (-B + sqrt(max(0., d))) / (2 * A);
        if (i - 1.0 <= eps && i >= -eps) t.emplace_back(a.x + i * x, a.y + i * y);
        if (j - 1.0 <= eps && j >= -eps) t.emplace_back(a.x + j * x, a.y + j * y);
    }
    return t;
}

double SectorArea(P a, P b, double r) {
    double theta = atan2(a.y, a.x) - atan2(b.y, b.x);
    while (theta <= 0) theta += 2 * pi;
    while (theta >= 2 * pi) theta -= 2 * pi;
    theta = min(theta, 2 * pi - theta);
    return r * r * theta / 2;
}

double AreaOfCircleTriangle(P a, P b, double r) {
    bool ina = a.abs() < r, inb = b.abs() < r;
    if (ina) {
        if (inb) return abs(a ^ b) / 2;
        P p = CircleCrossLine(a, b, P(0, 0), r)[0];
        return SectorArea(b, p, r) + abs(a ^ p) / 2;
    }
    auto p = CircleCrossLine(a, b, P(0, 0), r);
    if (inb) return SectorArea(p[0], a, r) + abs(p[0] ^ b) / 2;
    if (p.size() == 2) return SectorArea(a, p[0], r) + SectorArea(p[1], b, r) + abs(p[0] ^ p[1]) / 2;
    return SectorArea(a, b, r);
}

int main() {
    int n, r; cin >> n >> r;
    vector<P> ps(n);
    for (int i = 0; i < n; ++i) cin >> ps[i].x >> ps[i].y;


    auto calc = [&] (double x, double y) -> double {
        double res = 0;
        for (int i = 0; i < n; ++i) {
            int j = (i == n - 1 ? 0 : i + 1);
            P pi = ps[i] - P(x, y);
            P pj = ps[j] - P(x, y);
            res += AreaOfCircleTriangle(pi, pj, r) * ((pi ^ pj) > 0 ? 1 : -1);
        }
        // cerr << "calc x = " << x << " y = " << y << " res = " << res << endl;
        return res;
    };

    // cout << "Area of circlectriangle " << AreaOfCircleTriangle(P(5, 0), P(0, 5), 3) << endl;
    // cout << calc(3, 3) << endl;

    auto meow = [&] (double x) -> double {
        L l(P(x, -100), P(x, 1000));
        double ymin = 1e9, ymax = -1e9;
        for (int i = 0; i < n; ++i) {
            int j = (i == n - 1 ? 0 : i + 1);
            L ll(ps[i], ps[j]);
            if (SegmentIntersect(l.pa, l.pb, ll.pa, ll.pb)) {
                double yy = intersect(l, ll).y;
                ymin = min(ymin, yy);
                ymax = max(ymax, yy);
            }
        }

        int step = 50;
        while (step--) {
            double yl = (ymin * 2 + ymax) / 3;
            double yr = (ymin + ymax * 2) / 3;
            if (calc(x, yl) > calc(x, yr)) ymax = yr;
            else ymin = yl;
        }

        return calc(x, ymin);
    };

    double xmin = 1e9, xmax = -1e9;
    for (int i = 0; i < n; ++i) xmin = min(xmin, ps[i].x), xmax = max(xmax, ps[i].x);

    int step = 50;
    while (step--) {
        double xl = (xmin * 2 + xmax) / 3;
        double xr = (xmin + xmax * 2) / 3;
        if (meow(xl) > meow(xr)) xmax = xr;
        else xmin = xl;
    }

    cout << fixed << setprecision(10) << meow(xmin) << endl;
}
