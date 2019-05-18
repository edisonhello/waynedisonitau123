#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int maxk = 41;
const int mod = 1e9 + 7;
int s[maxk][maxn];

int main() {
    int n, m, k; cin >> n >> m >> k;
    while (m--) {
        int t, x, y; cin >> t;
        if (t == 0) {
            cin >> x >> y;
            s[0][x] += y;
            s[0][x] %= mod;
            for (int i = 1; i <= k; ++i) {
                for (int j = 1; j <= n; ++j) s[i][j] = (s[i - 1][j] + s[i][j - 1]) % mod;
            }
        } else {
            cin >> x;
            cout << s[k][x] << endl;
        }
    }
}
