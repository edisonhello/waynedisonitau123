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

vector<P> pol[205];

vector<pair<int, double>> g[205];

void addedge(int a, int b, double x) {
    g[a].emplace_back(b, x);
    g[b].emplace_back(a, x);
}

double calc1(P a, P b, P c) {
    L l(b, c);
    double rt = 1e9;
    rt = min(rt, (a - b).abs());
    rt = min(rt, (a - c).abs());
    P p = l.project(a);
    if (l.inside(p)) rt = min(rt, (a - p).abs());
    return rt;
}

double calc2(P a, P b, P c, P d) {
    double rt = 1e9;
    rt = min(rt, calc1(a, c, d));
    rt = min(rt, calc1(b, c, d));
    rt = min(rt, calc1(c, a, b));
    rt = min(rt, calc1(d, a, b));
    return rt;
}

bitset<205> ok;
double dd[205];

double dijk(int s, int t) {
    for (int i = 0; i < 205; ++i) dd[i] = 1e9;
    dd[s] = 0; 
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.emplace(0, s);
    while (pq.size()) {
        while (pq.size() && ok[pq.top().second]) pq.pop();
        if (pq.empty()) break;
        int now = pq.top().second;
        ok[now] = 1;
        for (auto &e : g[now]) {
            if (dd[e.first] > dd[now] + e.second) {
                dd[e.first] = dd[now] + e.second;
                pq.emplace(dd[e.first], e.first);
            }
        }
    }
    return dd[t];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int w, n; cin >> w >> n;
    for (int i = 1; i <= n; ++i) {
        int m; cin >> m;
        pol[i].resize(m);
        for (int j = 0; j < m; ++j) cin >> pol[i][j].x >> pol[i][j].y;
    }
    for (int i = 1; i <= n; ++i) {
        double xmin = 1e9;
        double xmax = 0;
        for (int j = 0; j < pol[i].size(); ++j) {
            xmin = min(xmin, pol[i][j].x);
            xmax = max(xmax, pol[i][j].x);
        }
        addedge(0, i, xmin);
        addedge(i, n + 1, w - xmax);
    }
    addedge(0, n + 1, w);
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            double mind = 1e9;
            for (int x = 0; x < pol[i].size(); ++x) {
                for (int y = 0; y < pol[j].size(); ++y) {
                    mind = min(mind, (pol[i][x] - pol[j][y]).abs());
                }
            }
            for (int x = 0; x < pol[i].size(); ++x) {
                int xx = (x + 1) % pol[i].size();
                for (int y = 0; y < pol[j].size(); ++y) {
                    mind = min(mind, calc1(pol[j][y], pol[i][x], pol[i][xx]));
                }
            }
            for (int x = 0; x < pol[i].size(); ++x) {
                for (int y = 0; y < pol[j].size(); ++y) {
                    int yy = (y + 1) % pol[j].size();
                    mind = min(mind, calc1(pol[i][x], pol[j][y], pol[j][yy]));
                }
            }
            for (int x = 0; x < pol[i].size(); ++x) {
                int xx = (x + 1) % pol[i].size();
                for (int y = 0; y < pol[j].size(); ++y) {
                    int yy = (y + 1) % pol[j].size();
                    mind = min(mind, calc2(pol[i][x], pol[i][xx], pol[j][y], pol[j][yy]));
                }
            }
            addedge(i, j, mind);
        }
    }    
    cout << fixed << setprecision(10) << dijk(0, n + 1) << endl;
}
