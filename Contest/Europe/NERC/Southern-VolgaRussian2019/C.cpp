#include <bits/stdc++.h>
using namespace std;

const int kN = 200'000 + 5;
const long long kInf = 1'000'000'000'000'000'000;
int l[kN], r[kN];
long long p[kN];
vector<int> seg[kN];
long long tg[kN * 4];
pair<long long, int> nd[kN * 4];

void Build(int l, int r, long long k, int o = 0) {
    if (r - l == 1) {
        nd[o] = make_pair(1LL * k * l, l);
        return;
    }
    Build(l, (l + r) >> 1, k, o * 2 + 1);
    Build((l + r) >> 1, r, k, o * 2 + 2);
    nd[o] = max(nd[o * 2 + 1], nd[o * 2 + 2]);
}

void Push(int o) {
    nd[o * 2 + 1].first += tg[o];
    nd[o * 2 + 2].first += tg[o];
    tg[o * 2 + 1] += tg[o];
    tg[o * 2 + 2] += tg[o];
    tg[o] = 0;
}

void Modify(int l, int r, int ql, int qr, long long v, int o = 0) {
    if (l >= qr || ql >= r) return;
    if (l >= ql && r <= qr) {
        nd[o].first += v;
        tg[o] += v;
        return;
    }
    Push(o);
    Modify(l, (l + r) >> 1, ql, qr, v, o * 2 + 1);
    Modify((l + r) >> 1, r, ql, qr, v, o * 2 + 2);
    nd[o] = max(nd[o * 2 + 1], nd[o * 2 + 2]);
}

pair<long long, int> Query(int l, int r, int ql, int qr, int o = 0) {
    if (l >= qr || ql >= r) return make_pair(-kInf, -1);
    if (l >= ql && r <= qr) return nd[o];
    Push(o);
    return max(Query(l, (l + r) >> 1, ql, qr, o * 2 + 1),
               Query((l + r) >> 1, r, ql, qr, o * 2 + 2));
}

int main() {
    int n; long long k;
    scanf("%d%lld", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%lld", &l[i], &r[i], &p[i]);
        seg[r[i]].push_back(i);
    }
    Build(0, kN, k);
    long long ans = 0;
    int tl = -1, tr = -1;
    for (int r = 0; r < kN; ++r) {
        for (int i : seg[r]) {
            Modify(0, kN, 0, l[i] + 1, p[i]);
        }
        auto res = Query(0, kN, 0, r + 1);
        if (res.first - 1LL * k * (r + 1) > ans) {
            ans = res.first - 1LL * k * (r + 1);
            tl = res.second;
            tr = r;
        }
    }
    vector<int> v;
    for (int i = 0; i < n; ++i) {
        if (l[i] >= tl && r[i] <= tr) v.push_back(i);
    }
    if (ans == 0) {
        puts("0");
        return 0;
    }
    printf("%lld %d %d %d\n", ans, tl, tr, (int)v.size());
    for (int i : v) printf("%d ", i + 1);
    puts("");
    return 0;
}
