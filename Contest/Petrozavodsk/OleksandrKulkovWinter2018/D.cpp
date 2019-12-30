#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

inline int norm(int x) {
    return x < 0 ? x + mod : x;
}
inline int norm(long long x) {
    return norm((int)(x % mod));
}

int pw(int b, int n, int m) {
    int a = 1;
    while (n) {
        if (n & 1) a = 1ll * a * b % m;
        b = 1ll * b * b % m;
        n >>= 1;
    }
    return a;
}

int inv(int x) {
    return pw(x, mod - 2, mod);
}

struct Poly {
    vector<int> coef;
    int& operator[] (const int x) { return coef[x]; }
    const int& operator[] (const int x) const { return coef[x]; }
    int size() const { return coef.size(); }
    void resize(int z) { coef.resize(z); }
    void Multi(int x) { 
        for (int i = 0; i < x; ++i) 
            coef.insert(coef.begin(), 0); 
    }
    void Divide(const Poly &q) {
        // cout << "Divide " << *this << " by " << q << endl;
        for (int i = (int)coef.size() - 1; i >= (int)q.size() - 1; --i) {
            int multi = norm(coef[i] * 1ll * inv(q.coef.back()));
            // cout << "i = " << i << ", multi = " << multi << endl;
            for (int j = i, k = q.size() - 1; k >= 0; --j, --k) {
                coef[j] = norm(coef[j] - q[k] * 1ll * multi);
            }
        }
        while (coef.size() && coef.back() == 0) coef.pop_back();
        // cout << "get " << *this << endl;
    }
    friend ostream& operator << (ostream &o, const Poly &x) {
        o << "[";
        for (int i : x.coef) o << i << ", ";
        o << "]";
        return o;
    }
};

Poly operator * (const Poly &a, const Poly &b) {
    Poly p; p.coef.resize(a.size() + b.size() + 3, 0);
    for (int i = 0; i < a.size(); ++i) for (int j = 0; j < b.size(); ++j) {
        p[i + j] = norm(p[i + j] + 1ll * a[i] * b[j]);
    }
    while (p.size() && p.coef.back() == 0) p.coef.pop_back();
    return p;
}


Poly GetRemain(const Poly &q, int z) {
    if (z == 0) {
        Poly p;
        p.resize(1);
        p[0] = 1;
        return p;
    }
    if (z & 1) {
        Poly rr = GetRemain(q, z >> 1);
        rr = rr * rr;
        rr.Multi(1);
        rr.Divide(q);
        return rr;
    } else {
        Poly rr = GetRemain(q, z >> 1);
        rr = rr * rr;
        rr.Divide(q);
        return rr;
    }
}

vector<int> solve(vector<vector<int>> vv, vector<int> b) {
    int zz = 0;
    // for (vector<int> &v : vv) {
    //     cout << "[";
    //     for (int i : v) cout << i << ", ";
    //     cout << "] = " << b[zz] << endl;
    //     ++zz;
    // }
    stack<pair<int, int>> swaps;
    int n = vv.size();
    for (int i = 0; i < n; ++i) {
        int p = -1;
        for (int j = i; j < n; ++j) {
            if (vv[j][i] == 0) continue;
            if (p == -1) p = j;
        }
        assert(p != -1);
        for (int j = 0; j < n; ++j) swap(vv[p][j], vv[i][j]); 
        swap(b[p], b[i]);
        swaps.emplace(p, i);
        int piv = vv[i][i];
        for (int j = 0; j < n; ++j) vv[i][j] = 1ll * vv[i][j] * inv(piv) % mod;
        b[i] = 1ll * b[i] * inv(piv) % mod;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            int z = vv[j][i] * 1ll * inv(vv[i][i]);
            for (int k = 0; k < n; ++k)
                vv[j][k] = norm(vv[j][k] - 1ll * z * vv[i][k]);
            b[j] = norm(b[j] - 1ll * z * b[i]);
        }
    }
    while (swaps.size()) {
        int a = swaps.top().first, c = swaps.top().second; swaps.pop();
        for (int j = 0; j < n; ++j) swap(vv[a][j], vv[c][j]);
        swap(b[a], b[c]);
    }
    zz = 0;
    // for (vector<int> &v : vv) {
    //     cout << "[";
    //     for (int i : v) cout << i << ", ";
    //     cout << "] = " << b[zz] << endl;
    //     ++zz;
    // }
    return b;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    Poly q;
    q.resize(n + 1);
    q[n] = 1;
    for (int i = n - 1; i >= 0; --i) {
        int t; cin >> t;
        q[i] = norm(-t);
    }
    // for (int i = 0; i <= 10; ++i) {
    //     cout << GetRemain(q, i) << endl;
    // }
    vector<int> bs;
    for (int i = 1; i <= n; ++i) {
        int t; cin >> t;
        bs.push_back(t);
    }
    vector<Poly> pos;
    for (int i = 0; i < n; ++i) {
        int z = bs[i];
        pos.push_back(GetRemain(q, bs.back() - z));
    }
    for (Poly &p : pos) {
        while ((int)p.size() < n) p.coef.push_back(0);
    }
    Poly boss = GetRemain(q, bs.back());
    while ((int)boss.size() < n) boss.coef.push_back(0);
    vector<vector<int>> vv;
    vector<int> b;
    for (int i = 0; i < n; ++i) {
        vector<int> v;
        for (int j = 0; j < n; ++j) {
            v.push_back(pos[j].coef[i]);
        }
        vv.push_back(v);
        b.push_back(boss.coef[i]);
    }
    vector<int> a = solve(vv, b);
    for (int i : a) cout << i << ' ';
    cout << endl;
}
