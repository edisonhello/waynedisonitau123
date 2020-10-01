#include <bits/stdc++.h>
using namespace std;

long long f(long long a, long long b) {
    if (a == 0 && b == 0) return 1;
    if (a == 0) return 2;
    if (b == 0) return 2;
    if (a % b == 0) return a / b + 1;
    if (b > a) return 1 + f(b - a, a);
    if ((a / b) & 1) return a / b + f(b, a % b);
    return a / b + f(a % b, b);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T = 0;
    int t; cin >> t; while (t--) {
        long long a, b; cin >> a >> b;
        ++T;
        cout << "Case #" << T << ": ";
        cout << f(a, b) << '\n';
    }
}

