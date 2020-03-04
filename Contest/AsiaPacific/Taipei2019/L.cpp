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
            int op = 2, r = 3, l = 1;
            for (int i = 0; i < (int)tb.size(); ++i) {
                int ll = l, rr = r;
                auto calc1 = [&] (int op) -> long long {
                    ll = l, rr = r;
                    auto calc_ans = [&] (int i, int j, int k) {
                        if (i == j || j == k || i == k) return -1LL;
                        return abs((tb[i] ^ tb[j]) + (tb[j] ^ tb[k]) + (tb[k] ^ tb[i]));
                    };
                    while (true) {
                        int tr = (rr == (int)tb.size() - 1 ? 0 : rr + 1);
                        if (calc_ans(i, op, tr) > calc_ans(i, op, rr)) rr = tr;
                        else break;
                    }
                    while (true) {
                        int tl = (ll == (int)tb.size() - 1 ? 0 : ll + 1);
                        if (calc_ans(i, op, tl) > calc_ans(i, op, ll)) ll = tl;
                        else break;
                    }
                    return calc_ans(i, op, ll) + calc_ans(i, op, rr);
                };
                while (true) {
                    int top = (op == (int)tb.size() - 1 ? 0 : op + 1);
                    if (calc1(top) > calc1(op)) {
                        op = top;
                        ans = max(ans, calc1(op));
                        l = ll, r = rr;
                    }
                    else break;
                }
            }
        }

        if (ans % 2 == 0) cout << ans / 2 << endl;
        else cout << ans / 2 << ".5" << endl;
    }
}
