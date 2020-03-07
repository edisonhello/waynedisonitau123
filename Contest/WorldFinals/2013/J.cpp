#include <bits/stdc++.h>
using namespace std;

#define sq(x) ((x) * (x))

const double eps = 1e-9;
const double pi = acos(-1);

struct P {
    double x, y;
    P(double x = 0, double y = 0) : x(x), y(y) {}
    double abs() const { return hypot(x, y); }
} ps[1005];

P operator+ (P a, P b) { return P(a.x + b.x, a.y + b.y); }
P operator- (P a, P b) { return P(a.x - b.x, a.y - b.y); }
double operator* (P a, P b) { return a.x * b.x + a.y * b.y; }
P operator* (P a, double b) { return P(a.x * b, a.y * b); }
double operator^ (P a, P b) { return a.x * b.y - a.y * b.x; }

double SectorArea(P a, P b, double r) {
    double o = atan2(a.y, a.x) - atan2(b.y, b.x);
    while (o <= 0) o += 2 * pi;
    while (o >= 2 * pi) o -= 2 * pi;
    o = min(o, 2 * pi - o);
    return r * r * o / 2;
}

vector<P> CircleCrossLine(P a, P b, P o, double r) {
    double x = b.x - a.x, y = b.y - a.y, A = sq(x) + sq(y), B = 2 * x * (a.x - o.x) + 2 * y * (a.y - o.y);
    double C = sq(a.x - o.x) + sq(a.y - o.y) - sq(r), d = B * B - 4 * A * C;
    vector<P> t;
    if (d >= -eps) {
        d = max(0., d);
        double i = (-B - sqrt(d)) / (2 * A);
        double j = (-B + sqrt(d)) / (2 * A);
        if (i - 1.0 <= eps && i >= -eps) t.emplace_back(a.x + i * x, a.y + i * y);
        if (j - 1.0 <= eps && j >= -eps) t.emplace_back(a.x + j * x, a.y + j * y);
    }
    return t;
}

double AOCT(P a, P b, double r) {
    bool ina = a.abs() < r, inb = b.abs() < r;
    auto p = CircleCrossLine(a, b, P(0, 0), r);
    if (ina) {
        if (inb) return abs(a ^ b) / 2;
        return SectorArea(b, p[0], r) + abs(a ^ p[0]) / 2;
    }
    if (inb) return SectorArea(p[0], a, r) + abs(p[0] ^ b) / 2;
    if (p.size() == 2u) return SectorArea(a, p[0], r) + SectorArea(p[1], b, r) + abs(p[0] ^ p[1]) / 2;
    else return SectorArea(a, b, r);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, r; cin >> n >> r;
    for (int i = 0; i < n; ++i) {
        cin >> ps[i].x >> ps[i].y;
    }
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        double add = AOCT(ps[i], ps[j], r) * ((ps[i] ^ ps[j]) > 0 ? 1 : -1);
        // cerr << i << ' ' << add << endl;
        ans += add;
    }

    cout << fixed << setprecision(10) << ans << endl;
}
