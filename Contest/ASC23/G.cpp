

#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5, maxc = 40005;
int _dp[maxn][maxc], _fr[maxn][maxc], a[maxn];

inline int &dp(int i, int j) {
    return _dp[i][j + 20000];
}

inline int &fr(int i, int j) {
    return _fr[i][j + 20000];
}

int main() {
#ifndef LOCAL
    freopen("polygon.in", "r", stdin);
    freopen("polygon.out", "w", stdout);
#endif
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int j = 0; j < maxn; ++j) for (int i = -20000; i <= 20000; ++i) dp(j, i) = -maxn;
    dp(0, 0) = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = -20000; j <= 20000; ++j) {
            if (j + a[i] <= 20000) {
                if (dp(i - 1, j) + 1 > dp(i, j + a[i])) {
                    dp(i, j + a[i]) = dp(i - 1, j) + 1;
                    fr(i, j + a[i]) = j;
                }
            }
            if (j - a[i] >= -20000) {
                if (dp(i - 1, j) + 1 > dp(i, j - a[i])) {
                    dp(i, j - a[i]) = dp(i - 1, j) + 1;
                    fr(i, j - a[i]) = j;
                }
            }
            if (dp(i - 1, j) > dp(i, j)) {
                dp(i, j) = dp(i - 1, j);
                fr(i, j) = j;
            }
        }
    }
    cout << dp(n, 0) << endl;
    if (dp(n, 0) == 0) {
        return 0;
    }
    int x = n, y = 0;
    vector<int> pos, neg;
    while (x) {
        int t = fr(x, y);
        if (t != y) {
            if (y - t > 0) pos.push_back(y - t);
            else neg.push_back(y - t);
        }
        --x, y = t;
    }
    int last = 0, ky = 0;
    cout << 0 << ' ' << 0 << endl;
    for (int i : pos) {
        last += i;
        cout << last << ' ' << ky << endl;
        ++ky;
        cout << last << ' ' << ky << endl;
    }
    for (int i : neg) {
        last += i;
        cout << last << ' ' << ky << endl;
        ++ky;
        if (last) cout << last << ' ' << ky << endl;
    }
}
