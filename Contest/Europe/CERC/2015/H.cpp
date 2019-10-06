#include <bits/stdc++.h>
using namespace std;

double x[4], y[4];

struct point {
    double x, y;
    point(double x = 0, double y = 0): x(x), y(y) {}
    point operator+(const point &p) const { return point(x + p.x, y + p.y); }
    point operator-(const point &p) const { return point(x - p.x, y - p.y); }
    point operator/(const double d) const { return point(x / d, y / d); }
    double operator*(const point &p) const { return x * p.x + y * p.y; }
    double operator^(const point &p) const { return x * p.y - y * p.x; }
};

struct line {
    double a, b, c, ang;
    point pa, pb;
    line(): a(0), b(0), c(0), ang(0), pa(), pb() {}
    line(point pa, point pb):
        a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), ang(atan2(-a, b)), pa(pa), pb(pb) {}
};

bool eq(double a, double b) {
    return fabs(a - b) < 1e-9;
}

point intersect(line la, line lb) {
    double bot = -la.a * lb.b + la.b * lb.a;
    return point(-la.b * lb.c + la.c * lb.b, la.a * lb.c - la.c * lb.a) / bot;
}

bool check(line l1, line l2, line l3) {
    point p = intersect(l2, l3);
    return ((l1.pb - l1.pa) ^ (p - l1.pa)) < 1e-9;
}

vector<point> hpi(vector<line> ls) {
    sort(ls.begin(), ls.end(), [&](line l1, line l2) {
        if (eq(l1.ang, l2.ang)) return ((l2.pb - l2.pa) ^ (l1.pb - l2.pa)) > 1e-9;
        return l1.ang < l2.ang;
    });
    vector<line> pl(1, ls[0]);
    for (int i = 1; i < (int)ls.size(); ++i) if (!eq(ls[i].ang, pl.back().ang)) pl.push_back(ls[i]);
    deque<int> dq = { 0, 1 };
    for (int i = 2; i < (int)pl.size(); ++i) {
        while (dq.size() > 1 && check(pl[i], pl[dq.back()], pl[dq[dq.size() - 2]]))
            dq.pop_back();
        while (dq.size() > 1 && check(pl[i], pl[dq[0]], pl[dq[1]])) 
            dq.pop_front();
        dq.push_back(i);
    }
    while (dq.size() > 1 && check(pl[0], pl[dq.back()], pl[dq[dq.size() - 2]]))
        dq.pop_back();
    while (dq.size() > 1 && check(pl[dq.back()], pl[dq[0]], pl[dq[1]])) 
        dq.pop_front();
    vector<point> res;
    for (int i = 0; i < (int)dq.size(); ++i)
        res.push_back(intersect(pl[dq[i]], pl[dq[(i + 1) % dq.size()]]));
    return res;
}

double area(vector<point> poly) {
    double s = 0;
    for (int i = 0; i < (int)poly.size(); ++i) {
        s += (poly[i] ^ poly[(i + 1) % poly.size()]);
    }
    return fabs(s) * 0.5;
}

int main() {
    for (int i = 0; i < 4; ++i) cin >> x[i] >> y[i];
    long double ans = 5 * 4 * 5 * 5;
    vector<line> ls;
    for (int i = 0; i < 4; ++i) ls.emplace_back(point(x[i], y[i]), point(x[(i + 1) % 4], y[(i + 1) % 4]));
    ls.emplace_back(point(0.5, 1), point(0.5, -1));
    double a = area(hpi(ls));
    ls.pop_back();
    ls.emplace_back(point(-1, 0.5), point(1, 0.5));
    double b = area(hpi(ls));
    ls.pop_back();
    ls.emplace_back(point(-0.5, -1), point(-0.5, 1));
    double c = area(hpi(ls));
    ls.pop_back();
    ls.emplace_back(point(1, -0.5), point(-1, -0.5));
    double d = area(hpi(ls));
    ans += 3 * a * 5;
    ans += 6 * b * 5;
    ans += 4 * c * 5;
    ans += 1 * d * 5;
    ans /= 124;
    cout << fixed << setprecision(20) << ans << endl;
}
