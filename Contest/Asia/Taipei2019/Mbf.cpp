#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n, d; cin >> m >> n >> d;
    long long c = 1;
    for (int i = 0; i < n; ++i) c *= (m - i);
    for (int i = 0; i < n; ++i) c /= (n - i);
    long long cc = c, mt = 1;
    int k = 0;
    while (cc % d == 0) {
        cc /= d;
        k += 1;
        mt *= d;
    }
    cout << cc % d << endl;
}
