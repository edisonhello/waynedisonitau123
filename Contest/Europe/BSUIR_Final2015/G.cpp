#include <bits/stdc++.h>
using namespace std;

vector<int> factors[1000006];

int main() {
    int n, t; cin >> n >> t;
    int q, a, b, m; cin >> q >> a >> b >> m;
    int ans = 0;
    if (n < 1000) {
        int nn = n * n;
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= nn; j += i) {
                factors[j].push_back(i);
            }
        }
    }
    while (t--) {
        q = (1ll * a * q + b) % m;
        int k = q % (1ll * n * n + 1);
        // if (k == 0) continue;
        long long x = 1ll * n * n - 2ll * k;
        long long y = abs(x);
        // printf("k = %d, x = %lld, y = %lld\n", k, x, y);
        if (y == 0) {
            ++ans;
            continue;
        }
        if (n >= 1000) {
            for (int i = 1; i <= n; ++i) {
                if ((i + n) % 2) continue;
                if (x % i == 0 && y / i <= n) {
                    if ((y / i + n) % 2) continue;
                    ++ans;
                    break;
                }
            }
        } else {
            for (int i : factors[y]) {
                if ((i + n) % 2) continue;
                if (x % i == 0 && y / i <= n) {
                    if ((y / i + n) % 2) continue;
                    ++ans;
                    break;
                }
            }
        }
    }
    cout << ans << endl;
}
