#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int p[maxn], s[maxn], c[maxn], l[maxn], r[maxn], k[maxn];
int ql[maxn], qr[maxn];

namespace segtree {
    int st[maxn * 4], tg[maxn * 4];
    void push(int o) {
        if (tg[o] == 0) return;
        st[o * 2 + 1] += tg[o], tg[o * 2 + 1] += tg[o];
        st[o * 2 + 2] += tg[o], tg[o * 2 + 2] += tg[o];
        tg[o] = 0;
    }
    void build(int l, int r, vector<tuple<int, int, int>> &seg, int o = 0) {
        if (r - l == 1) return st[o] = get<2>(seg[l]), void();
        build(l, (l + r) >> 1, seg, o * 2 + 1);
        build((l + r) >> 1, r, seg, o * 2 + 2);
        st[o] = min(st[o * 2 + 1], st[o * 2 + 2]);
    }
    void modify(int l, int r, int ql, int qr, int v, int o = 0) {
        if (r - l > 1) push(o);
        if (l >= qr || ql >= r) return;
        if (l >= ql && r <= qr) {
            st[o] += v;
            tg[o] += v;
            return;
        }
        modify(l, (l + r) >> 1, ql, qr, v, o * 2 + 1);
        modify((l + r) >> 1, r, ql, qr, v, o * 2 + 2);
        st[o] = min(st[o * 2 + 1], st[o * 2 + 2]);
    }
    int query(int l, int r, int ql, int qr, int o = 0) {
        if (r - l > 1) push(o);
        if (l >= qr || ql >= r) return 1e9;
        if (l >= ql && r <= qr) return st[o];
        return min(query(l, (l + r) >> 1, ql, qr, o * 2 + 1),
                   query((l + r) >> 1, r, ql, qr, o * 2 + 2));
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
        s[i] = p[i];
        if (p[i]) c[i] = 1;
    }
    if (m == 0) {
        for (int i = 0; i < n; ++i) {
            if (p[i] == 0) p[i] = -1;
            printf("%d ", p[i]);
        }
        puts("");
        return 0;
    }
    for (int i = 1; i < n; ++i) s[i] += s[i - 1], c[i] += c[i - 1];
    vector<tuple<int, int, int>> seg;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &l[i], &r[i], &k[i]);
        --l[i], --r[i];
        int emp = r[i] - l[i] + 1 - (c[r[i]] - (l[i] ? c[l[i] - 1] : 0));
        int sum = k[i] - (s[r[i]] - (l[i] ? s[l[i] - 1] : 0));
        int need = max(0, (emp + sum + 1) >> 1);
        int diff = emp - need;
        seg.emplace_back(l[i], r[i], diff);
    }
    sort(seg.begin(), seg.end());
    // for (int i = 0; i < m; ++i) printf("%d %d %d\n", get<0>(seg[i]), get<1>(seg[i]), get<2>(seg[i]));
    segtree::build(0, m, seg);
    memset(ql, -1, sizeof(ql));
    memset(qr, -1, sizeof(qr));
    for (int i = 0; i < m; ) {
        int j = i;
        while (j < m && get<0>(seg[j]) == get<0>(seg[i])) ++j;
        ql[get<0>(seg[i])] = i;
        qr[get<0>(seg[i])] = j;
        i = j;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    set<int> ind;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j < m && get<0>(seg[j]) <= i) {
            pq.emplace(get<1>(seg[j]), j);
            ind.insert(j);
            ++j;
        }
        while (pq.size() && pq.top().first < i) {
            segtree::modify(0, m, pq.top().second, pq.top().second + 1, 1e9);
            ind.erase(pq.top().second);
            pq.pop();
        }
        int ql = ind.size() ? *ind.begin() : -1, qr = ind.size() ? *ind.rbegin() + 1 : -1;
        int minv = ql == -1 ? 1e9 : segtree::query(0, m, ql, qr); 
        if (minv < 0) {
            puts("Impossible");
            return 0;
        }
        if (p[i] != 0) continue;
        if (minv > 1e8) {
            p[i] = -1;
            continue;
        }
        // printf("i = %d ql = %d qr = %d\n", i, ql[i], qr[i]);
        if (minv == 0) {
            p[i] = 1;
            continue;
        }
        p[i] = -1;
        segtree::modify(0, m, ql, qr, -1);
    }
    for (int i = 0; i < n; ++i) printf("%d ", p[i]);
    puts("");
    return 0;
}
