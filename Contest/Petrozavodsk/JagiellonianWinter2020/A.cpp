#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 10'000'000;
constexpr int kA = 50000;
constexpr int kB = 500;
int64_t phic[kA][kB];
int prc[kN];
vector<int> pr;

void Sieve() {
    bitset<kN> v;
    pr.push_back(0);
    for (int i = 2; i < kN; ++i) {
        if (!v[i]) {
            pr.push_back(i);
        }
        for (int j = 1; i * pr[j] < kN; ++j) {
            v[i * pr[j]] = true;
            if (i % pr[j] == 0) break;
        }
    }
    for (int u : pr) prc[u] = 1;
    for (int i = 1; i < kN; ++i) prc[i] += prc[i - 1];
}

int64_t P2(int64_t, int64_t);

int64_t Phi(int64_t m, int64_t n) {
    if (m < kA && n < kB && phic[m][n] != -1) {
        return phic[m][n];
    }
    if (n == 0) return m;
    if (pr[n] >= m) return 1;
    int64_t res = Phi(m, n - 1) - Phi(m / pr[n], n - 1);
    if (m < kA && n < kB) phic[m][n] = res;
    return res;
}

int64_t Pi(int64_t m) {
    if (m < kN) return prc[m];
    int64_t n = Pi(cbrt(m));
    return Phi(m, n) + n - P2(m, n);
}

int64_t P2(int64_t m, int64_t n) {
    int64_t res = 0;
    for (int i = n + 1; 1LL * pr[i] * pr[i] <= m; ++i) {
        res += Pi(m / pr[i]) - Pi(pr[i]) + 1;
    }
    return res;
}

int main() {
    Sieve();
    memset(phic, -1, sizeof(phic));
    int t;
    cin >> t;
    while (t--) {
        int64_t n;
        cin >> n;
        int64_t k = Pi(n) - Pi(n / 2);
        cout << n - (n - k - 1) / 2 << "\n";
    }
}

