#include <bits/stdc++.h>
using namespace std;
 
 
int main() {
    long long T = 0, n, k; while (cin >> n >> k) {
        cout << "Case #" << (++T) << ": ";
        if (k <= n) {
            cout << k << '\n';
            continue;
        } else {
            k -= n;
            if (k % (n - 1)) {
                cout << k % (n - 1) << '\n';
            } else {
                if ((k / (n - 1)) & 1) cout << n - 1 << '\n';
                else cout << n << '\n';
            }
        }
    }
}
