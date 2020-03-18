#include <bits/stdc++.h>
using namespace std;

struct Circle {
    int x, y, r, u, i;
    Circle(int x, int y, int r, int u, int i) : x(x), y(y), r(r), u(u), i(i) {}
};

int nx;
double CalcY(const Circle &c) {
    int x_ = nx - c.x;
    double yd = sqrt((double)c.r * c.r - (double)x_ * x_);
    if (c.u) return c.y + yd;
    else return c.y - yd;
}

struct Treap {
    Treap *l, *r;
    Circle val;
    int pri, mx, v, sz, sum;
    Treap(int x, int y, int r, int u, int i) : 
        l(0), r(0), val(x, y, r, u, i), pri(rand()), 
        mx(u == 1 ? 1 : -1), v(u == 1 ? 1 : -1), sz(1), sum(u == 1 ? 1 : -1) {}
    int lz() { return l ? l->sz : 0; }
    int rz() { return r ? r->sz : 0; }
    void pull() {
        sz = lz() + rz() + 1;
        sum = (l ? l->sum : 0) + (r ? r->sum : 0) + v;
        mx = v + (l ? l->sum : 0);
        if (l) mx = max(mx, l->mx);
        if (r) mx = max(mx, (l ? l->sum : 0) + v + r->mx);
        // Mx = max(sum, max(l ? l->mx : INT_MIN, r ? r->mx : INT_MIN));
        // Mn = min(sum, min(l ? l->mn : INT_MAX, r ? r->mn : INT_MAX));
    }
};

vector<vector<int>> BuildTree(const vector<tuple<int, int, int>> &circle) {
    function<Treap*(Treap*, Treap*)> Merge = [&] (Treap *a, Treap *b) {
        if (!a) return b; if (!b) return a;
        if (a->pri > b->pri) {
            a->r = Merge(a->r, b);
            a->pull();
            return a;
        } else {
            b->l = Merge(a, b->l);
            b->pull();
            return b;
        }
    };

    function<void(Treap*, int, Treap*&, Treap*&)> SplitByVal = [&] (Treap *now, int val, Treap *&a, Treap *&b) {
        if (!now) { a = b = 0; return; }
        if (CalcY(now->val) <= val) {
            a = now;
            SplitByVal(now->r, val, a->r, b);
            a->pull();
        } else {
            b = now;
            SplitByVal(now->l, val, a, b->l);
            b->pull();
        }
    };

    function<void(Treap*, int, Treap*&, Treap*&)> SplitBySz = [&] (Treap *now, int sz, Treap *&a, Treap *&b) {
        if (!now) { a = b = 0; return; }
        if (now->lz() >= sz) {
            b = now;
            SplitBySz(now->l, sz, a, b->l);
            b->pull();
        } else {
            a = now;
            SplitBySz(now->r, sz - 1 - now->lz(), a->r, b);
            a->pull();
        }
    };

    function<void(Treap *)> Delete = [&] (Treap *now) {
        if (!now) return;
        Delete(now->l);
        Delete(now->r);
        delete now;
    };

    function<Treap*(Treap *, int pre)> GetLeftestPos = [&] (Treap *now, int pre) -> Treap* {
        if (!now) return 0;
        if (now->l && now->l->mx + pre > 0) return GetLeftestPos(now->l, pre);
        if ((now->l ? now->l->sum : 0) + now->v + pre > 0) return now;
        return GetLeftestPos(now->r, pre + now->v + (now->l ? now->l->sum : 0));
    };

    function<void(Treap *)> PrintTreap = [&] (Treap *now) {
        if (now->l) cerr << "(", PrintTreap(now->l), cerr << ")";
        cerr << "[sum=" << now->sum << "," << now->v << ",mx=" << now->mx << ",i=" << now->val.i << "]";
        if (now->r) cerr << "(", PrintTreap(now->r), cerr << ")";
    };

    vector<pair<int, int>> evs;
    for (int i = 0; i < (int)circle.size(); ++i) {
        int x, y, r; tie(x, y, r) = circle[i];
        evs.emplace_back(x - r, i + 1);
        evs.emplace_back(x + r, -(i + 1));
    }

    vector<vector<int>> g(circle.size());

    sort(evs.begin(), evs.end());
    Treap *root = 0;

    for (auto &pp : evs) {
        int ii; tie(nx, ii) = pp;

        // cerr << "event: ";
        // cerr << nx << ' ' << ii << endl;

        if (ii > 0) {
            --ii;
            // cerr << "real ii = " << ii << endl;
            Treap *a, *b;
            // cerr << "a " << endl;
            SplitByVal(root, get<1>(circle[ii]), a, b);
            // cerr << "b " << endl;
            // if (b) PrintTreap(b);
            auto it = GetLeftestPos(b, 0);
            // cerr << "c " << endl;
            if (it) {
                g[it->val.i].push_back(ii);
                // cerr << "parent: " << it->val.i << endl;
            }

            Treap *na = new Treap(get<0>(circle[ii]), get<1>(circle[ii]), get<2>(circle[ii]), 1, ii);
            Treap *nb = new Treap(get<0>(circle[ii]), get<1>(circle[ii]), get<2>(circle[ii]), 0, ii);

            root = Merge(Merge(Merge(a, nb), na), b);
            // cerr << "d " << endl;
            // PrintTreap(root);
        } else {
            ii = -ii - 1;
            // cerr << "real ii = " << ii << endl;

            Treap *a, *b, *c, *d;
            // cerr << "e" << endl;
            SplitByVal(root, get<1>(circle[ii]), a, d);
            // cerr << "f" << endl;
            assert(a && a->sz >= 2);
            SplitBySz(a, a->sz - 2, b, c);
            // cerr << "g" << endl;

            Delete(c);
            // cerr << "gg" << endl;

            root = Merge(b, d);
            // cerr << "h" << endl;
        }
    }

    // for (int i = 0; i < (int)g.size(); ++i) {
    //     cerr << i << " : ";
    //     for (int j : g[i]) cerr << j << ' ';
    //     cerr << endl;
    // }

    return g;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> cr;
    for (int i = 0; i < n + m; ++i) {
        int x, y, r;
        cin >> x >> y >> r;
        cr.emplace_back(x, y, r);
    }
    cr.emplace_back(0, 0, 100000000 + 5);
    auto g = BuildTree(cr);
    int root = n + m;

    vector<vector<int>> dp(n + m + 1, vector<int>(3));
    constexpr int kInf = 1'000'000'000;

    function<void(int)> Dfs = [&](int x) {
        dp[x][0] = dp[x][1] = 0;
        int sum1 = 0;
        int sum2 = 0;
        for (int u : g[x]) {
            Dfs(u);
            sum1 += max(dp[u][0], dp[u][1]);
            sum2 += dp[u][0];
        }
        if (x < n) {
            dp[x][0] = sum1;
            dp[x][1] = sum2 + 1;
        } else {
            dp[x][0] = sum2;
            dp[x][1] = sum1;
        }
        // cout << "dp[" << x << "][0] = " << dp[x][0] << endl;
        // cout << "dp[" << x << "][1] = " << dp[x][1] << endl;
    };

    Dfs(root);
    for (int i = 0; i < m; ++i) {
        int res = max(dp[i + n][1], dp[i + n][0] + 1);
        cout << res << "\n";
    }
}
