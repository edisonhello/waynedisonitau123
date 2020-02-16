#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;
const int maxn = 100005;
int mu[maxn], pi[maxn];
vector<int> prime;
vector<int> dv[maxn];

void init() {
    mu[1] = pi[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (!pi[i]) {
            pi[i] = i;
            prime.push_back(i);
            mu[i] = -1;
        }
        for (int j = 0; i * prime[j] < maxn; ++j) {
            pi[i * prime[j]] = prime[j];
            mu[i * prime[j]] = -mu[i];
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
    for (int i = 1; i < maxn; ++i) {
        for (int j = i; j < maxn; j += i) dv[j].push_back(i);
    }
}

const int kN = maxn;
const int kMod = mod;
int dp[maxn], s[kN], g[kN];

int fpow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1LL * res * a % kMod;
        a = 1LL * a * a % kMod;
        n >>= 1;
    }
    return res;
}

int main() {
    int n, k; cin >> n >> k;
    init();

    for (int i = 1; i <= n; ++i) {
        if (i & 1) s[i] = 1LL * i * fpow(k, (i + 1) / 2) % kMod;
        else s[i] = (1LL * (i / 2) * fpow(k, i / 2) % kMod + 1LL * (i / 2) * fpow(k, i / 2 + 1)) %kMod;
    }
    for (int i = 1; i <= n; ++i) {
        if (mu[i] < 0) mu[i] += kMod;
    }
    for (int i = 1; i <= n; ++i) {
        dp[i] = s[i];
        for (int d : dv[i]) {
            if (d == 1) continue;
            dp[i] += kMod - 1LL * g[i / d] * (d - 1) % kMod;
            dp[i] %= kMod;
        }
        for (int d : dv[i]) {
            g[i] += 1LL * dp[i / d] * mu[d] % kMod;
            g[i] %= kMod;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) (ans += dp[i]) %= kMod;
    cout << ans << endl;
}

