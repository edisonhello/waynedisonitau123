#include <bits/stdc++.h>
using namespace std;

struct Frac {
    long long d, u;
    void norm() {
        if (u < 0) u *= -1, d *= -1;
        long long g = __gcd(u, d);
        d /= g, u /= g;
    }
    Frac() : d(1), u(0) {}
    Frac(pair<int, int> p) : d(p.first), u(p.second) { norm(); }
};

bool operator < (const Frac &a, const Frac &b) { return a.u * b.d < a.d * b.u; }
bool operator == (const Frac &a, const Frac &b) { return a.u * b.d == a.d * b.u; }

pair<int, int> operator - (const pair<int, int> &a, const pair<int, int> &b) { return make_pair(a.first - b.first, a.second - b.second); }
long long operator ^ (const pair<int, int> &a, const pair<int, int> &b) { return 1ll * a.first * b.second - 1ll * b.first * a.second; }


int main() {
    int n; cin >> n;
    vector<pair<int, int>> seg(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> seg[i].first >> seg[i].second;
    }

    auto GetLP = [&](int i) {
        return make_pair(i, seg[i].first);
    };
    auto GetRP = [&](int i) {
        return make_pair(i, seg[i].second);
    };

    vector<int> ucv = {1, 2};
    for (int i = 3; i <= n; ++i) {
        while (ucv.size() > 1u && ((GetLP(i) - GetLP(ucv[ucv.size() - 1])) ^ (GetLP(ucv[ucv.size() - 2]) - GetLP(ucv[ucv.size() - 1]))) >= 0) ucv.pop_back();
        ucv.push_back(i);
    }

    vector<int> dcv = {1, 2};
    for (int i = 3; i <= n; ++i) {
        while (dcv.size() > 1u && ((GetRP(i) - GetRP(dcv[dcv.size() - 1])) ^ (GetRP(dcv[dcv.size() - 2]) - GetRP(dcv[dcv.size() - 1]))) <= 0) dcv.pop_back();
        dcv.push_back(i);
    }

    vector<pair<int, int>> pu;
    for (int i : ucv) pu.emplace_back(GetLP(i));

    // cerr << "pu" << endl;
    // for (auto p : pu) {
    //     cerr << p.first << " " << p.second << endl;
    // }

    vector<pair<int, int>> pd;
    for (int i : dcv) pd.emplace_back(GetRP(i));

    // cerr << "pd" << endl;
    // for (auto p : pd) {
    //     cerr << p.first << " " << p.second << endl;
    // }

    auto Ceil = [&](int a, int b) {
        // cout << "a = " << a << " b = " << b << endl;
        return a / b + ((a ^ b) > 0 && a % b);
    };

    auto Eval = [&](pair<int, int> p, int x) {
        return p.second - 1LL * p.first * x;
    };

    int64_t res = 0;

    auto RealSolve = [&](pair<int, int> a, pair<int, int> b, int l, int r) -> int64_t {
        int64_t res = 0;
        res += 1LL * (r - l + 1) * b.second;
        res -= 1LL * b.first * (l + r) * (r - l + 1) / 2;
        res -= 1LL * (r - l + 1) * a.second;
        res += 1LL * a.first * (l + r) * (r - l + 1) / 2;
        res += r - l + 1;
        // for (int i = l; i <= r; ++i) {
        //     res += Eval(b, i) - Eval(a, i) + 1;
        // }
        return res;
    };

    auto Solve = [&](pair<int, int> a, pair<int, int> b, int l, int r) -> int64_t {
        int64_t res = 0;
        if (Eval(b, l) < Eval(a, l) && Eval(b, r) < Eval(a, r)) return 0LL;
        if (Eval(b, l) < Eval(a, l)) {
            int m = l;
            for (int d = 30; d >= 0; --d) {
                if (m + (1 << d) <= r) {
                    if (Eval(b, m + (1 << d)) < Eval(a, m + (1 << d))) m += (1 << d);
                }
            }
            // for (int i = m + 1; i <= r; ++i) assert(Eval(b, i) >= Eval(a, i));
            return RealSolve(a, b, m + 1, r);
        } 
        if (Eval(b, r) < Eval(a, r)) {
            int m = r;
            for (int d = 30; d >= 0; --d) {
                if (m - (1 << d) >= l) {
                    if (Eval(b, m - (1 << d)) < Eval(a, m - (1 << d))) m -= (1 << d);
                }
            }
            // for (int i = l; i <= m - 1; ++i) assert(Eval(b, i) >= Eval(a, i));
            return RealSolve(a, b, l, m - 1);
        }
        return RealSolve(a, b, l, r);
        // for (int i = l; i <= r; ++i) {
        //     res += max(0LL, Eval(b, i) - Eval(a, i) + 1);
        // }
    };

    swap(pd, pu);
    int di = 0, ui = pu.size() - 1;
    int nowm = 1050000000;


    while (di + 1 < pd.size() || ui - 1 >= 0) {
        int nxt = -1000000000;
        // cout << "di = " << di << " ui = " << ui << endl;
        if (di + 1 < pd.size()) {
            // cout << "slope = " << Ceil(pd[di + 1].second - pd[di].second, pd[di + 1].first - pd[di].first) << endl;
            nxt = max(nxt, Ceil(pd[di + 1].second - pd[di].second, pd[di + 1].first - pd[di].first));
        }
        if (ui - 1 >= 0) {
            // cout << "slope = " << Ceil(pu[ui].second - pu[ui - 1].second, pu[ui].first - pu[ui - 1].first) << endl;
            nxt = max(nxt, Ceil(pu[ui].second - pu[ui - 1].second, pu[ui].first - pu[ui - 1].first));
        }
        // cerr << "nxt = " << nxt << endl;
        res += Solve(pd[di], pu[ui], nxt, nowm);
        nowm = nxt - 1;
        while (di + 1 < pd.size() && Eval(pd[di + 1], nowm) >= Eval(pd[di], nowm)) di++;
        while (ui - 1 >= 0 && Eval(pu[ui - 1], nowm) <= Eval(pu[ui], nowm)) ui--;
    }
    res += Solve(pd.back(), pu[0], -1000000005, nowm);
    cout << res << "\n";
}

