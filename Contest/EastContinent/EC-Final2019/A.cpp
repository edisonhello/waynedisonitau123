#include <bits/stdc++.h>
using namespace std;
 
 
int main() {
    int n, m; cin >> n >> m;
    long long ans = 0;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            int l = i, r = n - i;
            int u = j, d = m - j;
            int a = min(l, r);
            int b = min(u, d);
            long long c = a * b * 2 + a + b;
            // cout << i << ' ' << j << ' ' << c << endl;
            ans += c;
        }
    }
    cout << ans << endl;
}
