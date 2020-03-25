#include <bits/stdc++.h>
using namespace std;

struct P {
    int x, y;
    P() : x(0), y(0) {}
    P(int x, int y) : x(x), y(y) {}
};


P operator - (const P &a, const P &b) { return P(a.x - b.x, a.y - b.y); }
long long operator ^ (const P &a, const P &b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; };

int main() {
    int n;
    long long s; 
    cin >> n >> s;
    s *= 2;

    vector<P> ps(n);
    for (int i = 0; i < n; ++i) cin >> ps[i].x >> ps[i].y;
    sort(ps.begin(), ps.end(), [] (const P &a, const P &b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });

    vector<long long> pre(n), suf(n);
    vector<P> utb, dtb;

    long long nowc = 0;
    for (int i = 0; i < n; ++i) {
        // cerr << "Add point i = " << i << " = " << ps[i].x << ' ' << ps[i].y << endl;

        while (utb.size() >= 2u && ((ps[i] - utb[utb.size() - 1]) ^ (utb[utb.size() - 2] - utb[utb.size() - 1])) >= 0) {
            nowc -= utb[utb.size() - 1] ^ utb[utb.size() - 2];
            utb.pop_back();
        }
        utb.push_back(ps[i]);
        if (utb.size() > 1u) nowc += utb[utb.size() - 1] ^ utb[utb.size() - 2];

        while (dtb.size() >= 2u && ((ps[i] - dtb[dtb.size() - 1]) ^ (dtb[dtb.size() - 2] - dtb[dtb.size() - 1])) <= 0) {
            nowc -= dtb[dtb.size() - 2] ^ dtb[dtb.size() - 1];
            dtb.pop_back();
        }
        dtb.push_back(ps[i]);
        if (dtb.size() > 1u) nowc += dtb[dtb.size() - 2] ^ dtb[dtb.size() - 1];

        pre[i] = nowc + (dtb.back() ^ utb.back());

        // cerr << "pre[" << i << "] = " << pre[i] << endl;
    }

    nowc = 0;
    utb.clear(); dtb.clear();
    for (int i = n - 1; i >= 0; --i) {
        // cerr << "Add point i = " << i << " = " << ps[i].x << ' ' << ps[i].y << endl;

        while (utb.size() >= 2u && ((ps[i] - utb[utb.size() - 1]) ^ (utb[utb.size() - 2] - utb[utb.size() - 1])) <= 0) {
            nowc -= utb[utb.size() - 2] ^ utb[utb.size() - 1];
            utb.pop_back();
        }
        utb.push_back(ps[i]);
        if (utb.size() > 1u) nowc += utb[utb.size() - 2] ^ utb[utb.size() - 1];

        while (dtb.size() >= 2u && ((ps[i] - dtb[dtb.size() - 1]) ^ (dtb[dtb.size() - 2] - dtb[dtb.size() - 1])) >= 0) {
            nowc -= dtb[dtb.size() - 1] ^ dtb[dtb.size() - 2];
            dtb.pop_back();
        }
        dtb.push_back(ps[i]);
        if (dtb.size() > 1u) nowc += dtb[dtb.size() - 1] ^ dtb[dtb.size() - 2];

        suf[i] = nowc + (utb.back() ^ dtb.back());

        // cerr << "suf[" << i << "] = " << suf[i] << endl;
    }

    long long ans = -1;

    auto Update = [&] (long long l, long long r) {
        long long d = abs(r - l);
        if (ans == -1) ans = d;
        else {
            if (abs(ans - s) > abs(d - s)) {
                ans = d;
            } else if (abs(ans - s) == abs(d - s)) {
                if (d < ans) ans = d;
            }
        }
    };

    Update(0, suf[0]);
    Update(pre[n - 1], 0);

    for (int i = 0; i < n - 1; ++i) {
        if (ps[i].x != ps[i + 1].x) Update(pre[i], suf[i + 1]);
    }

    if (ans & 1) cout << ans / 2 << ".5000" << endl;
    else cout << ans / 2 << ".0000" << endl;
}

