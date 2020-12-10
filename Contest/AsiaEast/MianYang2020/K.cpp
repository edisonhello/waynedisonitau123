#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        int x;
        cin >> x;
        if (x == 6) {
            cout << "-1\n";
            continue;
        }
        if (x % 2 == 1) {
            cout << 1 << "\n";
            continue;
        }
        if (x % 4 == 0) {
            cout << 2 << "\n";
            continue;
        }
        // x, x + 1, x + 2
        if ((x - 3) % 3 == 0) {
            int k = (x - 3) / 3;
            if (k > 1 && __gcd(k, k + 2) == 1) {
                cout << 2 << "\n";
                continue;
            }
        }
        // x, x + 3
        if ((x - 3) % 2 == 0) {
            int k = (x - 3) / 2;
            if (k > 1 && __gcd(k, k + 3) == 1) {
                cout << 3 << "\n";
                continue;
            }
        }
        // x, x + 1, x + 3
        if ((x - 4) % 3 == 0) {
            int k = (x - 4) / 3;
            if (k > 1 && __gcd(k, k + 3) == 1 && __gcd(k + 1, k + 3) == 1) {
                cout << 3 << "\n";
                continue;
            }
        }
        // x, x + 2, x + 3
        if ((x - 5) % 3 == 0) {
            int k = (x - 5) / 3;
            if (k > 1 && __gcd(k, k + 3) == 1 && __gcd(k, k + 2) == 1) {
                cout << 3 << "\n";
                continue;
            }
        }
        cout << 4 << "\n";
    }
}

