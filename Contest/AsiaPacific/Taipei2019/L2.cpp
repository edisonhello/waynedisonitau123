#include <bits/stdc++.h>
using namespace std;

#define crx(a, b, c) ((b - a) ^ (c - a))

bool same(long long x, long long y) {
    return x == y;
}

struct P {
    long long x, y;
    P operator - (P b) { return P{x - b.x, y - b.y}; }
    long long operator ^ (P b) { return x * b.y - y * b.x; }
    long long operator != (const P &b) { return x != b.x || y != b.y; }
    long long operator == (const P &b) { return x == b.x && y == b.y; }
};

ostream& operator << (ostream &o, P p) {
    o << "(" << p.x << ", " << p.y << ")";
    return o;
}

vector<P> convex(vector<P> ps) {
    vector<P> p;
    sort(ps.begin(), ps.end(), [&] (const P &a, const P &b) { return same(a.x, b.x) ? a.y < b.y : a.x < b.x; });
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
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--){
        int n; cin >> n; 
        vector<P> ps(n);
        for (int i = 0; i < n; ++i) cin >> ps[i].x >> ps[i].y;
        vector<P> tb = convex(ps);

        // cerr << "tb: ";
        // for (int i = 0; i < (int)tb.size(); ++i) cerr << tb[i] << ' ';
        // cerr << endl;

        long long ans = 0;
        if (tb.size() < 3u) {
            ;
        } else if (tb.size() == 3u) {
            long long base = abs((tb[0] ^ tb[1]) + (tb[1] ^ tb[2]) + (tb[2] ^ tb[0]));
            vector<bool> no(n, false);
            for (int i = 0; i < n; ++i) if (ps[i] == tb[0]) { no[i] = true; break; }
            for (int i = 0; i < n; ++i) if (ps[i] == tb[1]) { no[i] = true; break; }
            for (int i = 0; i < n; ++i) if (ps[i] == tb[2]) { no[i] = true; break; }

            for (int i = 0; i < n; ++i) if (!no[i]) {
                long long c1 = abs((tb[0] ^ tb[1]) + (tb[1] ^ ps[i]) + (ps[i] ^ tb[0]));
                long long c2 = abs((tb[0] ^ tb[2]) + (tb[2] ^ ps[i]) + (ps[i] ^ tb[0]));
                long long c3 = abs((tb[2] ^ tb[1]) + (tb[1] ^ ps[i]) + (ps[i] ^ tb[2]));
                ans = max(ans, base - min(c1, min(c2, c3)));
            }
        } else {
            for (int i = 0; i < (int)tb.size(); ++i) {
                int l = (i + 1) % tb.size();
                int r = (i + 3) % tb.size();
                for (int op = (i + 2) % tb.size(); (op + 1) % tb.size() != i; op = (op == (int)tb.size() - 1 ? 0 : op + 1)) {
                    auto calc_3 = [&] (int i, int j, int k) {
                        if (i == j || j == k || i == k) return -1000LL;
                        return abs((tb[i] ^ tb[j]) + (tb[j] ^ tb[k]) + (tb[k] ^ tb[i]));
                    };
                    while (true) {
                        int tl = (l == (int)tb.size() - 1 ? 0 : l + 1);
                        // cerr << "l = " << l << ", tl = " << tl << endl;
                        // cerr << "tl calc3 = " << calc_3(i, op, tl) << " orig = " << calc_3(i, op, l) << endl;
                        if (calc_3(i, op, tl) > calc_3(i, op, l)) l = tl;
                        else break;
                    }
                    while (true) {
                        int tr = (r == (int)tb.size() - 1 ? 0 : r + 1);
                        if (calc_3(i, op, tr) > calc_3(i, op, r)) r = tr;
                        else break;
                    }
                    // cerr << "i op l r " << i << " " << op << ' ' << l << ' ' << r << " ans = " << calc_3(i, op, l) + calc_3(i, op, r) << endl;
                    ans = max(ans, calc_3(i, op, l) + calc_3(i, op, r));
                }
            }
        }

        if (ans % 2 == 0) cout << ans / 2 << endl;
        else cout << ans / 2 << ".5" << endl;
    }
}
