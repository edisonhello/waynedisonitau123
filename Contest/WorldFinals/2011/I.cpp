#include <bits/stdc++.h>
using namespace std;
 
const int kN = 1e5 + 5;
vector<int> p[2][2];
int x[kN], y[kN];
 
namespace seg {
 
const int kC = 30'000'000;
int tg[2][kC], lc[kC], rc[kC], sz;
 
void Init() { sz = 0; }
 
int gnode() {
    tg[0][sz] = tg[1][sz] = 0;
    lc[sz] = -1;
    rc[sz] = -1;
    return sz++;
}
 
void Modify(int l, int r, int ql, int qr, int p, int v, int o) {
    if (l >= qr || ql >= r) return;
    if (l >= ql && r <= qr) {
        tg[p][o] = max(tg[p][o], v);
        return;
    }
    int m = (l + r) >> 1;
    if (qr <= m) {
        if (lc[o] == -1) lc[o] = gnode();
        Modify(l, m, ql, qr, p, v, lc[o]);
    } else if (ql >= m) {
        if (rc[o] == -1) rc[o] = gnode();
        Modify(m, r, ql, qr, p, v, rc[o]);
    } else {
        if (lc[o] == -1) lc[o] = gnode();
        if (rc[o] == -1) rc[o] = gnode();
        Modify(l, m, ql, qr, p, v, lc[o]);
        Modify(m, r, ql, qr, p, v, rc[o]);
    }
}
 
bool Query(int l, int r, array<int, 2> v, int d, int o) {
    for (int i = 0; i < 2; ++i) v[i] = max(v[i], tg[i][o]);
    // printf("l = %d r = %d v[0] = %d v[1] = %d\n", l, r, v[0], v[1]);
    if (v[0] + v[1] >= d) return true;
    return (lc[o] != -1 && Query(l, (l + r) >> 1, v, d, lc[o])) &&
           (rc[o] != -1 && Query((l + r) >> 1, r, v, d, rc[o]));
}
 
}
 
bool Check(int n, int d) {
    int t = d + d + 1;
    seg::Init();
    int rt = seg::gnode();
    for (int i : p[0][0]) {
        int px = d + d + 1 - abs(x[i]);
        int py = d + d + 1 - abs(y[i]);
        if (px <= 0 || py <= 0) continue;
        seg::Modify(0, t, 0, px, 0, py, rt);
    }
    for (int i : p[0][1]) {
        int px = d + d + 1 - abs(x[i]);
        int py = d + d + 1 - abs(y[i]);
        if (px <= 0 || py <= 0) continue;
        seg::Modify(0, t, t - px, t, 0, py, rt);
    }
    for (int i : p[1][0]) {
        int px = d + d + 1 - abs(x[i]);
        int py = d + d + 1 - abs(y[i]);
        if (px <= 0 || py <= 0) continue;
        seg::Modify(0, t, 0, px, 1, py, rt);
    }
    for (int i : p[1][1]) {
        int px = d + d + 1 - abs(x[i]);
        int py = d + d + 1 - abs(y[i]);
        if (px <= 0 || py <= 0) continue;
        seg::Modify(0, t, t - px, t, 1, py, rt);
    }
    int top = 1e9, bot = -1e9, lft = -1e9, rgt = 1e9;
    for (int i = 0; i < n; ++i) {
        if (x[i] == 0 && y[i] < 0) bot = max(bot, y[i]);
        if (x[i] == 0 && y[i] > 0) top = min(top, y[i]);
        if (y[i] == 0 && x[i] < 0) lft = max(lft, x[i]);
        if (y[i] == 0 && x[i] > 0) rgt = min(rgt, x[i]);
    }
    top = d + d + 1 - abs(top);
    bot = d + d + 1 - abs(bot);
    lft = d + d + 1 - abs(lft);
    rgt = d + d + 1 - abs(rgt);
    if (bot > 0) seg::Modify(0, t, 0, t, 0, bot, rt);
    if (top > 0) seg::Modify(0, t, 0, t, 1, top, rt);
    if (lft > 0) seg::Modify(0, t, 0, lft, 0, d + d + 1, rt);
    if (rgt > 0) seg::Modify(0, t, t - rgt, t, 1, d + d + 1, rt);
    array<int, 2> v = {0, 0};
    return !seg::Query(0, t, v, t, rt);
} 
 
int main() {
    int n, tc = 0; 
    while (scanf("%d", &n) != EOF) {
        if (n == -1) break;
        printf("Case %d: ", ++tc);
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j)
                p[i][j].clear();
        }
        for (int i = 0; i < n; ++i) scanf("%d%d", &x[i], &y[i]);
        int v[4] = {0, 0, 0, 0};
        for (int i = 0; i < n; ++i) {
            if (x[i] <= 0 && y[i] <= 0) v[0] = 1;
            if (x[i] >= 0 && y[i] <= 0) v[1] = 1;
            if (x[i] <= 0 && y[i] >= 0) v[2] = 1;
            if (x[i] >= 0 && y[i] >= 0) v[3] = 1;
 
            if (x[i] < 0 && y[i] < 0) p[0][0].push_back(i);
            if (x[i] > 0 && y[i] < 0) p[0][1].push_back(i);
            if (x[i] < 0 && y[i] > 0) p[1][0].push_back(i);
            if (x[i] > 0 && y[i] > 0) p[1][1].push_back(i);
        }
        if (!v[0] || !v[1] || !v[2] || !v[3]) {
            puts("never");
            continue;
        }
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (j == 0)
                    sort(p[i][j].begin(), p[i][j].end(), [&](int a, int b) { return x[a] < x[b]; });
                else
                    sort(p[i][j].begin(), p[i][j].end(), [&](int a, int b) { return x[a] > x[b]; });
            }
        }
        int ans = 0;
        for (int d = 25; d >= 0; --d) {
            if (Check(n, ans + (1 << d)))
                ans += (1 << d);
        }
        printf("%d\n", ans + 1);
    }
    return 0;
}
