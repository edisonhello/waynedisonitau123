#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
char s[maxn];
int nxt[maxn][26], last[26];

int main() {
#ifdef ONLINE_JUDGE
    freopen("jingles.in", "r", stdin);
    freopen("jingles.out", "w", stdout);
#endif
    int t; scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        int n = strlen(s);
        for (int i = 0; i < 26; ++i) last[i] = n;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < 26; ++j) nxt[i][j] = last[j];
            last[s[i] - 'a'] = i;
        }
        map<int, int> f;
        for (int i = 0; i < n; ++i) {
            int mask = 1 << (s[i] - 'a');
            int j = i;
            while (j < n) {
                int p = n;
                for (int k = 0; k < 26; ++k) {
                    if (mask >> k & 1) continue;
                    p = min(p, nxt[j][k]);
                }
                j = p;
                f[mask] = max(f[mask], j - i);
                if (j < n) {
                    mask ^= 1 << (s[j] - 'a');
                }
            }
        }
        long long ans = 0;
        for (auto it : f) ans += __builtin_popcount(it.first) * 1ll * it.second;
        printf("%d %lld\n", (int)f.size(), ans);
    }
    return 0;
}
