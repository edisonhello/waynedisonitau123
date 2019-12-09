#include <bits/stdc++.h>
using namespace std;

int d[1005][1005];

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) d[i][j] = 1e9;
    for (int i = 1; i <= n; ++i) d[i][i] = 0;

    for (int i = 1; i <= n; ++i) {
        int t; cin >> t;
        for (int j = max(1, i - t); j <= min(n, i + t); ++j) {
            d[i][j] = 1;
        }
    }

    for (int k = 1; k <= n; ++k) for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    int mx = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) 
        mx = max(mx, min(d[i][j], d[j][i]));

    cout << mx << endl;

}
