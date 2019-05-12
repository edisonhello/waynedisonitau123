#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-6;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); 
    int n; cin >> n; while (n--) {
        long double a, b, c; cin >> a >> b >> c;
        long long aa = a * 100000 + eps, bb = b * 100000 + eps, cc = c * 100000 + eps;
        // cerr << aa << " " << bb << " " << cc << '\n';
        if ((aa * bb + bb * cc + cc * aa) * 100000 < aa * bb * cc) {
            cout << "YES" << '\n';
        } else cout << "NO" << '\n';
    }
}
