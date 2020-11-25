#include <bits/stdc++.h>
using namespace std;

int meow(long long n) {
    if (n == 0) return 0;
    long long m = n;
    long long a = 1;
    long long b = 0;
    long long c = 1;
    while (n >= c) {
        b += (n / c) % 10 * c;
        c *= 10;
        a = (1ll * a * b) % (m + 1);
    }
    return a;
}

int main() {
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;

        long long tot = 0;
        while (m--) {
            int to = meow(n);
            tot += to;

            if (to == n) {
                tot += 1ll * to * m;
                break;
            }
            n = to;
        }

        cout << tot << endl;
    }

}

