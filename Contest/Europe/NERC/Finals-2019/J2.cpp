#include <bits/stdc++.h>
using namespace std;

const int kN = 2'000'000 + 5;
int cnt[kN], c[kN], ck[kN], sk[kN];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &c[i]);
            ++cnt[c[i]];
        }
        sort(c, c + n);
        n = unique(c, c + n) - c;
        vector<int> v;
        for (int i = 0; i < n; ++i) {
            for (int s = 1; s <= cnt[c[i]] + 1; ++s) {
                int t = (cnt[c[i]] + s - 1) / s;
                assert(t * s >= cnt[c[i]]);
                if (t * (s - 1) <= cnt[c[i]]) {
                    sk[s] += t;
                    ck[s] += 1;
                    v.push_back(s);
                }
            }
        }
        int ans = 1e9;
        for (int u : v) {
            if (ck[u] == n) ans = min(ans, sk[u]);
        }
        for (int u : v) {
            ck[u] = 0;
            sk[u] = 0;
        }
        for (int i = 0; i < n; ++i) cnt[c[i]] = 0;
        printf("%d\n", ans);
    }
}
