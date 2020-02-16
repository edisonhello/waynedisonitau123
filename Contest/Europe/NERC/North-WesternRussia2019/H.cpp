#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; scanf("%d", &n);
    vector<int> a(n), s(n + 1);
    int kp = -1;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        s[i + 1] = s[i] + a[i];
        kp = max(kp, a[i]);
    }
    int q; scanf("%d", &q);
    vector<vector<int>> qr(s[n] + 1);
    for (int i = 0; i < q; ++i) {
        int t; scanf("%d", &t);
        qr[t].push_back(i);
    }
    vector<int> ans(q);
    for (int t = 1; t <= s[n]; ++t) {
        if (qr[t].empty()) continue;
        if (t < kp) {
            for (int u : qr[t]) ans[u] = -1;
            continue;
        }
        int p = 0, res = 0;
        while (p < n) {
            // printf("t = %d p = %d\n", t, p);
            auto it = upper_bound(s.begin(), s.end(), s[p] + t);
            assert(it != s.begin());
            int pos = prev(it) - s.begin();
            assert(pos > p);
            p = pos;
            res += 1;
        }
        for (int u : qr[t]) ans[u] = res;
    }
    for (int i = 0; i < q; ++i) {
        if (ans[i] == -1) puts("Impossible");
        else printf("%d\n", ans[i]);
    }
}

