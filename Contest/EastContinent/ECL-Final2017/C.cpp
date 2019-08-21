#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; for (int T = 1; T <= t; ++T) {
        cout << "Case #" << T << ": ";
        int n; cin >> n;
        int sum = 0, mx = 0;
        for (int i = 0; i <= n; ++i) { int t; cin >> t; sum += t; }
        for (int i = 0; i < n; ++i) { int x, y; cin >> x >> y; mx = max(mx, y); }
        cout << sum + mx << endl;
    }
}
