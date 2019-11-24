#include <bits/stdc++.h>
using namespace std;

const int kN = 500 + 5, kM = 15;
const int kInf = 1e9;
bitset<kN> bs[kM];
char buf[kN];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 0; i < m; ++i) {
            scanf("%s", buf);
            for (int j = 0; j < n; ++j) {
                if (buf[j] == '1') bs[i][j] = 1;
                else bs[i][j] = 0;
            }
        }
        int ans = kInf;
        for (int s = 0; s < (1 << m); ++s) {
            bitset<kN> v;
            for (int i = 0; i < m; ++i) {
                if (s >> i & 1) v |= bs[i];
            }
            if (v.count() == n) ans = min(ans, __builtin_popcount(s));
        }
        if (ans == kInf) ans = -1;
        printf("%d\n", ans);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j)
                bs[i][j] = 0;
        }
    }
}
