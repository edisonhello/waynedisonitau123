#include <bits/stdc++.h>
using namespace std;

struct Poly {
    int p;
    vector<int> cf;
    
    Poly() = default;
    Poly(int n, int p) : cf(n), p(p) {}
    Poly(vector<int> v, int p) : p(p), cf(v) {}

    Poly operator+(const Poly &rhs) const {
        Poly res(max(cf.size(), rhs.cf.size()), p);
        for (int i = 0; i < cf.size(); ++i) {
            res.cf[i] = cf[i];
        }
        for (int i = 0; i < rhs.cf.size(); ++i) {
            res.cf[i] += rhs.cf[i];
            if (res.cf[i] >= p) res.cf[i] -= p;
        }
        while (res.cf.size() > 0 && res.cf.back() == 0) res.cf.pop_back();
        return res;
    }

    Poly operator-(const Poly &rhs) const {
        Poly res(max(cf.size(), rhs.cf.size()), p);
        for (int i = 0; i < cf.size(); ++i) {
            res.cf[i] = cf[i];
        }
        for (int i = 0; i < rhs.cf.size(); ++i) {
            res.cf[i] += p - rhs.cf[i];
            if (res.cf[i] >= p) res.cf[i] -= p;
        }
        while (res.cf.size() > 0 && res.cf.back() == 0) res.cf.pop_back();
        return res;
    }

    Poly operator*(const Poly &rhs) const {
        if (cf.empty() && rhs.cf.empty()) {
            return Poly(0, p);
        }
        Poly res(cf.size() + rhs.cf.size() - 1, p);
        for (int i = 0; i < cf.size(); ++i) {
            for (int j = 0; j < rhs.cf.size(); ++j) {
                res.cf[i + j] += 1LL * cf[i] * rhs.cf[j] % p;
                if (res.cf[i + j] >= p) res.cf[i + j] -= p;
            }
        }
        while (res.cf.size() > 0 && res.cf.back() == 0) res.cf.pop_back();
        return res;
    }

    int Deg() const { return (int)cf.size() - 1; }

    Poly MultX() const {
        Poly res(cf.size() + 1, p);
        for (int i = 0; i < cf.size(); ++i) {
            res.cf[i + 1] = cf[i];
        }
        return res;
    }

    int fpow(int a, int n) const {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % p;
            a = 1LL * a * a % p;
            n >>= 1;
        }
        return res;
    }

    Poly operator%(const Poly &rhs) const {
        if (rhs.cf.size() > cf.size()) return *this;
        Poly res = *this;
        for (int i = (int)res.cf.size() - 1; i + 1 >= (int)rhs.cf.size(); --i) {
            int dv = 1LL * res.cf[i] * fpow(rhs.cf.back(), p - 2) % p;
            for (int j = 0; j < rhs.cf.size(); ++j) {
                int f = 1LL * dv * rhs.cf[rhs.cf.size() - 1 - j] % p;
                (res.cf[i - j] += p - f) %= p;
            }
            assert(res.cf[i] == 0);
        }
        while (res.cf.size() > 0 && res.cf.back() == 0) res.cf.pop_back();
        return res;
    }

    friend ostream &operator<<(ostream &os, const Poly &p) {
        os << "p = " << p.p << ": ";
        for (int i = p.cf.size() - 1; i >= 0; --i) os << p.cf[i] << " ";
        return os;
    }
};

Poly fdiv(int deg, const Poly &p) {
    if (deg < p.Deg()) {
        Poly res(deg + 1, p.p);
        res.cf[deg] = 1;
        return res;
    }
    // cerr << "deg = " << deg << endl;
    Poly poly = fdiv(deg / 2, p);
    // cerr << "poly1: " << poly << endl;
    poly = poly * poly;
    if (deg & 1) poly = poly.MultX();
    // cerr << "poly2: " << poly << endl;
    // cerr << "res: " << poly % p << endl;
    return poly % p;
}

int Solve(int n, int p) {
    Poly poly(n + 1, p);
    for (int i = 0; i <= n; ++i) cin >> poly.cf[i]; 
    for (int i = 0; i <= n; ++i) {
        poly.cf[i] %= p;
        poly.cf[i] += p;
        poly.cf[i] %= p;
    }
    while (!poly.cf.empty() && poly.cf.back() == 0) poly.cf.pop_back();
    if (poly.cf.empty()) return p;
    if (poly.cf.size() == 1) {
        if (poly.cf[0] == 0) return p;
        return 0;
    }
    Poly rd = fdiv(p, poly);
    Poly add(2, p);
    add.cf[1] = p - 1;
    rd = rd + add;
    // cerr << "rd: " << rd << endl;
    while (poly.Deg() >= 0 && rd.Deg() >= 0) {
        // cerr << "poly: " << poly << endl;
        // cerr << "rd: " << rd << endl;
        // cerr << "poly.deg = " << poly.Deg() << endl;
        // cerr << "rd.deg = " << rd.Deg() << endl;
        // int key;
        // cin >> key;
        if (poly.Deg() >= rd.Deg()) {
            poly = poly % rd;
        } else {
            rd = rd % poly;
        }
    }
    if (rd.Deg() == -1) swap(rd, poly);
    return rd.Deg();
}

int main() {
    int n, p;
    while (cin >> n >> p) {
        if (p == 0) break;
        cout << Solve(n, p) << "\n";
    }
    return 0;
}

