#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n, m; cin >> n >> m;
        cout << "Case #" << i << ": ";
        if (n == 1) cout << fixed << setprecision(6) << "1.000000 " << (double)(m + 1) / (2 * m) << endl;
        else cout << fixed << setprecision(6) << 0.5 << " " << (double)(m + 1) / (2 * m) << endl;
    }
}
