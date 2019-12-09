#include <bits/stdc++.h>
using namespace std;

const int kN = 600'000 + 5;
const int kInf = 1'000'000'000;
int a[kN], s[kN], dp[kN];

int Sign(int x) {
    if (x == 0) return 0;
    return x > 0 ? 1 : -1;
}

int nd[kN * 4];

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

multiset<int> ks[kN];

int main() {
    int n, l, r; scanf("%d%d%d", &n, &l, &r);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
    }

    auto Erase = [&](int x) {
        ks[s[x] + n].erase(ks[s[x] + n].find(dp[x]));
        int v = ks[s[x] + n].empty() ? -kInf : *ks[s[x] + n].rbegin();
        Modify(0, n + n, s[x] + n, v);
    };

    auto Insert = [&](int x) {
        ks[s[x] + n].insert(dp[x]);
        int v = ks[s[x] + n].empty() ? -kInf : *ks[s[x] + n].rbegin();
        Modify(0, n + n, s[x] + n, v);
    };

    fill(nd, nd + kN * 4, -kInf);
    dp[0] = 0;

    for (int i = 1, jl = 0, jr = 0; i <= n; ++i) {
        dp[i] = -kInf;
        while (jr < i && i - jr > r) Erase(jr++);
        while (jl < i && i - jl >= l) Insert(jl++);
        dp[i] = max(dp[i], Query(0, n + n, 0, s[i] + n) + 1);
        dp[i] = max(dp[i], Query(0, n + n, s[i] + n + 1, n + n) - 1);
        dp[i] = max(dp[i], Query(0, n + n, s[i] + n, s[i] + n + 1));
        /* for (int j = i - 1; j >= 0; --j) {
            if (i - j >= l && i - j <= r) {
                int add = Sign(s[i] - s[j]);
                dp[i] = max(dp[i], dp[j] + add);
            }
        } */
    }
    if (dp[n] < -1e8) puts("Impossible");
    else printf("%d\n", dp[n]);
}
