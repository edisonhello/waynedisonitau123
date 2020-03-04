#include <bits/stdc++.h>
using namespace std;


const double eps = 1e-9;
const double pi = acos(-1);

#define sq(x) ((x) * (x))
bool same(double a, double b) { return abs(a - b) < eps; }

struct P {
    double x, y;
    P(double x = 0, double y = 0) : x(x), y(y) {}
    P operator + (P b) { return P(x + b.x, y + b.y); }
    P operator - (P b) { return P(x - b.x, y - b.y); }
    P operator * (double b) { return P(x * b, y * b); }
    P operator / (double b) { return P(x / b, y / b); }
    double operator * (P b) { return x * b.x + y * b.y; }
    double operator ^ (P b) { return x * b.y - y * b.x; }
    double abs() { return hypot(x, y); }
    P unit() { return *this / abs(); }
    P spin(double o) {
        double c = cos(o), s = sin(o);
        return P(c*x-s*y, s*x+c*y);
    }
    double angle() { return atan2(y, x); }
};

ostream& operator << (ostream& o, P p) { o << "(" << p.x << "," << p.y << ")"; return o; }

struct L {
    double a, b, c;
    P pa, pb;
    L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
    P project(P p) { return pa + (pb - pa).unit() * ((pb - pa) * (p - pa) / (pb - pa).abs()); }
};

struct C {
    P c; double r;
    C(P c = P(0, 0), double r = 0) : c(c), r(r) {}
    P get_point_by_angle(double o) {
        return c + P(cos(o), sin(o)) * r;
    }
};

ostream& operator << (ostream& o, C c) { o << "[" << c.c << "," << c.r << "]"; return o; }

vector<pair<double, double>> CoverSegment(C &a, C &b) {
    double d = (a.c - b.c).abs();
    vector<pair<double, double>> res;
    if (same(a.r + b.r, d)) ;
    else if (d <= abs(a.r - b.r) + eps) {
        if (a.r < b.r) res.emplace_back(0, 2 * pi);
    } else if (d < abs(a.r + b.r) - eps) {
        double o = acos((sq(a.r) + sq(d) - sq(b.r)) / (2 * a.r * d)), z = (b.c - a.c).angle();
        if (z < 0) z += 2 * pi;
        double l = z - o, r = z + o;
        if (l < 0) l += 2 * pi;
        if (r > 2 * pi) r -= 2 * pi;
        if (l > r) res.emplace_back(l, 2 * pi), res.emplace_back(0, r);
        else res.emplace_back(l, r);
    }
    return res;
}

bool CircleCrossLine_angle_yn(P a, P b, P o, double r, pair<double, double> &pp) {
    double x = b.x - a.x, y = b.y - a.y, A = sq(x) + sq(y), B = 2 * x * (a.x - o.x) + 2 * y * (a.y - o.y), C = sq(a.x - o.x) + sq(a.y - o.y) - sq(r), d = B * B - 4 * A * C;
    vector<P> t;
    if (d >= -eps) {
        d = max(0., d);
        double i = (-B - sqrt(d)) / (2 * A);
        double j = (-B + sqrt(d)) / (2 * A);
        if (i - 1.0 <= eps && i >= -eps) t.emplace_back(a.x + i * x, a.y + i * y);
        if (j - 1.0 <= eps && j >= -eps) t.emplace_back(a.x + j * x, a.y + j * y);
    }
    for (P p : t) {
        double z = (p - o).angle();
        if (z <= 0) z += 2 * pi;
        if (pp.first <= z && z <= pp.second) return true;
    }
    return false;
}


int main() {
    int n, w; while (cin >> n >> w) {
        if (n == 0 && w == 0) break;
        vector<pair<P, double>> nd(n);
        for (int i = 0; i < n; ++i) cin >> nd[i].first.x >> nd[i].first.y >> nd[i].second;

        auto ok = [&] (const double R) -> bool {
            double cube_in = (R > w ? sqrt(sq(R) - sq(R - w)) : R);
            if (cube_in * 2 > 100) return false;

            // cerr << "Binary search, check R = " << R << endl;
            // cerr << "cube_in = " << cube_in << endl;

            vector<C> cc(n);
            for (int i = 0; i < n; ++i) {
                cc[i].c = nd[i].first;
                cc[i].r = (R > nd[i].second ? sqrt(sq(R) - sq(R - nd[i].second)) : R);
            }

            vector<P> kado = {P(cube_in, cube_in), P(100 - cube_in, cube_in), P(100 - cube_in, 100 - cube_in), P(cube_in, 100 - cube_in)};
            vector<L> ls = {L(kado[0], kado[1]), L(kado[1], kado[2]), L(kado[2], kado[3]), L(kado[3], kado[0])};

            auto inside_square = [&] (P p) {
                return cube_in <= p.x && p.x <= 100 - cube_in &&
                    cube_in <= p.y && p.y <= 100 - cube_in;
            };

            auto intersect_circle_cube = [&] (C &c, pair<double, double> &p) {
                if (CircleCrossLine_angle_yn(ls[0].pa, ls[0].pb, c.c, c.r, p) ||
                        CircleCrossLine_angle_yn(ls[1].pa, ls[1].pb, c.c, c.r, p) ||
                        CircleCrossLine_angle_yn(ls[2].pa, ls[2].pb, c.c, c.r, p) ||
                        CircleCrossLine_angle_yn(ls[3].pa, ls[3].pb, c.c, c.r, p)) return true;
                if (inside_square(c.get_point_by_angle(p.first)) ||
                        inside_square(c.get_point_by_angle(p.second))) return true;
                return false;
            };

            // double nearest = 1e9;
            // bool ans = true;

            for (int i = 0; i < n; ++i) {
                // cerr << "checking circle i = " << i << " : " << cc[i] << endl;
                vector<pair<double, double>> unavil;
                for (int j = 0; j < n; ++j) if (j != i) {
                    auto tmp = CoverSegment(cc[i], cc[j]);
                    for (auto p : tmp) unavil.push_back(p);
                }
                sort(unavil.begin(), unavil.end());
                vector<pair<double, double>> avil;
                double cR = 0;
                for (auto p : unavil) {
                    if (p.first <= cR) ;
                    else avil.emplace_back(cR, p.first);
                    cR = max(cR, p.second);
                }
                if (cR < 2 * pi) avil.emplace_back(cR, 2 * pi);
                for (auto p : avil) {
                    // cerr << "checking available segment: " << p.first << " ~ " << p.second << endl;
                    if (intersect_circle_cube(cc[i], p)) {
                        // cerr << "the circle crossed the cube, return true" << endl;
                        return true;
                    }

                    // P p0 = P(cube_in, cube_in);
                    // P p1 = cc[i].get_point_by_angle(p.first);
                    // P p2 = cc[i].get_point_by_angle(p.second);
                    // double d = (p1 - p0).abs();
                    // if (d < nearest) {
                    //     cerr << "useful segment outside, from " << p1 << " to " << p2 << " around " << cc[i].c << endl;
                    //     nearest = d;

                    //     if (((p1 - p0) ^ (p2 - p0)) <= 0) ans = true;
                    //     else ans = false;
                    //     cerr << "ans = " << ans << endl;
                    // }
                }
            }

            // return ans;
            P p0(cube_in, cube_in);
            for (int i = 0; i < n; ++i) {
                if ((cc[i].c - p0).abs() <= cc[i].r) return false;
            }
            return true;
        };

        double L = 0, R = 200;
        int step = 100;
        while (step--) {
            double M = (L + R) / 2;
            if (ok(M)) L = M;
            else R = M;
        }

        cout << fixed << setprecision(20) << L << '\n';
    }
}
