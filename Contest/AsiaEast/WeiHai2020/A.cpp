#include <bits/stdc++.h>
using namespace std;


int main() {
    int t; cin >> t; while (t--) {
        long long n, x, t; cin >> n >> x >> t;
        long long a = max(2 * n * t, x + 2 * t) + 2 * n * t;
        long long b = max(2 * n * t + t, x + t) + 2 * n * t;
        cout << min(a, b) << '\n';
    }
}

