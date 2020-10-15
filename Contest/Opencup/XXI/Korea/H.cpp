#include <bits/stdc++.h>
using namespace std;

long long c[1000006];
long long cc[1000006];

int main() {
    int n; cin >> n;
    long long sig = 0;
    long long zz = 0;
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        cc[i] = c[i];
        sig += c[i];
        if (c[i]) zz = i;
    }

    if (sig == 1) {
        cout << max(1ll, zz) << endl;
        exit(0);
    }

    auto meow = [&] (int z) {
        for (int i = 0; i < n; ++i) {
            c[i] = cc[i];
        }
        for (int i = z; i <= 1000000; ++i) {
            c[0] += c[i];
            c[i] = 0;
        }

        long long t = 1;
        for (int i = z; i >= 0; --i) {
            long long u = min(c[i], t / 2);
            if (i == 0) u = c[i];
            t -= u;
            if (u < c[i]) {
                c[0] += c[i] - u;
            }
            if (t <= 0) return 1;
            if (i > 1) { 
                t *= 2;
                if (t >= 1000000000000) return 0;
            }
        }
        return 0;
    };

    int L = 0, R = 1e6;
    while (L < R) {
        int M = (L + R + 1) >> 1;
        if (meow(M)) L = M;
        else R = M - 1;
    }
    cout << L << endl;

}

