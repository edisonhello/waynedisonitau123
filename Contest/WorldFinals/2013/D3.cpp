#include <bits/stdc++.h>
using namespace std;

const vector<int> ps = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
uint64_t cnk[100][100];
constexpr uint64_t kInf = (1ULL << 63);

long long Dfs(int i, int prv, int tk, long long val, long long n) {
    if (n == 1) return val;
    if (i == ps.size()) return -1;
    long long k = 1;
    long long res = LLONG_MAX;
    for (int j = 0; j <= prv; ++j) {
        uint64_t ch = cnk[tk + j][j];
        if (1.0 * val * k >= kInf) break;
        if (ch <= n && n % ch == 0) {
            long long kr = Dfs(i + 1, j, tk + j, val * k, n / ch);
            if (kr != -1) res = min(res, kr);
        }
        if (ch > n) break;
        if (1.0 * k * ps[i] >= kInf) break;
        k = k * ps[i];
    }
    return res;
}


uint64_t Add(uint64_t a, uint64_t b) {
    if (a == kInf || b == kInf) return kInf;
    uint64_t res = a + b;
    return min(res, kInf);
}

int main() {
    for (int i = 0; i < 100; ++i) {
        cnk[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            cnk[i][j] = Add(cnk[i - 1][j], cnk[i - 1][j - 1]);
        }
    }
    long long n;
    while (cin >> n) {
        if (n == 1) cout << "1 2\n";
        else cout << n << " " << Dfs(0, 99, 0, 1, n) << "\n";
    }
}
