#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int kN = 1000 + 5;
const int kM = 1e5 + 5;
const int kInf = 2e9 + 5;
int st[kM], ed[kM], cost[kM], cnt[kM], mst[kM][kN];
short sz[kM];
pair<int, int> qr[kM];

struct DisjointSet {
    int uf[kN], sz[kN];
    vector<pair<int *, int>> rec;
    vector<int> hist, mst, mh;

    void Init(int n) {
        for (int i = 0; i < n; ++i) {
            sz[i] = 1;
            uf[i] = i;
        }
        rec.clear();
        hist.clear();
        mst.clear();
    }

    int Find(int x) {
        if (x == uf[x]) return x;
        return Find(uf[x]);
    }

    void Save() { 
        hist.push_back(rec.size()); 
        mh.push_back(mst.size());
    }

    void Undo() {
        int lst = hist.back();
        hist.pop_back();
        while (rec.size() > lst) {
            *rec.back().first = rec.back().second;
            rec.pop_back();
        }
        lst = mh.back();
        mh.pop_back();
        while (mst.size() > lst) mst.pop_back();
    }

    void Assign(int *p, int v) {
        rec.emplace_back(p, *p);
        *p = v;
    }

    void Merge(int x, int y, int w) {
        x = Find(x), y = Find(y);
        if (x == y) return;
        if (sz[x] > sz[y]) swap(x, y);
        Assign(&uf[x], y);
        Assign(&sz[y], sz[x] + sz[y]);
        if (w < kInf) mst.push_back(w);
    }
} djs;

void Contract(int l, int r, vector<int> v, vector<int> &x, vector<int> &y) {
    sort(v.begin(), v.end(), [&](int i, int j) {
        if (cost[i] == cost[j]) return i < j;
        return cost[i] < cost[j];
    });
    djs.Save();
    for (int i = l; i <= r; ++i) djs.Merge(st[qr[i].first], ed[qr[i].first], cost[qr[i].first]);
    for (int i = 0; i < v.size(); ++i) {
        if (djs.Find(st[v[i]]) != djs.Find(ed[v[i]])) {
            x.push_back(v[i]);
            djs.Merge(st[v[i]], ed[v[i]], cost[v[i]]);
        }
    }
    djs.Undo();
    djs.Save();
    for (int i = 0; i < x.size(); ++i) djs.Merge(st[x[i]], ed[x[i]], cost[x[i]]);
    for (int i = 0; i < v.size(); ++i) {
        if (djs.Find(st[v[i]]) != djs.Find(ed[v[i]])) {
            y.push_back(v[i]);
            djs.Merge(st[v[i]], ed[v[i]], cost[v[i]]);
        }
    }
    djs.Undo();
}

void Solve(int l, int r, vector<int> v, long long c) {
    if (l == r) {
        cost[qr[l].first] = qr[l].second;
        for (int i = 0; i < djs.mst.size(); ++i) mst[l][i] = djs.mst[i];
        sz[l] = djs.mst.size();
        int minv = qr[l].second;
        for (int i = 0; i < v.size(); ++i) minv = min(minv, cost[v[i]]);
        if (minv < kInf) {
            mst[l][sz[l]++] = minv;
        }
        return;
    }
    int m = (l + r) >> 1;
    vector<int> lv = v, rv = v;
    vector<int> x, y;
    for (int i = m + 1; i <= r; ++i) {
        cnt[qr[i].first]--;
        if (cnt[qr[i].first] == 0) lv.push_back(qr[i].first);
    }
    Contract(l, m, lv, x, y);
    long long lc = c, rc = c;
    djs.Save();
    for (int i = 0; i < x.size(); ++i) {
        lc += cost[x[i]];
        djs.Merge(st[x[i]], ed[x[i]], cost[x[i]]);
    }
    Solve(l, m, y, lc);
    djs.Undo();
    x.clear(), y.clear();
    for (int i = m + 1; i <= r; ++i) ++cnt[qr[i].first];
    for (int i = l; i <= m; ++i) {
        cnt[qr[i].first]--;
        if (cnt[qr[i].first] == 0) rv.push_back(qr[i].first);
    }
    Contract(m + 1, r, rv, x, y);
    djs.Save();
    for (int i = 0; i < x.size(); ++i) {
        rc += cost[x[i]];
        djs.Merge(st[x[i]], ed[x[i]], cost[x[i]]);
    }
    Solve(m + 1, r, y, rc);
    djs.Undo();
    for (int i = l; i <= m; ++i) ++cnt[qr[i].first];
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, m; scanf("%d%d", &n, &m);
        djs.Init(n);
        vector<int> wd;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &st[i], &ed[i], &cost[i]);
            --st[i], --ed[i];
            wd.push_back(cost[i]);
        }
        sort(wd.begin(), wd.end());
        vector<int> od(m);
        iota(od.begin(), od.end(), 0);
        sort(od.begin(), od.end(), [&](int i, int j) {
            return cost[i] < cost[j];
        });
        for (int i = 0; i < m; ++i) cnt[i] = 0;
        qr[0].first = od[0];
        qr[0].second = cost[od[0]];
        ++cnt[od[0]];
        for (int i = 0; i < m; ++i) {
            qr[i + 1].first = od[i];
            qr[i + 1].second = kInf;
            ++cnt[od[i]];
        }
        vector<int> v;
        for (int i = 0; i < m; ++i) if (cnt[i] == 0) v.push_back(i);
        Solve(0, m, v, 0);
        for (int i = 0; i <= m; ++i) sort(mst[i], mst[i] + sz[i]);
        for (int i = 0; i <= m; ++i) {
            // printf("cost = %lld ", ans[i]);
            for (int j = 1; j < sz[i]; ++j) mst[i][j] += mst[i][j - 1];
        }
        int q; scanf("%d", &q);
        int last = 0;
        while (q--) {
            int l, h;
            scanf("%d%d", &l, &h);
            l -= last, h -= last;
            // printf("l = %d h = %d\n", l, h);
            int v = lower_bound(wd.begin(), wd.end(), l) - wd.begin();
            // printf("v = %d\n", v);
            int g = -1;
            for (int d = 10; d >= 0; --d) {
                if (g + (1 << d) < sz[v]) {
                    int gd = g + (1 << d);
                    int vv = mst[v][gd] - (gd == 0 ? 0 : mst[v][gd - 1]);
                    if (vv <= h) g = gd;
                }
            }
            printf("%d\n", last = (g == -1 ? 0 : mst[v][g]));
        }
    }
    return 0;
}
