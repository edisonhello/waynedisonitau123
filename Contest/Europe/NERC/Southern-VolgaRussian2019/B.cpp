#include <bits/stdc++.h>
using namespace std;

int c[10005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int m, n; cin >> m >> n;
    while (m--) {
        int t; cin >> t;
        ++c[t];
    }
    sort(c + 1, c + 1 + n);
    long long mn = 1e15;
    for (int i = 1; i <= n + 1; ++i) {
        int trip = 0, mx = 0;    
        for (int j = i; j <= n; ++j) {
            ++trip;
            mx = max(mx, c[j]);
        }
        for (int j = 1, k = i - 1; j <= k; ++j, --k) {
            ++trip;
            mx = max(mx, j == k ? c[j] : c[j] + c[k]);
        }
        // cerr << "i = " << i << " trip = " << trip << " mx = " << mx << endl;
        mn = min(mn, 1ll * trip * mx);
    }
    cout << mn << '\n';
}
