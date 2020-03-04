#include <bits/stdc++.h>
using namespace std;

const int kN = 1e5 + 5;
const int kMod = 1e9 + 7;
array<array<int, 2>, 2> nd[kN * 4];
int tg[kN * 4];
char s[kN];

void Debug(array<array<int, 2>, 2> x) {
    printf("%d %d %d %d\n", x[0][0], x[0][1], x[1][0], x[1][1]);
}

array<array<int, 2>, 2> Merge(array<array<int, 2>, 2> x, array<array<int, 2>, 2> y) {
    // printf("x: "); Debug(x);
    // printf("y: "); Debug(y);
    array<array<int, 2>, 2> res{};
    res[0][0] = (1LL * x[0][0] * y[0][0] + 1LL * x[1][0] * y[0][1]) % kMod;
    res[0][1] = (1LL * x[0][1] * y[0][0] + 1LL * x[1][1] * y[0][1]) % kMod;
    res[1][0] = (1LL * x[0][0] * y[1][0] + 1LL * x[1][0] * y[1][1]) % kMod;
    res[1][1] = (1LL * x[0][1] * y[1][0] + 1LL * x[1][1] * y[1][1]) % kMod;
    // printf("res: "); Debug(res);
    return res;
}

void Build(int l, int r, int o = 0) {
    if (r - l == 1) {
        if (s[l] == 'A') {
            nd[o][0][0] = 1;
            nd[o][0][1] = 1;
            nd[o][1][0] = 0;
            nd[o][1][1] = 1;
        } else {
            nd[o][1][0] = 1;
            nd[o][1][1] = 1;
            nd[o][0][0] = 1;
            nd[o][0][1] = 0;
        }
        return;
    }
    int m = (l + r) >> 1;
    Build(l, m, o * 2 + 1);
    Build(m, r, o * 2 + 2);
    nd[o] = Merge(nd[o * 2 + 1], nd[o * 2 + 2]);
}

array<array<int, 2>, 2> Flip(array<array<int, 2>, 2> x) {
    array<array<int, 2>, 2> res{};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j)
            res[i ^ 1][j ^ 1] = x[i][j];
    }
    return res;
}

void Push(int o) {
    if (tg[o]) {
        nd[o * 2 + 1] = Flip(nd[o * 2 + 1]);
        nd[o * 2 + 2] = Flip(nd[o * 2 + 2]);
        tg[o * 2 + 1] ^= 1;
        tg[o * 2 + 2] ^= 1;
        tg[o] = 0;
    }
}

void Modify(int l, int r, int ql, int qr, int o = 0) {
    if (l >= qr || ql >= r) return;
    if (l >= ql && r <= qr) {
        nd[o] = Flip(nd[o]);
        tg[o] ^= 1;
        return;
    }
    Push(o);
    int m = (l + r) >> 1;
    Modify(l, m, ql, qr, o * 2 + 1);
    Modify(m, r, ql, qr, o * 2 + 2);
    nd[o] = Merge(nd[o * 2 + 1], nd[o * 2 + 2]);
}

array<array<int, 2>, 2> Query(int l, int r, int ql, int qr, int o = 0) {
    // printf("ql = %d qr = %d\n", ql, qr);
    if (l >= ql && r <= qr) return nd[o];
    Push(o);
    int m = (l + r) >> 1;
    if (qr <= m) return Query(l, m, ql, qr, o * 2 + 1);
    if (ql >= m) return Query(m, r, ql, qr, o * 2 + 2);
    return Merge(Query(l, m, ql, qr, o * 2 + 1), Query(m, r, ql, qr, o * 2 + 2));
}

int main() {
    int n, q; scanf("%d%d", &n, &q);
    scanf("%s", s);
    Build(0, n);
    for (int i = 0; i < q; ++i) {
        int t; scanf("%d", &t);
        if (t == 1) {
            int l, r; scanf("%d%d", &l, &r);
            Modify(0, n, l - 1, r);
        } else {
            int l, r, a, b; scanf("%d%d%d%d", &l, &r, &a, &b);
            auto f = Query(0, n, l - 1, r);
            printf("%lld %lld\n", (1LL * f[0][0] * a + 1LL * f[0][1] * b) % kMod,
                                  (1LL * f[1][0] * a + 1LL * f[1][1] * b) % kMod);
        }
    }
    return 0;
}
