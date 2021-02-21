#include <bits/stdc++.h>
using namespace std;

void solve() {
    double l, p1, p2, v1, v2;

    cin >> l >> p1 >> v1 >> p2 >> v2;
    if (p2 < p1) swap(p1, p2), swap(v1, v2);

    double L = p1, R = p2;
    double mnt = 1e20;
    for (int i = 0; i < 100; ++i) {
        double M = (L + R) / 2;
        double ltime = (M + min(M - p1, p1)) / v1;
        double rtime = (l - M + min(l - p2, p2 - M)) / v2;
        mnt = min(mnt, max(ltime, rtime));
        if (ltime > rtime) R = M;
        else L = M;
    }

    mnt = min(mnt, (l + min(p1, l - p1)) / v1);
    mnt = min(mnt, (l + min(p2, l - p2)) / v2);
    mnt = min(mnt, max(p2 / v2, (l - p1) / v1));

    cout << fixed << setprecision(20) << mnt << '\n';
}


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) solve();
}

