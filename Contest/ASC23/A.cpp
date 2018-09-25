#include <bits/stdc++.h>
#define y1 asd
using namespace std;

struct point {
    double x, y;
    point(double x = 0.0, double y = 0.0): x(x), y(y) {}
    point operator+(const point &p) const { return point(x + p.x, y + p.y); }
    point operator-(const point &p) const { return point(x - p.x, y - p.y); }
    point operator*(const double &d) const { return point(x * d, y * d); }
    double operator*(const point &p) const { return x * p.x + y * p.y; }
    double operator^(const point &p) const { return x * p.y - y * p.x; }
};

const double pi = acos(-1);
double ds, rd, x1, y1, x2, y2, u, v; 

void debug(point p) {
    printf("(%.3lf, %.3lf)\n", p.x, p.y);
}

point rotate(point p, double ang) {
    double cs = cos(ang), sn = sin(ang);
    return point(p.x * cs - p.y * sn, p.x * sn + p.y * cs);
}

double len(point p) {
    return sqrt(p * p);
}

double arc(point a, point b, point o) {
    // debug(a), debug(b), debug(o);
    point oa = a - o;
    point ob = b - o;
    double ang = acos(oa * ob / len(oa) / len(ob));
    // printf("ang = %.20lf\n", ang);
    return ang * rd;
}

double dist(point a, point b) {
    return len(a - b);
}

double calc(point a, point b, point c, point d) {
    double ab = dist(a, b);
    double bc = dist(b, c);
    double cd = dist(c, d);
    double aob = arc(a, b, point(0, 0));
    double cod = arc(c, d, point(0, ds));
    // printf("ab = %.5lf bc = %.5lf cd = %.5lf aob = %.5lf cod = %.5lf\n", ab, bc, cd, aob, cod);
    return min(ab / v, aob / u) + bc / v + min(cd / v, cod / u);
}

double ts(double ang) {
    point p = rotate(point(1, 0), ang) * rd;
    int iter = 100;
    double l = 0.0, r = 2 * pi + 1e-9;
    while (iter--) {
        double ml = l + (r - l) / 3;
        double mr = r - (r - l) / 3;
        point ql = point(0, ds) + rotate(point(-1, 0), ml) * rd;
        point qr = point(0, ds) + rotate(point(-1, 0), mr) * rd;
        double dl = calc(point(x1, y1), p, ql, point(x2, y2));
        double dr = calc(point(x1, y1), p, qr, point(x2, y2));
        if (dl < dr) r = mr;
        else l = ml;
    }
    point q = point(0, ds) + rotate(point(-1, 0), l) * rd;
    return calc(point(x1, y1), p, q, point(x2, y2));
}

int main() {
#ifndef LOCAL
    freopen("bike.in", "r", stdin);
    freopen("bike.out", "w", stdout);
#endif
    cin >> ds >> rd >> x1 >> y1 >> x2 >> y2 >> u >> v;
    int iter = 100;
    double l = 0.0, r = 2 * pi + 1e-9;
    while (iter--) {
        double ml = l + (r - l) / 3;
        double mr = r - (r - l) / 3;
        double dl = ts(ml);
        double dr = ts(mr);
        if (dl < dr) r = mr;
        else l = ml;
    }
    cout << fixed << setprecision(20) << ts(l) << endl;
    return 0;
}
