#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int b, d;
        cin >> b >> d;
        int64_t x = 1LL * b * b;
        int64_t y = 1LL * b * d / __gcd(b, d);
        cout << (x - 1) / y << "\n";
    }
}

