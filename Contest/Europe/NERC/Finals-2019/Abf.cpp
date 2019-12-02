#include <bits/stdc++.h>
using namespace std;

struct seg {
    int l, r, t;
} a[200005];

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].l >> a[i].r >> a[i].t;
    int left = 0;
    int ans = 0;
    while (true) {
        int r = INT_MAX;
        for (int i = 1; i <= n; ++i) {
            int rr = max(a[i].l, left) + a[i].t;
            if (rr > a[i].r) continue;
            if (rr < r) r = rr;
        }
        if (r == INT_MAX) break;
        left = r;
        ++ans;
        cout << "new r " << r << endl;
    }
    cout << ans << endl;
}
