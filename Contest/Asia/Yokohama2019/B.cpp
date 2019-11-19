#include <bits/stdc++.h>
using namespace std;

bool as[55][55];
int val[55][55];

int mx[55][55];

int main() {
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) mx[i][j] = -1e9;

    while (k--) {
        int x, y, z; cin >> x >> y >> z;
        as[x][y] = 1;
        val[x][y] = z;
        for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) 
            mx[i][j] = max(mx[i][j], z - abs(i - x) - abs(j - y));
    }

    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) if (as[i][j] && val[i][j] < mx[i][j]) {
        cout << "No" << endl;
        exit(0);
    }

    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= m; ++j) {
    //         cout << mx[i][j] << ' '; 
    //     }
    //     cout << endl;
    // }

    long long sum = 0;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) sum += mx[i][j];
    cout << sum << endl;
}
