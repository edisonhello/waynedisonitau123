#include <bits/stdc++.h>
using namespace std;

long long Calc(long long x) {
    long long c = 0;
    for (long long i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            ++c;
            if (i * i != x) ++c;
        }
    }
    return c;
}


int main() {
    long long L, R, Q; cin >> L >> R >> Q;
    long long a = L / Q, b = R / Q;
    if (a == b && a == 0) {
        cout << "infinity" << endl;
    } else if (a == b) {
        cout << Calc(a * Q) << endl;
    } else cout << Calc(Q) << endl;
}

