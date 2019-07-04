#include <bits/stdc++.h>
using namespace std;
 
const int mod = 1000000007;
 
int pw(int b, int n, int m, int a = 1) {
    while (n) {
        if (n & 1) a = 1ll * a * b % m;
        b = 1ll * b * b % m; n >>= 1;
    } return a;
}
int inv(int x) { return pw(x, mod - 2, mod); }
 
int fac[1000006], ifac[1000006];
 
int C(int n, int m) {
    if (m > n) return 0;
    if (m < 0) return 0;
    return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
 
vector<pair<int, int>> R[1000006];
int it[1000006];
int l[1000006];
 
int dfs(int l, int r) {
    // cerr << "dfs " << l << " " << r << endl;
    // if (l == r) return 1;
    if (l > r) return 1;
    if (it[l] >= (int)R[l].size()) return 0;
    if (R[l][it[l]].first != r) return 0;
    int at = R[l][it[l]++].second;
    if (at > r) return 0;
    if (at + 1 <= l) return 0;
    if (l == r) return 1;
    return 1ll * dfs(l, at - 1) * dfs(at + 1, r) % mod * C(r - l, at - l) % mod;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    fac[0] = 1;
    for (int i = 1; i < 1000006; ++i) fac[i] = fac[i - 1] * 1ll * i % mod;
    ifac[1000005] = inv(fac[1000005]);
    for (int i = 1000004; i >= 0; --i) ifac[i] = ifac[i + 1] * 1ll * (i + 1) % mod;
    int n, T = 0; while (cin >> n) {
        cout << "Case #" << (++T) << ": ";
        for (int i = 1; i <= n; ++i) cin >> l[i];
        for (int i = 1; i <= n; ++i) {
            int r; cin >> r;
            R[l[i]].emplace_back(r, i);
        }
        for (int i = 1; i <= n; ++i) sort(R[i].begin(), R[i].end()), reverse(R[i].begin(), R[i].end());
        // for (int i = 1; i <= n; ++i) st[0][i] = R
        cout << dfs(1, n) << '\n';
 
        for (int i = 1; i <= n; ++i) R[i].clear();
        for (int i = 1; i <= n; ++i) it[i] = 0;
        // for (int j = 0; j < 21; ++j) for (int i = 1; i <= n; ++i) st[j][i] = 0, at[j][i] = 0;
    }
}
