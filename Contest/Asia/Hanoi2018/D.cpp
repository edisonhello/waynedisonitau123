#include <bits/stdc++.h>
using namespace std;

int ask(int x) {
    cout << "QUERY " << x << " " << (x + 500000000 - 1) << endl;
    int y; cin >> y; return y;
}
int sign(int x) {
    if (x == 0) return 0;
    if (x < 0) return -1;
    return 1;
}

int main() {
    int N; cin >> N;
    int want = N / 2;
    int L = 0, R = 500000000 - 1;
    int zero = sign(ask(0) - want);
    if (zero == 0) {
        cout << "YES " << 0 << endl;
        exit(0);
    }
    while (L < R) {
        int M = (L + R) >> 1;
        int m = sign(ask(M) - want);
        if (m == 0) {
            cout << "YES " << M << endl;
            exit(0);
        }
        if (m * zero == 1) {
            L = M + 1;
        } else {
            R = M - 1;
        }
    }
    cout << "YES " << L << endl;
}


