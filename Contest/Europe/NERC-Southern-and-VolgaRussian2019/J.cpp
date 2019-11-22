#include <bits/stdc++.h>
using namespace std;

long long c[30005];

bool ok(int n, long long k, long long m) {
    long long prv = 0;
    long long get = 0;
    for (int i = 1; i <= n; ++i) {
        long long now = c[i];
        if (prv) {
            if (prv + now >= m) {
                now -= m - prv;
                ++get;
            }
        }
        get += now / m;
        now %= m;
        prv = now;
    }
    return get >= k;
}

void solve(int n, long long k) {
    long long L = 0, R = 1e13;
    while (L < R) {
        long long M = (1 + L + R) >> 1;
        if (ok(n, k, M)) L = M;
        else R = M - 1;
    }
    cout << k * L << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        long long n, k; cin >> n >> k;
        for (int i = 1; i <= n; ++i) cin >> c[i];
        solve(n, k);
    }
}
