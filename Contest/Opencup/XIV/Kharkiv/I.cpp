#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;
bool same(const double a, const double b) { return abs(a - b) < eps; }

struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
};
Point operator + (const Point a, const Point b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point a, const Point b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point a, const double b) { return Point(a.x * b, a.y * b); }
Point operator / (const Point a, const double b) { return Point(a.x / b, a.y / b); }
double operator ^ (const Point a, const Point b) { return a.x * b.y - a.y * b.x; }
double abs(const Point a) { return hypot(a.x, a.y); }

struct Line {
    double a, b, c;
    double angle;
    Point pa, pb;
    Line() : a(0), b(0), c(0), angle(0), pa(), pb() {}
    Line(Point pa, Point pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), angle(atan2(-a, b)), pa(pa), pb(pb) {}
};

bool tag;
Point intersect(Line &la, Line &lb) {
    if (same(la.a * lb.b, la.b * lb.a)) return tag = true, Point(0, 0);
    double bot = -la.a * lb.b + la.b * lb.a;
    return Point(-la.b * lb.c + la.c * lb.b, la.a * lb.c - la.c * lb.a) / bot;
}

bool jizz(Line &l1, Line &l2, Line &l3) {
    Point p = intersect(l2, l3);
    return ((l1.pb - l1.pa) ^ (p - l1.pa)) < -eps;
}
bool cmp(const Line &a, const Line &b) {
    return same(a.angle, b.angle) ? (((b.pb - b.pa) ^ (a.pb - b.pa)) > eps) : a.angle < b.angle;
}

vector<Point> HPI(vector<Line> &ls) {
    tag = false;
    // sort(ls.begin(), ls.end(), cmp);
    vector<Line> pls(1, ls[0]);
    for (size_t i = 0; i < ls.size(); ++i) if (!same(ls[i].angle, pls.back().angle)) pls.push_back(ls[i]);
    deque<int> dq; dq.push_back(0); dq.push_back(1);
    for (size_t i = 2; i < pls.size(); ++i) {
        while (dq.size() > 1u && jizz(pls[i], pls[dq.back()], pls[dq[dq.size() - 2]])) dq.pop_back();
        while (dq.size() > 1u && jizz(pls[i], pls[dq[0]], pls[dq[1]])) dq.pop_front();
        dq.push_back(i);
    }
    while (dq.size() > 1u && jizz(pls[dq.front()], pls[dq.back()], pls[dq[dq.size() - 2]])) dq.pop_back();
    while (dq.size() > 1u && jizz(pls[dq.back()], pls[dq[0]], pls[dq[1]])) dq.pop_front();
    if (dq.size() < 3u || tag) return vector<Point>();
    vector<Point> rt;
    for (size_t i = 0; i < dq.size(); ++i) rt.push_back(intersect(pls[dq[i]], pls[dq[(i + 1) % dq.size()]]));
    return rt;
}

Point p[50005], nm[50005];
Line ol[50005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> p[i].x >> p[i].y;
    double ara = 0;
    for (int i = 0; i < n; ++i) ara += (p[i] ^ p[(i + 1) % n]);
    if (ara < 0) reverse(p, p + n);

    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        ol[i] = Line(p[i], p[j]);
        nm[i] = Point(ol[i].a, ol[i].b) / hypot(ol[i].a, ol[i].b);
    }

    double xmx = -1e7, xmn = 1e7, ymx = -1e7, ymn = 1e7;
    for (int i = 0; i < n; ++i) xmx = max(xmx, p[i].x), xmn = min(xmn, p[i].x), ymx = max(ymx, p[i].y), ymn = min(ymn, p[i].y);
    double L = 0, R = min(xmx - xmn, ymx - ymn);
    int cnt = 40;
    while (cnt--) {
        double go = (L + R) / 2;
        vector<Line> ls(n);
        for (int i = 0; i < n; ++i) {
            int j = (i + 1) % n;
            ls[i] = Line(p[i] + nm[i] * go, p[j] + nm[i] * go);
        }
        if (HPI(ls).size()) L = go;
        else R = go;
    }
    cout << fixed << setprecision(10) << L << endl;
}
