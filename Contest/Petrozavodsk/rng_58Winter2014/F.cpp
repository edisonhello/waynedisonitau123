#include <bits/stdc++.h>
using namespace std;

struct P {
    int x, y, v;
    long double o;
    void init() {
        int g = __gcd(x, y);
        g = abs(g);
        x /= g;
        y /= g;
        o = atan2((long double)y, (long double)x);
    }

    long long operator^ (P b) {
        return 1ll * x * b.y - 1ll * y * b.x;
    }
};

long long Solve(vector<P> ps) {
    // cerr << "solve: ";
    // for (int i = 0; i < (int)ps.size(); ++i) { cerr << "(" << ps[i].x << ' ' << ps[i].y << " = " << ps[i].v << ") "; }
    // cerr << endl;
    int n = ps.size();
    int op = 0;
    for (; op < n - 1 && (ps[0] ^ ps[op + 1]) >= 0; ++op);

    // cerr << "op = " << op << endl;

    long long ans = 1e14;
    long long mn = 1e14;
    for (int i = 1, j = op; i <= op; ++i) {
        if (ps[0].x == -ps[i].x && ps[0].y == -ps[i].y) break;
        while (j < n - 1 && (ps[i] ^ ps[j + 1]) > 0) {
            ++j;
            mn = min(mn, (long long)ps[j].v);
        }
        // cerr << "i = " << i << ' ' << "j = " << j << " mn = " << mn << endl;
        ans = min(ans, mn + ps[0].v + 0ll + ps[i].v);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<P> ps;
    for (int i = 0; i < n; ++i) {
        int x, y, v; cin >> x >> y >> v;
        if (x == 0 && y == 0) continue;

        P p{x, y, v, (double)0};
        p.init();
        ps.push_back(p);
    }
    sort(ps.begin(), ps.end(), [&] (const P &a, const P &b) { return a.x == b.x ? a.y < b.y : a.x < b.x; });

    if (ps.size() < 2) {
        cout << "-1\n";
        return 0;
    }

    vector<P> tmpps;
    for (int i = 0, j; i < (int)ps.size(); i = j) {
        for (j = i; j < n && ps[i].x == ps[j].x && ps[i].y == ps[j].y; ++j);
        int mn = INT_MAX;
        for (int k = i; k < j; ++k) mn = min(mn, ps[k].v);
        ps[i].v = mn;
        tmpps.push_back(ps[i]);
    }
    tmpps.swap(ps);

    sort(ps.begin(), ps.end(), [&] (const P &a, const P &b) { return a.o < b.o; });

    // cerr << "done 1 " << endl;

    auto minp = min_element(ps.begin(), ps.end(), [&] (const P &a, const P &b) { return a.v < b.v; });
    
    vector<P> ps2;
    for (int i = minp - ps.begin(); i < (int)ps.size(); ++i) ps2.push_back(ps[i]);
    for (int i = 0; i < minp - ps.begin(); ++i) ps2.push_back(ps[i]);

    long long ans = Solve(ps2);

    // cerr << "done 2 " << endl;

    int opp = -1;
    for (int i = 0; i < (int)ps.size(); ++i) {
        if (ps[i].x == -minp->x && ps[i].y == -minp->y) opp = i;
    }

    if (opp != -1) {
        vector<P> ps3;

        for (int i = opp; i < (int)ps.size(); ++i) ps3.push_back(ps[i]);
        for (int i = 0; i < opp; ++i) ps3.push_back(ps[i]);

        ans = min(ans, Solve(ps3));
    }

    // cerr << "done 3 " << endl;

    map<pair<int, int>, vector<int>> mp;
    for (int i = 0; i < (int)ps.size(); ++i) {
        mp[minmax(abs(ps[i].x), abs(ps[i].y))].push_back(i);
    }

    for (auto &p : mp) {
        if (p.second.size() == 4u) {
            long long v = 0;
            for (auto i : p.second) v += ps[i].v;
            ans = min(ans, v);
        }
    }

    if (ans >= 1e13) ans = -1;

    cout << ans << endl;
}

