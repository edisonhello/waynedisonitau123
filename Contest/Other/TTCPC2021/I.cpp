#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

bool same(double a, double b) { return abs(a - b) < eps; }

struct P {
    double x, y;

    P() = default;
    P(double x, double y) : x(x), y(y) {}

    P operator+ (const P b) { return P{x + b.x, y + b.y}; }
    P operator- (const P b) { return P{x - b.x, y - b.y}; }
    double operator* (const P b) { return x * b.x + y * b.y; }
    P operator* (const double b) { return P{x * b, y * b}; }
    P operator/ (const double b) { return P{x / b, y / b}; }
    double operator^ (const P b) { return x * b.y - y * b.x; }

    double abs() { return hypot(x, y); }
    P spin() { return P{y, -x}; }
    P unit() { return *this / abs(); }

    bool operator< (const P b) const { return same(x, b.x) ? same(y, b.y) ? false : y < b.y : x < b.x; }
};

ostream& operator<< (ostream &o, P p) {
    o << "(" << p.x << ", " << p.y << ")";
    return o;
}

struct L {
    double a, b, c;
    P pa, pb;
    L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}

    P project(P p) { return pa + (pb - pa).unit() * ((pb - pa) * (p - pa) / (pb - pa).abs()); }
};

int main() {
    int n; cin >> n;
    vector<pair<int, int>> ps(n);
    for (int i = 0; i < n; ++i) {
        cin >> ps[i].first >> ps[i].second;
    }

    vector<int> id(n), pos(n);
    vector<pair<int, int>> line(n * (n - 1) / 2);
    int m = -1;
    for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) line[++m] = make_pair(i, j); ++m;
    
    sort(line.begin(), line.end(), [&] (const pair<int, int> &a, const pair<int, int> &b) -> bool {
        if (ps[a.first].first == ps[a.second].first) return 0;
        if (ps[b.first].first == ps[b.second].first) return 1;
        return (double)(ps[a.first].second - ps[a.second].second) / (ps[a.first].first - ps[a.second].first) < (double)(ps[b.first].second - ps[b.second].second) / (ps[b.first].first - ps[b.second].first);
    });

    for (int i = 0; i < n; ++i) id[i] = i;
    sort(id.begin(), id.end(), [&] (const int &a, const int &b) { return ps[a] < ps[b]; });
    for (int i = 0; i < n; ++i) pos[id[i]] = i;

    double ans1 = 0;

    auto updans1 = [&] (int p, int l1, int l2) {
        P pp{ps[p].first, ps[p].second},
          pl1{ps[l1].first, ps[l1].second},
          pl2{ps[l2].first, ps[l2].second};

        L l(pl1, pl2);
        double d = (pp - l.project(pp)).abs();

        ans1 = max(ans1, d);
    };

    for (int i = 0; i < m; ++i) {
        auto l = line[i];

        int mi = pos[l.first], ma = pos[l.second];
        if (ma < mi) swap(ma, mi);

        if (mi > 0) updans1(id[mi - 1], l.first, l.second);
        if (ma < n - 1)  updans1(id[ma + 1], l.first, l.second);

        tie(pos[l.first], pos[l.second], id[pos[l.first]], id[pos[l.second]]) = 
            make_tuple(pos[l.second], pos[l.first], l.second, l.first);
    }

    // cout << fixed << setprecision(3) << ans1 << endl;

    vector<P> ps2;
    for (int i = 0; i < n; ++i) ps2.emplace_back(P{ps[i].first, ps[i].second});
    vector<tuple<int, int, int>> line2;
    m = -1;
    line2.resize(n * (n - 1) / 2 * 2);
    map<pair<int, int>, pair<int, int>> toq;
    for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) line2[++m] = make_tuple(1, i, j);
    for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
        P pi{ps[i].first, ps[i].second},
          pj{ps[j].first, ps[j].second};
        P dir = pi - pj;
        P mid = (pi + pj) / 2;

        line2[++m] = make_tuple(-1, ps2.size(), ps2.size() + 1);
        toq[minmax((int)ps2.size(), (int)ps2.size() + 1)] = minmax(i, j);
        ps2.emplace_back(mid);
        ps2.emplace_back(mid + dir.spin());
    }
    ++m;

    sort(line2.begin(), line2.end(), [&] (const tuple<int, int, int> &a, const tuple<int, int, int> &b) -> bool {

        if (ps2[get<1>(a)].x == ps2[get<2>(a)].x) return 0;
        if (ps2[get<1>(b)].x == ps2[get<2>(b)].x) return 1;
        return (double)(ps2[get<1>(a)].y - ps2[get<2>(a)].y) / (ps2[get<1>(a)].x - ps2[get<2>(a)].x) < (double)(ps2[get<1>(b)].y - ps2[get<2>(b)].y) / (ps2[get<1>(b)].x - ps2[get<2>(b)].x);
    });

    for (int i = 0; i < n; ++i) id[i] = i;
    sort(id.begin(), id.end(), [&] (const int &a, const int &b) { return ps[a] < ps[b]; });
    for (int i = 0; i < n; ++i) pos[id[i]] = i;

    double ans2 = 0;

    for (auto [t, p1i, p2i] : line2) {
        if (t == 1) {
            tie(pos[p1i], pos[p2i], id[pos[p1i]], id[pos[p2i]]) = 
                make_tuple(pos[p2i], pos[p1i], p2i, p1i);
        } else if (t == -1) {
            auto [i, j] = toq[minmax(p1i, p2i)];
            // cerr << "p1i p2i i j " << p1i << ' ' << p2i << ' ' << i << ' ' << j << endl;
            if (abs(pos[i] - pos[j]) == 1) {
                ans2 = max(ans2, (ps2[i] - ps2[j]).abs());
            }
        }
    }

    cout << fixed << setprecision(12);
    cout << max(ans1, ans2) << endl;
}
