#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int s[maxn];
vector<int> pos[maxn];

namespace segtree {
    int st[maxn * 4];
    void init() {
        for (int i = 0; i < maxn * 4; ++i)
            st[i] = -1;
    }
    void modify(int l, int r, int p, int v, int o = 0) {
        if (r - l == 1) return st[o] = max(st[o], v), void();
        if (p < (l + r) >> 1) modify(l, (l + r) >> 1, p, v, o * 2 + 1);
        else modify((l + r) >> 1, r, p, v, o * 2 + 2);
        st[o] = max(st[o * 2 + 1], st[o * 2 + 2]);
    }
    int query(int l, int r, int ql, int qr, int o = 0) {
        if (l >= qr || ql >= r) return -1;
        if (l >= ql && r <= qr) return st[o];
        return max(query(l, (l + r) >> 1, ql, qr, o * 2 + 1),
                   query((l + r) >> 1, r, ql, qr, o * 2 + 2));
    }
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &s[i]);
        pos[s[i]].push_back(i);
    }
    int a = n + 1;
    segtree::init();
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j + 1 < (int)pos[i].size(); ++j) {
            int x = segtree::query(0, n, pos[i][j], pos[i][j + 1] + 1);
            if (x > pos[i][j + 1]) {
                a = min(a, i);
                break;
            }
        }
        if (pos[i].size() < 2) continue;
        int last = pos[i].back();
        for (int j = 0; j + 1 < (int)pos[i].size(); ++j) {
            segtree::modify(0, n, pos[i][j], last + 1);
        }
    }
    segtree::init();
    for (int i = n; i >= 1; --i) {
        for (int j = 0; j + 1 < (int)pos[i].size(); ++j) {
            int x = segtree::query(0, n, pos[i][j], pos[i][j + 1] + 1);
            if (x > pos[i][j + 1]) {
                a = min(a, i);
                break;
            }
        }
        if (pos[i].size() < 2) continue;
        int last = pos[i].back();
        for (int j = 0; j + 1 < (int)pos[i].size(); ++j) {
            segtree::modify(0, n, pos[i][j], last + 1);
        }
    }
    if (a == n + 1) {
        puts("-1");
        return 0;
    }
    for (int b = 1; b <= n; ++b) {
        if (pos[b].size() < 2) continue;
        if (a == b) continue;
        int alast = pos[a].back(), afirst = pos[a].front(), blast = pos[b].back();
        for (int i = 0; i < (int)pos[b].size(); ++i) {
            if (pos[b][i] > afirst && pos[b][i] < alast && blast > alast) {
                printf("%d %d\n", a, b);
                return 0;
            }
        }
    }
    assert(false);
}
