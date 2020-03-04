#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1e5 + 5;
const int mod = 1e9 + 7;
int a[maxn], b[maxn], kc[maxn], fin[maxn];
bool va[maxn], vb[maxn];
 
int main() {
    int n, m, tc = 0;
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        for (int i = 0; i < m; ++i) scanf("%d", &b[i]);
        for (int i = 0; i < n; ++i) va[i] = false;
        for (int i = 0; i < m; ++i) vb[i] = false;
        for (int i = 0; i <= n; ++i) kc[i] = 0;
        for (int i = 0; i <= n; ++i) fin[i] = 0;
 
        for (int i = 0; i < m; ++i) {
            if (!vb[i]) {
                int cnt = 0;
                for (int j = i; !vb[j]; j = b[j]) {
                    vb[j] = true;
                    ++cnt;
                }
                kc[cnt] += cnt;
            }
        }
 
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; j += i)
                (fin[j] += kc[i]) %= mod;
        }
 
        int ans = 1;
 
        for (int i = 0; i < n; ++i) {
            if (!va[i]) {
                int cnt = 0;
                for (int j = i; !va[j]; j = a[j]) {
                    va[j] = true;
                    ++cnt;
                }
                ans = ans * 1ll * fin[cnt] % mod;
            }
        }
 
        printf("Case #%d: %d\n", ++tc, ans);
    }
}
