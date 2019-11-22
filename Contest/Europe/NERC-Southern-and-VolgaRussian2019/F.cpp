#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int ans = 1e9;
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0) {
            ans = min(ans, 2 * (i + n / i));
        }
    }
    cout << ans << endl;
}
