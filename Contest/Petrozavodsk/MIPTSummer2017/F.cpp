#include <bits/stdc++.h>
using namespace std;


int main() {
    long long n, m, k; cin >> n >> m >> k;
    if (m < n) swap(n, m);
    if (k == 1) {
        cout << n * m * (n * m % 2) << endl;
        exit(0);
    }
    if (n < 2 * k && m < 2 * k) {
        cout << (n - k + 1) * (m - k + 1) << endl;
        exit(0);
    }
    if (n < 2 * k && m < 3 * k) {
        cout << (n - k + 1) * ((k + 1) - (m - 2 * k + 1) - 1) << endl;
        exit(0);
    }
    if (n < 3 * k && m < 3 * k) {
        cout << ((k + 1) - (n - 2 * k + 1) - 1) * ((k + 1) - (m - 2 * k + 1) - 1) << endl;
        exit(0);
    }
    if (n < 2 * k) {
        cout << n - k + 1 << endl;
        exit(0);
    }
    if (n < 3 * k - 1) {
        cout << ((k + 1) - (n - 2 * k + 1) - 1) + 2 * (n - k + 1 - ((k + 1) - (n - 2 * k + 1) - 1)) << endl;
        exit(0);
    }
    if (n == 3 * k - 1) {
        cout << 0 << endl;
        exit(0);
    }
    cout << 1 << endl;
}

