#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000;
int x[maxn], y[maxn];

int cross(int x, int y, int a, int b) {
    return x * b - y * a;
}

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
    line(point pa, point pb): a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), ang(atan2(-a, b)), pa(pa), pb(pb) {}
};

bool eq(double a, double b) {
    return fabs(a - b) < 1e-9;
}

point intersect(line la, line lb) {
    if (eq(la.a * lb.b, la.b * lb.a)) throw;
    double bot = -la.a * lb.b + la.b * lb.a;
    return point(-la.b * lb.c + la.c * lb.b, la.a * lb.c - la.c * lb.a) / bot;
}

bool check(line l1, line l2, line l3) {
    point p = intersect(l2, l3);
    return ((l1.pb - l1.pa) ^ (p - l1.pa)) < -1e-9;
}
vector<point> hpi(vector<line> ls) {
    // for (int i = 0; i < (int)ls.size(); ++i)
    //    printf("(%.3lf, %.3lf) -> (%.3lf, %.3lf)\n", ls[i].pa.x, ls[i].pa.y, ls[i].pb.x, ls[i].pb.y);
    sort(ls.begin(), ls.end(), [&](line a, line b) {
        if (eq(a.ang, b.ang)) return ((b.pb - b.pa) ^ (a.pb - b.pa)) > 1e-9;
        return a.ang < b.ang;
    });
    vector<line> pl(1, ls[0]);
    for (int i = 0; i < (int)ls.size(); ++i) if (!eq(ls[i].ang, pl.back().ang)) pl.push_back(ls[i]);
    deque<int> dq;
    dq.push_back(0);
    dq.push_back(1);
    for (int i = 2; i < (int)pl.size(); ++i) {
        while ((int)dq.size() > 1 && check(pl[i], pl[dq.back()], pl[dq[dq.size() - 2]])) dq.pop_back();
        while ((int)dq.size() > 1 && check(pl[i], pl[dq[0]], pl[dq[1]])) dq.pop_front();
        dq.push_back(i);
    }
    while ((int)dq.size() > 1 && check(pl[dq[0]], pl[dq.back()], pl[dq[dq.size() - 2]])) dq.pop_back();
    while ((int)dq.size() > 1 && check(pl[dq.back()], pl[dq[0]], pl[dq[1]])) dq.pop_front();
    vector<point> res;
    for (int i = 0; i < (int)dq.size(); ++i) res.emplace_back(intersect(pl[dq[i]], pl[dq[(i + 1) % dq.size()]]));
    return res;
}


int main() {
    int n, r; scanf("%d%d", &n, &r);
    for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);
    vector<line> seg;
    for (int i = 0; i < n; ++i) {
        int dx = x[(i + 1) % n] - x[i];
        int dy = y[(i + 1) % n] - y[i];
        int ex = -dy, ey = dx;
        if (cross(dx, dy, ex, ey) > 0) ex = -ex, ey = -ey; 
        // printf("dx = %d dy = %d ex = %d ey = %d\n", dx, dy, ex, ey);
        double length = hypot(ex, ey);
        double cx = ex / length, cy = ey / length;
        // printf("cx = %.3lf cy = %.3lf\n", cx, cy);
        seg.emplace_back(point(x[(i + 1) % n] + cx * (r - 1e-9), y[(i + 1) % n] + cy * (r - 1e-9)), point(x[i] + cx * (r - 1e-9), y[i] + cy * (r - 1e-9)));
        // seg.emplace_back(make_pair(x[i] + cx * r, y[i] + cy * r), make_pair(x[(i + 1) % n] + cx * r, y[(i + 1) % n] + cy * r));
    }
    vector<point> poly = hpi(seg);
    double dist = 0.0;
    int mi = -1, mj = -1;
    for (int i = 0; i < (int)poly.size(); ++i) {
        for (int j = 0; j < (int)poly.size(); ++j) {
            double dx = poly[i].x - poly[j].x;
            double dy = poly[i].y - poly[j].y;
            double d = hypot(dx, dy);
            if (d > dist) {
                dist = d;
                mi = i;
                mj = j;
            }
        }
    }
    printf("%.4lf %.4lf %.4lf %.4lf\n", poly[mi].x, poly[mi].y, poly[mj].x, poly[mj].y);
}
