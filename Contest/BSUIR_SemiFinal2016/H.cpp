#include <bits/stdc++.h>
using namespace std;

int bit2[22][2], a[10004], bit1[22][2];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 20; ++j) {
            ans += 1ll * (1 << j) * bit2[j][((a[i] >> j) & 1) ^ 1] * 6;
        }
        for (int j = 0; j < 20; ++j) {
            if ((a[i] >> j) & 1) {
                bit2[j][0] += bit1[j][1];
                bit2[j][1] += bit1[j][0];
                bit1[j][1]++;
            } else {
                bit2[j][0] += bit1[j][0];
                bit2[j][1] += bit1[j][1];
                bit1[j][0]++;
            }
        }
        ans += 1ll * a[i] * ((n - 1) * 3 + 1);
    }
    cout << ans << endl;
}
