#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int p, q, n; cin >> p >> q >> n;
        int d = __gcd(p, q);
        if (n % d) {
            cout << "R\n";
            continue;
        }
        p /= d; q /= d; n /= d;
        if (p == q) {
            cout << "E\n";
            continue;
        }
        if (p < q) {
            if (n >= p) cout << "E\n";
            else if (n % (q - p) == 0) cout << "P\n";
            else cout << "E\n";
            continue;
        }
        if (q < p) {
            if (n < p) cout << "P\n";
            else if (n % p == 0) cout << "E\n";
            else if (n % p < q && (n % p) % (p - q) == 0) cout << "E\n";
            else cout << "P\n";
            continue;
        }
    }
}
