#include <bits/stdc++.h>
using namespace std;

const int kN = 1'000'000;
double nd[kN * 4], tg[kN * 4];
bool ht[kN * 4];
int a[kN];

void Build(int l, int r, int o = 0) {
    if (r - l == 1) {
        nd[o] = a[l];
        return;
    }
    int m = (l + r) >> 1;
    Build(l, m, o * 2 + 1);
    Build(m, r, o * 2 + 2);
    nd[o] = nd[o * 2 + 1] + nd[o * 2 + 2];
}

void Push(int o, int l, int r) {
    if (ht[o]) {
        int m = (l + r) >> 1;
        nd[o * 2 + 1] = tg[o] * (m - l);
        nd[o * 2 + 2] = tg[o] * (r - m);
        ht[o * 2 + 1] = ht[o * 2 + 2] = true;
        tg[o * 2 + 1] = tg[o * 2 + 2] = tg[o];
        ht[o] = false;
    }
}

void Modify(int l, int r, int ql, int qr, double v, int o = 0) {
    if (l >= qr || ql >= r) return;
    if (l >= ql && r <= qr) {
        nd[o] = (r - l) * v;
        tg[o] = v;
        ht[o] = true;
        return;
    }
    Push(o, l, r);
    int m = (l + r) >> 1;
    Modify(l, m, ql, qr, v, o * 2 + 1);
    Modify(m, r, ql, qr, v, o * 2 + 2);
    nd[o] = nd[o * 2 + 1] + nd[o * 2 + 2];
}

double Query(int l, int r, int ql, int qr, int o = 0) {
    if (l >= qr || ql >= r) return 0;
    if (l >= ql && r <= qr) return nd[o];
    Push(o, l, r);
    int m = (l + r) >> 1;
    return Query(l, m, ql, qr, o * 2 + 1) + 
           Query(m, r, ql, qr, o * 2 + 2);
}

int main() {
    int n, q; scanf("%d%d", &n, &q);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    Build(0, n);
    while (q--) {
        static char s[10];
        scanf("%s", s);
        if (s[0] == 's') {
            int l, r; scanf("%d%d", &l, &r); --l;
            double sum = Query(0, n, l, r);
            double ex = sum / (r - l);
            Modify(0, n, l, r, ex);
        } else {
            int i; scanf("%d", &i); --i;
            printf("%.20lf\n", Query(0, n, i, i + 1));
        }
    }
    return 0;
}
