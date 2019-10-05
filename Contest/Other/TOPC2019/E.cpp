#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

using DB = __float128;
const DB eps = 1e-9;

struct P;

struct PD {
    DB x, y;
    PD(DB x, DB y) : x(x), y(y) {}
    PD(P p);
    PD(const PD &p) : x(p.x), y(p.y) {}
    PD operator + (P b);
    PD operator + (PD b) { return PD(x + b.x, y + b.y); }
    PD operator - (PD b) { return PD(x - b.x, y - b.y); }
    PD operator * (DB b) { return PD(x * b, y * b); }
    PD operator / (DB b) { return PD(x / b, y / b); }
    DB operator ^ (P b);
    DB operator ^ (PD b);
    DB abs() { return hypot((long double)x, (long double)y); }
    PD unit() { return *this / abs(); }
    DB norm() { return x * x + y * y; }
};

struct P {
    long long x, y;
    P() : x(0), y(0) {}
    P(long long x, long long y) : x(x), y(y) {}
    P operator + (P b) { return P(x + b.x, y + b.y); }
    PD operator + (PD b) { return PD(x + b.x, y + b.y); }
    P operator - (P b) { return P(x - b.x, y - b.y); }
    PD operator - (PD b) { return PD(x - b.x, y - b.y); }
    PD operator * (DB b) { return PD(x * b, y * b); }
    PD operator / (DB b) { return PD(x / b, y / b); }
    long long operator ^ (P b) { return x * b.y - y * b.x; }
    DB operator ^ (PD b) { return x * b.y - y * b.x; }
    bool operator == (P &b) { return x == b.x && y == b.y; }
    DB abs() { return hypot(x, y); }
    PD unit() { return *this / abs(); }
};

PD::PD(P p) : x(p.x), y(p.y) {}
PD PD::operator + (P b) { return PD(x + b.x, y + b.y); }
DB PD::operator ^ (P b) { return x * b.y - y * b.x; }
DB PD::operator ^ (PD b) { return x * b.y - y * b.x; }


PD cen3(PD a, PD b, PD c) {
    PD p0 = b - a, p1 = c - a;
    DB c1 = p0.norm() * 0.5, c2 = p1.norm() * 0.5;
    DB d = p0 ^ p1;
    DB x = a.x + (c1 * p1.y - c2 * p0.y) / d;
    DB y = a.y + (c2 * p0.x - c1 * p1.x) / d;
    return PD(x, y);
}

pair<PD, DB> min_enc(vector<P> &ps) {
    // cout << "with P set: "; for (P p : ps) cout << p.x << ' ' << p.y << '\n'; cout << endl;
    random_shuffle(ps.begin(), ps.end());
    DB r = 0;
    PD c(0, 0);
    for (int i = 0; i < (int)ps.size(); ++i) {
        if ((c - ps[i]).norm() <= r) continue;
        c = ps[i];
        r = 0;
        for (int j = 0; j < i; ++j) {
            if ((c - ps[j]).norm() <= r) continue;
            c = (ps[i] + ps[j]) / 2;
            r = (ps[j] - c).norm();
            for (int k = 0; k < j; ++k) {
                if ((c - ps[k]).norm() <= r) continue;
                c = cen3(ps[i], ps[j], ps[k]);
                r = (ps[k] - c).norm();
            }
        }
    }
    // cout << "c = " << (long double)c.x << ' ' << (long double)c.y << " r = " << (long double)r << endl;
    return make_pair(c, sqrt((long double)r));
}

bool check(vector<P> &ps, P outp, int r) {
    auto cc = min_enc(ps);
    if (cc.second > r) return 0;
    if ((outp - cc.first).abs() > r) {
        cout << outp.x << ' ' << outp.y << endl;
        cout << fixed << setprecision(20) << (long double)cc.first.x << ' ' << (long double)cc.first.y << endl;
        return 1;
    }
    PD ncc = outp + (cc.first - outp).unit() * (r + eps * 2);
    for (auto &p : ps) {
        if ((ncc - p).abs() >= r) return false;
    }
    cout << outp.x << ' ' << outp.y << endl;
    cout << fixed << setprecision(20) << (long double)ncc.x << ' ' << (long double)ncc.y << endl;
    return 1;
}

#define crx(a, b, c) ((b - a) ^ (c - a))

vector<P> convex(vector<P> &ps) {
    vector<P> p;
    sort(ps.begin(), ps.end(), [&] (P a, P b) { return a.x == b.x ? a.y < b.y : a.x < b.x; });
    for (int i = 0; i < (int)ps.size(); ++i) {
        while (p.size() >= 2 && crx(p[p.size() - 2], ps[i], p[p.size() - 1]) >= 0) p.pop_back();
        p.push_back(ps[i]);
    }
    int t = p.size();
    for (int i = (int)ps.size() - 2; i >= 0; --i) {
        while ((int)p.size() > t && crx(p[p.size() - 2], ps[i], p[p.size() - 1]) >= 0) p.pop_back();
        p.push_back(ps[i]);
    }
    p.pop_back();
    return p;
}

int main() {
    // srand(880301);
    mt19937 rng(12487);
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, r; cin >> n >> r;

    vector<P> ps(n);
    for (int i = 0; i < n; ++i) {
        cin >> ps[i].x >> ps[i].y;
    }
    if (n == 1) {
        cout << ps[0].x << ' ' << ps[0].y << endl;
        cout << "2000000000 2000000000" << endl;
        exit(0);
    }
    {
        auto C = min_enc(ps);
        if (C.second <= r) {
            double dd = -1e9;
            int z = -1;
            int cnt = 0;
            for (int i = 0; i < n; ++i) {
                double dist = (ps[i] - C.first).abs();
                if (dist >= dd + eps) {
                    dd = dist;
                    z = i;
                    cnt = 1;
                } else if (abs(dist - dd) < eps) ++cnt;
            }
            // cout << "dd = " << dd << ", r -eps = " << (long double)(r - eps) << endl;
            if (cnt <= 1 || dd <= r - eps) {
                PD cc = ps[z] + (C.first - ps[z]).unit() * (r + eps * 2);
                cout << ps[z].x << ' ' << ps[z].y << '\n';
                cout << fixed << setprecision(20) << (long double)cc.x << ' ' << (long double)cc.y << '\n';
                exit(0);
            }
        }
    }
    PD cen(0, 0);
    for (auto &p : ps) cen = cen + p;
    cen = cen / n;

    vector<P> tb = convex(ps);
    sort(tb.begin(), tb.end(), [&] (P x, P y) { return (cen - x).abs() > (cen - y).abs(); });
    const int kMagic = 50;
    for (int i = 0; i < (int)tb.size(); i += kMagic) {
        int dist = min(kMagic, (int)tb.size() - i);
        shuffle(tb.begin() + i, tb.begin() + i + dist, rng);
    }
    // vector<double> ang(tb.size());
    // for (int i = 0; i < (int)tb.size(); ++i) {
    //     int j = (i == (int)tb.size() - 1 ? 0 : i + 1);
    //     int h = (i == 0 ? (int)tb.size() - 1 : i - 1);
    //     ((j - i) * (h - i)) / 
    // }
    
    for (auto &p : tb) {
        vector<P> nps; nps.reserve(n - 1);
        for (auto &pp : ps) {
            if (pp == p) continue;
            nps.push_back(pp);
        }
        if (check(nps, p, r)) exit(0);
        if (clock() > 2.85 * CLOCKS_PER_SEC) break;
    }
    cout << -1 << endl;
}
