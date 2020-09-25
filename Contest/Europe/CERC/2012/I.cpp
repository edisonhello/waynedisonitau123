// #pragma GCC optimize("O3")
#include <ext/pb_ds/assoc_container.hpp>
#include <bits/stdc++.h>

using namespace __gnu_pbds;
using namespace std;

struct P {
    double x, y;
    P() : x(0), y(0) {}
    P(double x, double y) : x(x), y(y) {}
    P operator / (double b) { return P(x / b, y / b); }
};

struct L {
    double a, b, c;
    int side(P p) {
        return p.x * a + p.y * b + c >= 0;
    }
    P getp() {
        if (abs(b) > 1e-9)
            return P(0, -c / b);
        return P(-c / a, 0);
    }
};

P Intersect(L x, L y) {
    return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a);
}

bool parallel(L x, L y) {
    return abs((-x.a * y.b + x.b * y.a)) < 1e-12;
}

auto cmp = [&] (const bitset<105> &a, const bitset<105> &b) {
    int i = (a ^ b)._Find_first();
    if (i >= 105) return false;
    return a[i] < b[i];
};

using Bitset = pair<uint64_t, uint64_t>;

namespace std::tr1 {

template <>
struct hash<Bitset> {
    uint64_t operator()(const Bitset &b) const {
        return b.first * 7122 + b.second;
    }
};

}

namespace std {

template <>
struct hash<Bitset> {
    uint64_t operator()(const Bitset &b) const {
        return b.first * 7122 + b.second;
    }
};

}
int rit() {
    int x = 0;
    char c = 0;
     bool flag = 0;
     while (c = getchar(), (c < '0' && c != '-') || c > '9');
     c == '-' ? (flag = true, x = 0) : (x = c & 15);
     while (c = getchar(), c >= '0' && c <= '9') x = x * 10 + (c & 15);
     return flag ? -x : x;
}

// vector<Bitset> faces, rfaces;
unordered_set<Bitset> faces;
// cc_hash_table<Bitset> faces;
vector<L> ls;
vector<P> ps;

void solve() {
    int n, m; 
    n = rit();
    m = rit();
    ls.resize(n);
    ps.resize(m);
    for (int i = 0; i < n; ++i) {
        ls[i].a = rit();
        ls[i].b = rit();
        ls[i].c = rit();
    }
    for (int i = 0; i < m; ++i) {
        ps[i].x = rit();
        ps[i].y = rit();
        // cin >> ps[i].x >> ps[i].y;
    }
    faces.clear();
    // rfaces.clear();

    auto Set = [&](Bitset &bs, int p) {
        if (p < 64) bs.first |= (1ULL << p);
        else bs.second |= (1ULL << (p - 64));
    };

    auto Unset = [&](Bitset &bs, int p) {
        if (p < 64) bs.first &= ~(1ULL << p);
        else bs.second &= ~(1ULL << (p - 64));
    };

    auto Get = [&] (P p) {
        Bitset bs;
        for (int i = 0; i < n; ++i) {
            if (ls[i].side(p)) Set(bs, i);
        }
        return bs;
    };

    for (int i = 0; i < n && faces.size() <= m; ++i) {
        for (int j = i + 1; j < n && faces.size() <= m; ++j) {
            if (parallel(ls[i], ls[j])) continue;

            P p = Intersect(ls[i], ls[j]);
            auto bs = Get(p);
            if (faces.find(bs) == faces.end()) {
                Unset(bs, i);
                Unset(bs, j);
                // faces.push_back(bs);
                faces.insert(bs);
                Set(bs, j);
                // faces.push_back(bs);
                faces.insert(bs);
                Set(bs, i);
                // faces.push_back(bs);
                faces.insert(bs);
                Unset(bs, j);
                // faces.push_back(bs);
                faces.insert(bs);
            }
        }

        P p = ls[i].getp();
        // cerr << "getp " << p.x << ' ' << p.y << endl;
        auto bs = Get(p);
        Unset(bs, i);
        if (!faces.count(bs)) {
            // faces.push_back(bs);
            faces.insert(bs);
            Set(bs, i);
            // faces.push_back(bs);
            faces.insert(bs);
        }
    }
    // sort(faces.begin(), faces.end());
    // faces.resize(unique(faces.begin(), faces.end()) - faces.begin());

    // cerr << "f size " << faces.size() << endl;

    // cerr << "faces" << endl;
    // for (auto b : faces) {
    //     cerr << b << endl;
    // }

    if (faces.size() > m) {
        cout << "VULNERABLE\n";
        return;
    }

    // vector<Bitset> rfaces;
    for (int i = 0; i < m && !faces.empty(); ++i) {
        auto bs = Get(ps[i]);
        // cerr << "pt " << ps[i].x << ' ' << ps[i].y << endl;
        // cerr << "get bs = " << bs << endl;
        // rfaces.push_back(bs);
        faces.erase(bs);
    }
    // sort(rfaces.begin(), rfaces.end());
    // rfaces.resize(unique(rfaces.begin(), rfaces.end()) - rfaces.begin());

    printf("%s\n", (faces.empty() ? "PROTECTED" : "VULNERABLE"));
}

int main() {
    // ios_base::sync_with_stdio(0); cin.tie(0);
    int t; t = rit(); while (t--) solve();
}

