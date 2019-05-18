#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    double ans = 0.0;
    while (n--) {
        double a, b; cin >> a >> b;
        ans += a * b;
    }
    cout << fixed << setprecision(20) << ans << endl;
}
