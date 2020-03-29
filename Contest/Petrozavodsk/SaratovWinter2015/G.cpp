#include <bits/stdc++.h>
using namespace std;


int main() {
    long long a, b; cin >> a >> b;

    long long mx = b;

    auto Calc = [&] (long long x) {
        long long r = 1;
        while (x) {
            r *= x % 10;
            x /= 10;
        }
        return r;
    };

    auto Update = [&] (long long x) {
        if (Calc(x) > Calc(mx)) mx = x;
    };

    for (long long x = 1; ; x *= 10) {
        long long bb = b;
        bb -= bb % x;
        --bb;
        if (a <= bb) Update(bb);

        if (x == 1000000000000000000ll) break;
    }

    cout << mx << endl;
}

