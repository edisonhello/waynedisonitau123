#include <bits/stdc++.h>
using namespace std;

int h[505][505];

int main() {
    int a, b, n, m; cin >> a >> b >> n >> m;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        cin >> h[i][j];
    }

    long long mx = 0;

    auto Solve = [&] () {
        for (int aa = 1; aa <= a; ++aa) {
            for (int i = 1; i + aa - 1 <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    auto Calc = [&] (const int bb) -> long long {
                        int mn = INT_MAX;
                        for (int ii = i; ii < i + aa; ++ii) {
                            for (int jj = j; jj < j + bb; ++jj) {
                                mn = min(mn, h[ii][jj]);
                            }
                        }
                        long long up = aa * bb * mn;
                        long long dn = m * n - aa * bb;
                        long long hh = (up / dn) - (up % dn ? 0 : 1);
                        return aa * bb * (mn + hh);
                    };
                    int l = 1, r = min(m - j + 1, b);
                    while (r - l >= 5) {
                        int ml = (l + r) / 2;
                        int mr = ml + 1;
                        long long ansl = Calc(ml);
                        long long ansr = Calc(mr);
                        if (ansl > ansr) r = mr;
                        else l = ml;
                    }
                    for (int bb = l; bb <= r; ++bb) mx = max(mx, Calc(bb));
                }
            }
        }
    };

    Solve();
    swap(a, b);
    Solve();

    cout << mx << endl;
}
