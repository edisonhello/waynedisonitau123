#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int a, b, c; cin >> a >> b >> c;
        int ab, bc, ca; cin >> ab >> bc >> ca;
        long long ans = 0;
        for (int i = 0; i <= a; ++i) {
            for (int j = 0; j <= b; ++j) {
                int ta = a - i;
                int tb = b - i - j;
                if (tb < 0) continue;
                int tc = c - j;
                if (tc < 0) continue;
                ans = max(ans, ab * 1ll * i + bc * 1ll * j + ca * 1ll * min(ta, tc));
            }
        }
        cout << ans << endl;
    }
}
