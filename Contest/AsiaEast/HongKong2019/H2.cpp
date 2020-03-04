#include <bits/stdc++.h>
using namespace std;

const int kN = 500'000 + 5;
const int kM = 1'000'000 + 5;
const int kInf = 1'000'000'000 + 123;

struct Operation {
    int t, h, x, y, z;
    bool operator<(const Operation &rhs) const { return h < rhs.h; }
} op[kM];

int n, m, nd[kN * 4], ans[kM];

void Modify(int l, int r, int p, int v, int o = 0) {
    if (r - l == 1) {
        nd[o] = v;
        return;
    }
    int m = (l + r) >> 1;
    if (p < m) Modify(l, m, p, v, o * 2 + 1);
    else Modify(m, r, p, v, o * 2 + 2);
    nd[o] = max(nd[o * 2 + 1], nd[o * 2 + 2]);
}

int Query(int l, int r, int ql, int qr, int o = 0) {
    if (l >= qr || ql >= r) return -kInf;
    if (l >= ql && r <= qr) return nd[o];
    int m = (l + r) >> 1;
    return max(Query(l, m, ql, qr, o * 2 + 1), Query(m, r, ql, qr, o * 2 + 2));
}

int u[kM], ptr;

void Solve(int l, int r) {
    if (r - l == 1) return;
    int m = (l + r) >> 1;
    Solve(l, m), Solve(m, r);
    for (int i = m, j = l; i < r; ++i) {
        if (op[i].t == 0) continue;
        while (j < m) {
            if (op[j].t == 1) ++j;
            else if (op[j].h <= op[i].h) {
                Modify(0, n, op[j].x, op[j].h);
                u[ptr++] = op[j].x;
                ++j;
            }
            else break;
        }
        int g = Query(0, n, op[i].x, op[i].y);
        // printf("case1 query = %d res = %d\n", op[i].h, g);
        if (g != -kInf) ans[op[i].z] = min(ans[op[i].z], op[i].h - g);
    }
    for (int i = 0; i < ptr; ++i) Modify(0, n, u[i], -kInf);
    ptr = 0;
    for (int i = r - 1, j = m - 1; i >= m; --i) {
        if (op[i].t == 0) continue;
        while (j >= l) {
            if (op[j].t == 1) --j;
            else if (op[j].h >= op[i].h) {
                Modify(0, n, op[j].x, -op[j].h);
                u[ptr++] = op[j].x;
                --j;
            }
            else break;
        }
        int g = Query(0, n, op[i].x, op[i].y);
        // printf("case2 query = %d res = %d\n", op[i].h, g);
        if (g != -kInf) ans[op[i].z] = min(ans[op[i].z], -g - op[i].h);
    }
    for (int i = 0; i < ptr; ++i) Modify(0, n, u[i], -kInf);
    ptr = 0;
    inplace_merge(op + l, op + m, op + r);
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; ++i) {
            int t; scanf("%d", &t);
            ans[i] = kInf;
            if (t == 0) {
                int x, h; scanf("%d%d", &x, &h);
                op[i] = {t, h, x - 1, -1, i};
                ans[i] = -1;
            } else {
                int l, r, h; scanf("%d%d%d", &l, &r, &h);
                op[i] = {t, h, l - 1, r, i};
            }
        }
        for (int i = 0; i < 4 * n; ++i) nd[i] = -kInf;
        Solve(0, m);
        for (int i = 0; i < m; ++i) {
            if (ans[i] < 0) continue;
            if (ans[i] == kInf) ans[i] = -1;
            printf("%d\n", ans[i]);
        }
    }
}
