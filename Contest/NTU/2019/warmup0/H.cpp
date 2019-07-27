#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, w, h; cin >> n >> w >> h;
        long long ans = w * 1ll * h;
        while (n--) {
            long long a; cin >> a;
            if (ans >= 0) ans -= a;
        }
        if (ans == 0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
