#include <bits/stdc++.h>
using namespace std;
#define sq(x) ((x) * (x))

const double pi = acos(-1);
const double eps = 1e-9;

bool same(double a, double b) {
    return abs(a - b) < eps;
}

double sign(double x) {
    if (same(x, 0)) return 0;
    if (x > 0) return 1;
    return -1;
}

struct P {
    double x, y;
    P() : x(0), y(0) {}
    P(double x, double y) : x(x), y(y) {}
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
        return P(c * x - s * y, s * x + c * y);
    }
    double angle() { return atan2(y, x); }
};

ostream& operator<< (ostream &o, const P &a) {
    o << "(" << a.x << ", " << a.y << ")";
    return o;
}

struct L {
    double a, b, c;
    P pa, pb;
    L() : a(0), b(0), c(0), pa(), pb() {}
    L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
    P project(P p) { return pa + (pb - pa).unit() * ((pb - pa) * (p - pa) / (pb - pa).abs()); }
    P reflect(P p) { return p + (project(p) - p) * 2; }
    double get_ratio(P p) { return (p - pa) * (pb - pa) / ((pb - pa).abs() * (pb - pa).abs()); }
};

bool SegmentIntersect(P p1, P p2, P p3, P p4) {
    if (max(p1.x, p2.x) < min(p3.x, p4.x) || max(p3.x, p4.x) < min(p1.x, p2.x)) return false;
    if (max(p1.y, p2.y) < min(p3.y, p4.y) || max(p3.y, p4.y) < min(p1.y, p2.y)) return false;
    return sign((p3 - p1) ^ (p4 - p1)) * sign((p3 - p2) ^ (p4 - p2)) <= 0 &&
           sign((p1 - p3) ^ (p2 - p3)) * sign((p1 - p4) ^ (p2 - p4)) <= 0;
}

P Intersect(L x, L y) { return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a); }

struct C {
    P c;
    double r;
    C() : c(), r() {}
    C(P c, double r) : c(c), r(r) {}
};

vector<P> CircleCrossLine(P a, P b, P o, double r) {
    double x = b.x - a.x, y = b.y - a.y, A = sq(x) + sq(y), B = 2 * x * (a.x - o.x) + 2 * y *(a.y - o.y);
    double C = sq(a.x - o.x) + sq(a.y - o.y) - sq(r), d = B * B - 4 * A * C;
    vector<P> t;
    // cerr << "d = " << d << endl;
    if (d >= -eps) { 
        d = max(0., d);
        double i = (-B - sqrt(d)) / (2 * A);
        double j = (-B + sqrt(d)) / (2 * A);
        if (i - 1 <= eps && i >= -eps) t.emplace_back(a.x + i * x, a.y + i * y);
        if (j - 1 <= eps && j >= -eps) t.emplace_back(a.x + j * x, a.y + j * y);
    }
    return t;
}

struct Wall {
    P p1, p2;
    bool circle;
    double r;
    vector<pair<double, double>> segs;
};

vector<pair<double, double>> CalcAngle(double a, double mid, double b) {
    vector<pair<double, double>> r;
    auto Get = [&] (double x) { return x < 0 ? x + 2 * pi : x; };
    if (Get(a - mid) > Get(mid - a)) {
        if (b > a) {
            r.emplace_back(a, b);
        } else {
            r.emplace_back(a, pi);
            r.emplace_back(-pi, b);
        }
    } else {
        if (a > b) {
            r.emplace_back(b, a);
        } else {
            r.emplace_back(-pi, a);
            r.emplace_back(b, pi);
        }
    }
    return r;
}

struct Edge {
    int to, cap, rev;
    Edge(int a, int b, int c) : to(a), cap(b), rev(c) {}
};

int Flow(vector<vector<Edge>> g, int S, int T) {
    int N = g.size(), res = 0;
    while (true) {
        vector<int> lev(N, -1);
        lev[S] = 0;
        vector<int> que(1, S);
        for (int it = 0; it < que.size(); ++it) {
            int x = que[it];
            for (Edge &e : g[x]) {
                if (lev[e.to] == -1 && e.cap > 0) {
                    lev[e.to] = lev[x] + 1;
                    que.push_back(e.to);
                }
            }
        }
        if (lev[T] == -1) break;

        auto Dfs = [&](auto dfs, int x, int f = 1'000'000'000) -> int {
            if (x == T) return f;
            int res = 0;
            for (Edge &e : g[x]) {
                if (e.cap == 0) continue;
                if (lev[e.to] == lev[x] + 1) {
                    int r = dfs(dfs, e.to, min(e.cap, f - res));
                    res += r;
                    e.cap -= r;
                    g[e.to][e.rev].cap += r;
                }
            }
            if (res == 0) lev[x] = -1;
            return res;
        };

        res += Dfs(Dfs, S);
    }
    return res;
}

void solve(int n, int a, int g) {
    vector<Wall> walls;

    auto BuildWall = [&] (P prevpt, char type, P pt, P tang) {
        Wall wall;
        if (type == 's') {
            wall.p1 = prevpt;
            wall.p2 = pt;
            wall.circle = false;
        } else {
            wall.circle = true;
            L tangent(prevpt, prevpt + tang.spin(pi / 2));
            P mid = (prevpt + pt) / 2;
            P revdir = (pt - prevpt).spin(pi / 2);
            L midline(mid, mid + revdir);
            P cen = Intersect(tangent, midline);
            wall.p1 = cen;
            P epsmove = prevpt + tang.unit();
            auto segs = CalcAngle((prevpt - cen).angle(), (epsmove - cen).angle(), (pt - cen).angle());
            for (auto &p : segs) wall.segs.push_back(p);
            wall.r = (pt - cen).abs();
        }

        walls.push_back(wall);
    };

    auto CanSee = [&] (P a, P b) {
        // cerr << "check " << a << " and " << b << endl;
        for (Wall &wall : walls) {
            if (wall.circle) {
                // cerr << "circle cen " << wall.p1 << ", r " << wall.r << endl;
                vector<P> ps = CircleCrossLine(a, b, wall.p1, wall.r);
                for (P &p : ps) {
                    for (auto &pp : wall.segs) {
                        double o = (p - wall.p1).angle();
                        // cerr << "l o r " << pp.first << ' ' << o << ' ' << pp.second << endl;
                        if (pp.first <= o && o <= pp.second) return false;
                    }
                }
            } else {
                // cerr << "seg " << wall.p1 << " " << wall.p2 << endl;
                if (SegmentIntersect(a, b, wall.p1, wall.p2)) return false;
            }
        }
        return true;
    };

    while (n--) {
        int m; cin >> m;
        P fpt, ppt, tang;
        char ptp;

        cin >> fpt.x >> fpt.y; ppt = fpt;
        cin >> ptp;
        if (ptp == 'c') {
            cin >> tang.x >> tang.y;
        }

        for (int i = 1; i < m; ++i) {
            P pt; cin >> pt.x >> pt.y;
            BuildWall(ppt, ptp, pt, tang);
            ppt = pt;
            cin >> ptp;
            if (ptp == 'c') {
                cin >> tang.x >> tang.y;
            }
        }

        BuildWall(ppt, ptp, fpt, tang);
    }

    vector<pair<P, int>> art(a), guard(g);
    for (int i = 0; i < a; ++i) {
        cin >> art[i].first.x >> art[i].first.y >> art[i].second;
    }
    for (int i = 0; i < g; ++i) {
        cin >> guard[i].first.x >> guard[i].first.y >> guard[i].second;
    }


    vector<vector<Edge>> gr(a + g + 2);

    auto AddEdge = [&](int a, int b, int c) {
        gr[a].emplace_back(b, c, (int)gr[b].size() - 0);
        gr[b].emplace_back(a, 0, (int)gr[a].size() - 1);
    };

    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < g; ++j) {
            // cerr << "i j " << i << ' ' << j << endl;
            if (CanSee(art[i].first, guard[j].first)) {
                // cerr << "See " << i << ' ' << j << endl;
                AddEdge(j, i + g, 1);
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < a; ++i) sum += art[i].second;
    for (int i = 0; i < a; ++i) AddEdge(i + g, a + g + 1, art[i].second);
    for (int i = 0; i < g; ++i) AddEdge(a + g, i, guard[i].second);
    
    if (Flow(gr, a + g, a + g + 1) == sum) cout << "Yes\n";
    else cout << "No\n";
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    for (int T = 1; ; ++T) {
        int n, a, g; cin >> n >> a >> g;
        if (n == 0) break;
        cout << "Case " << T << ": ";
        solve(n, a, g);
    }
}

