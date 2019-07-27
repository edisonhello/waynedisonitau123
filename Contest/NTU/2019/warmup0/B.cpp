#include <bits/stdc++.h>
using namespace std;

#define double long double

const double eps = 1e-12;

bool same(const double a, const double b) { return abs(a - b) < eps; }

struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double x, double y): x(x), y(y) {}
};
Point operator + (const Point a, const Point b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (const Point a, const Point b) { return Point(a.x - b.x, a.y - b.y); }
Point operator * (const Point a, const double b) { return Point(a.x * b, a.y * b); }
Point operator / (const Point a, const double b) { return Point(a.x / b, a.y / b); }

double operator ^ (const Point a, const Point b) { return a.x * b.y - a.y * b.x; }

struct Line {
    double a, b, c, angle;
    Point pa, pb;
    Line() : a(0), b(0), c(0), angle(0), pa(), pb() {}
    Line(Point pa, Point pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), angle(atan2(-a, b)), pa(pa), pb(pb) {}
};

bool tag;
Point intersect(Line la, Line lb) {
    if (same(la.a * lb.b, la.b * lb.a)) return tag = true, Point(0, 0);
    else tag = false;
    double bot = -la.a * lb.b + la.b * lb.a;
    return Point(-la.b * lb.c + la.c * lb.b, la.a * lb.c - la.c * lb.a) / bot;
}

vector<Point> convex(vector<Point> p) {
    sort(p.begin(), p.end(), [] (const Point &a, const Point &b) { return a.x == b.x ? a.y < b.y : a.x < b.x; });
    vector<Point> ch;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        while (ch.size() >= 2 && ((p[i] - ch[ch.size() - 2]) ^ (ch[ch.size() - 1] - ch[ch.size() - 2])) >= 0) ch.pop_back();
        ch.push_back(p[i]);
    }
    int t = ch.size();
    for (int i = n - 2; i >= 0; --i) {
        while ((int)ch.size() > t && ((p[i] - ch[ch.size() - 2]) ^ (ch[ch.size() - 1] - ch[ch.size() - 2])) >= 0) ch.pop_back();
        ch.push_back(p[i]);
    }
    ch.pop_back();
    // reverse(ch.begin(), ch.end());
    return ch;
}

bool jizz(Line l1, Line l2, Line l3) {
    Point p = intersect(l2, l3);
    if (tag) return true;
    return ((l1.pb - l1.pa) ^ (p - l1.pa)) < -eps;
}

bool cmp(const Line &a, const Line &b) {
    return same(a.angle, b.angle) ? (((b.pb - b.pa) ^ (a.pb - b.pa)) > eps) : a.angle < b.angle;
}

vector<Point> hpi(vector<Line> &ls) {
    // cerr << "here" << endl;
    sort(ls.begin(), ls.end(), cmp);
    vector<Line> pls(1, ls[0]);
    for (int i = 0; i < (int)ls.size(); ++i) if (!same(ls[i].angle, pls.back().angle)) pls.push_back(ls[i]);
    deque<int> dq; dq.push_back(0); dq.push_back(1);
    // cerr << "pls.size() = " << pls.size() << endl;
    for (int i = 2; i < (int)pls.size(); ++i) {
        // cerr << "i = " << i << endl;
        while (dq.size() > 1u && jizz(pls[i], pls[dq.back()], pls[dq[dq.size() - 2]])) dq.pop_back();
        while (dq.size() > 1u && jizz(pls[i], pls[dq[0]], pls[dq[1]])) dq.pop_front();
        dq.push_back(i);
    }
    while (dq.size() > 1u && jizz(pls[dq.front()], pls[dq.back()], pls[dq[dq.size() - 2]])) dq.pop_back();
    while (dq.size() > 1u && jizz(pls[dq.back()], pls[dq[0]], pls[dq[1]])) dq.pop_front();
    // cerr << "dq.size() = " << dq.size() << endl;
    if (dq.size() < 3u) return vector<Point>();
    vector<Point> rt;
    for (int i = 0; i < (int)dq.size(); ++i) rt.push_back(intersect(pls[dq[i]],pls[dq[(i + 1) % dq.size()]]));
    return rt;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        vector<Point> a(n), b(m);
        for (Point &p : a) cin >> p.x >> p.y;
        for (Point &p : b) cin >> p.x >> p.y;
        a = convex(a), b = convex(b);
        // cout << "A = "; for (Point &p : a) cout << "(" << p.x << ", " << p.y << ") "; cout << endl;
        // cout << "B = "; for (Point &p : b) cout << "(" << p.x << ", " << p.y << ") "; cout << endl;
        vector<Line> aa;
        for (int i = 0; i < (int)a.size(); ++i) aa.emplace_back(a[i], a[(i + 1) % a.size()]);
        for (int i = 0; i < (int)b.size(); ++i) aa.emplace_back(b[i], b[(i + 1) % b.size()]);
        vector<Point> c = hpi(aa);
        double ara = 0;
        for (int i = 0; i < (int)c.size(); ++i) {
            int j = (i + 1) % c.size();
            ara += c[i] ^ c[j];
        }
        ara = abs(ara) / 2;
        cout << fixed << setprecision(14) << ara << '\n';
    }
}
