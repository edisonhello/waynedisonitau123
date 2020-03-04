#include <bits/stdc++.h>
using namespace std;

long long H(long long previousHash, string &transaction) {
    long long v = previousHash;
    for (int i = 0; i < transaction.length(); i++) {
        v = (v * 31 + transaction[i]) % 1000000007;
    }
    return v * 7 % 1000000007;
}

int main() {
    long long n; cin >> n;
    string s = "jizz";
    long long h = H(n, s);
    for (long long x = 10000000; x <= 90000000; x += 10000000) {
        long long y = (x + 1000000007 - h) % 1000000007;
        if (y >= 0 && y < 1000000000) {
            string tt = "jizzzz";
            long long hh = H(x, tt);
            for (long long z = 10000000; z <= 90000000; z += 10000000) {
                long long p = (z + 1000000007 - hh) % 1000000007;
                if (p >= 0 && p < 1000000000) {
                    cout << s << ' ' << y << endl;
                    cout << tt << ' ' << p << endl;
                    return 0;
                }
            }
        }
    }
    assert(false);
}


