#include <bits/stdc++.h>
using namespace std;

__int128 cnk[50][50];
int c[50];

/* __int128 abs(__int128 v) {
    if (v < 0) return -v;
    return v;
} */
struct fraction {
    __int128 u, d; // u / d
    void general() {
        __int128 g = __gcd(abs(u), abs(d));
        u /= g, d /= g;
        if (d < 0) u = -u, d = -d;
    }
    fraction(): u(0), d(1) {}
    fraction(__int128 x): u(x), d(1) {}
    fraction(__int128 u, __int128 d): u(u), d(d) { general(); }
    fraction operator+(const fraction &f) const {
        fraction res(u * f.d + f.u * d, d * f.d);
        res.general();
        return res;
    }
    fraction operator-(const fraction &f) const {
        fraction res(u * f.d - f.u * d, d * f.d);
        res.general();
        return res;
    }
    fraction operator*(const fraction &f) const {
        fraction res(u * f.u, d * f.d);
        res.general();
        return res;
    }
    fraction operator/(const fraction &f) const {
        fraction res(u * f.d, d * f.u);
        res.general();
        return res;
    }
};

struct poly {
    vector<fraction> v;
    poly() {}
    poly(vector<__int128> &c) {
        for (int i = 0; i < c.size(); ++i) v.emplace_back(c[i]);
    }
    poly operator*(const fraction &p) const {
        poly res = (*this);
        for (int i = 0; i < res.v.size(); ++i) res.v[i] = res.v[i] * p;
        return res;
    }
    poly operator-(const poly &p) const {
        poly res = (*this);
        for (int i = 0; i < res.v.size(); ++i) res.v[i] = res.v[i] - p.v[i];
        return res;
    }
};

ostream &operator<<(ostream &s, __int128 v) {
    if (v == 0) return s << 0, s;
    stack<int> st;
    while (v) st.push(v % 10), v /= 10;
    while (st.size()) s << st.top(), st.pop();
    return s;
}


int main() {
    int tc; cin >> tc;
    cnk[0][0] = 1;
    for (int i = 1; i <= 30; ++i) {
        for (int j = 0; j <= i; ++j) {
            cnk[i][j] = cnk[i - 1][j];
            if (j) cnk[i][j] += cnk[i - 1][j - 1];
        }
    }
    while (tc--) {
        memset(c, 0, sizeof(c));
        int t; cin >> t;
        for (int i = 0; i <= t; ++i) cin >> c[i];
        vector<__int128> vc(c, c + t + 2);
        poly p = poly(vc);
        __int128 ans = abs(c[0]);
        for (int i = t; i >= 0; --i) {
            fraction ab = p.v[i] / fraction(i + 1);
            ans += abs(ab.u);
            // cout << "add = " << ab.u << endl;
            poly xi; xi.v.resize(t + 2);
            for (int j = 0; j <= t + 1; ++j) {
                if (j == i + 1) xi.v[j] = fraction(1, 1);
                else xi.v[j] = fraction(0, 1);
            }
            poly xj; xj.v.resize(t + 2);
            for (int j = 0; j <= t + 1; ++j) {
                __int128 cc = cnk[i + 1][j];
                if ((i + 1 - j) & 1) cc = -cc;
                xj.v[j] = fraction(cc, 1);
            }
            xi = xi - xj;
            xi = xi * (p.v[i] / fraction(i + 1));
            p = p - xi;
            // for (int j = 0; j <= t + 1; ++j) cout << p.v[j].u << "/" << p.v[j].d << ", ";
            // cout << endl;
        }
        cout << ans << endl;
    }
    return 0;
}
