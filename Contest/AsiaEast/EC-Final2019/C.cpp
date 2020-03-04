#include <bits/stdc++.h>
using namespace std;
 
const int kN = 100'000 + 5;
const int kMod = 998244353;
 
int fpow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1LL * res * a % kMod;
        a = 1LL * a * a % kMod;
        n >>= 1;
    }
    return res;
}
 
vector<int> dv[kN];
int g[kN], f[kN], ck[kN], h[kN], r[kN];
vector<int> cf[kN];
 
int main() {
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d", &g[i]);
    for (int i = 2; i <= n; ++i) {
        for (int j = i + i; j <= n; j += i) dv[j].push_back(i);
    }
    for (int i = 0; i < 2000; ++i) {
        ck[i] = 1;
        for (int j = 0; j < i; ++j) {
            ck[i] = 1LL * ck[i] * (k - j) % kMod;
            ck[i] = 1LL * ck[i] * fpow(i - j, kMod - 2) % kMod;
        }
    }
    f[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (dv[i].empty()) {
            f[i] = 1LL * g[i] * fpow(k, kMod - 2) % kMod;
            cf[i] = {f[i]};
            // printf("i = %d, ", i); for (int u : cf[i]) printf("%d ", u); puts("");
            continue;
        }
        for (int u : dv[i]) {
            if (cf[i].size() < cf[u].size() + 1) cf[i].resize(cf[u].size() + 1, 0);
            for (int j = 0; j < cf[u].size(); ++j) (cf[i][j + 1] += 1LL * f[i / u] * cf[u][j] % kMod) %= kMod;
        }
        int sum = 0;
        for (int j = 1; j < cf[i].size(); ++j) {
            sum += 1LL * ck[j + 1] * cf[i][j] % kMod;
            sum %= kMod;
        }
        // printf("sum = %d\n", sum);
        f[i] = 1LL * (g[i] + kMod - sum) % kMod * fpow(k, kMod - 2) % kMod;
        cf[i][0] = 1LL * f[i] % kMod;
        // printf("i = %d, ", i); for (int u : cf[i]) printf("%d ", u); puts("");
    }
    for (int i = 1; i <= n; ++i) printf("%d ", f[i]);
    puts("");
    // for (int i = 1; i <= n; ++i) r[i] = f[i];
    // for (int i = 0; i < k - 1; ++i) {
    //     for (int j = 1; j <= n; ++j) h[j] = 0;
    //     for (int j = 1; j <= n; ++j) {
    //         for (int u : dv[j]) {
    //             h[j] += 1LL * f[u] * r[j / u] % kMod;
    //             h[j] %= kMod;
    //         }
    //         h[j] += 1ll * f[1] * r[j] % kMod;
    //         h[j] %= kMod;
    //         if (j != 1) {
    //             h[j] += 1LL * f[j] * r[1] % kMod;
    //             h[j] %= kMod;
    //         }
    //     }
    //     for (int i = 1; i <= n; ++i) r[i] = h[i];
    // }
    // for (int i = 1; i <= n; ++i) assert(r[i] == g[i]);
    return 0;
}
