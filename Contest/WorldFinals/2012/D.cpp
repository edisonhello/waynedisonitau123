#include <bits/stdc++.h>
using namespace std;

const int kN = 100'000 + 5;
const int kMod = 1'000'000'000 + 123;
const int kP = 131;
const int kInf = 1'000'000'000;
int pw[kN];

struct Fib {
    vector<int> pref, suff;
    vector<int> phash, shash;
    int length;
    
    Fib() {}

    Fib(int d) : length(1) {
        pref.resize(1, d);
        suff.resize(1, d);
        InitHash();
    }

    void InitHash() {
        phash.resize(pref.size(), pref[0]);
        for (int i = 1; i < pref.size(); ++i) {
            phash[i] = (1LL * phash[i - 1] * kP + pref[i]) % kMod;
        }
        shash.resize(suff.size(), suff[0]);
        for (int i = 1; i < suff.size(); ++i) {
            int g = 1LL * pw[i] * suff[i] % kMod;
            shash[i] = (shash[i - 1] + g) % kMod;
        }
    }
};

Fib operator+(const Fib &lhs, const Fib &rhs) {
    Fib res; 
    res.length = min(kInf, lhs.length + rhs.length);
    res.pref.resize(min(kN, res.length));
    res.suff.resize(min(kN, res.length));
    for (int i = 0; i < lhs.pref.size(); ++i) {
        res.pref[i] = lhs.pref[i];
    }
    for (int i = lhs.pref.size(); i < res.pref.size(); ++i) {
        res.pref[i] = rhs.pref[i - lhs.pref.size()]; 
    }
    for (int i = 0; i < rhs.suff.size(); ++i) {
        res.suff[i] = rhs.suff[i];
    }
    for (int i = rhs.suff.size(); i < res.suff.size(); ++i) {
        res.suff[i] = lhs.suff[i - rhs.suff.size()];
    }
    res.InitHash();
    return res;
}

const int kM = 100 + 5;
long long dp[kM];
bool v[kM];
Fib f[kM];
char s[kN];

long long Dfs(int n, int m, int h) {
    if (n == 0) {
        if (m == 1 && s[0] == '0') return 1;
        return 0;
    }
    if (n == 1) {
        if (m == 1 && s[0] == '1') return 1;
        return 0;
    }
    if (v[n]) return dp[n];
    dp[n] = Dfs(n - 1, m, h) + Dfs(n - 2, m, h);
    v[n] = true;
    for (int i = 1; i < m; ++i) {
        if (f[n - 1].length < i || f[n - 2].length < m - i) continue;
        int a = f[n - 1].shash[i - 1], b = f[n - 2].phash[m - i - 1];
        int c = (1LL * a * pw[m - i] + b) % kMod;
        // printf("n = %d c = %d\n", n, c);
        if (h == c) dp[n]++;
    }
    // printf("dp[%d] = %lld\n", n, dp[n]);
    return dp[n];
}

int main() {
    f[0] = Fib(0);
    f[1] = Fib(1); 
    pw[0] = 1;
    for (int i = 1; i < kN; ++i) pw[i] = 1LL * pw[i - 1] * kP % kMod;
    for (int i = 2; i < kM; ++i) f[i] = f[i - 1] + f[i - 2];
    // for (int i = 0; i <= 6; ++i) {
    //     printf("fib(%d) (%d) = {", i, f[i].length);
    //     for (int u : f[i].pref) printf("%d", u);
    //     printf(", ");
    //     for (int u : f[i].suff) printf("%d", u);
    //     printf("}\n");
    //     printf("phash = {");
    //     for (int u : f[i].phash) printf("%d ", u);
    //     printf("}\n");
    //     printf("shash = {");
    //     for (int u : f[i].shash) printf("%d ", u);
    //     printf("}\n");
    // }
    int n, tc = 0;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i <= n; ++i) v[i] = false;
        scanf("%s", s);
        int hv = 0, m = strlen(s);
        for (int i = 0; i < m; ++i) {
            int d = s[i] - '0';
            hv = (1LL * hv * kP + d) % kMod;
        }
        // printf("hv = %d\n", hv);
        printf("Case %d: %lld\n", ++tc, Dfs(n, m, hv));
    }
    return 0;
}

