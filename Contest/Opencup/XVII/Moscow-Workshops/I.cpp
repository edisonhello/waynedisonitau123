#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

uint32_t x0, x1, a, b, c;

uint32_t gen() {
    uint32_t t = x0 * a + x1 * b + c;
    x0 = x1;
    x1 = t;
    return x0 >> 2;
}

uint32_t ar[10000007];
uint32_t curmin = INT_MAX;

int main() {
    int n, q; 
    cin >> n >> q >> x0 >> x1 >> a >> b >> c;
    for (int i = 0; i < n; ++i) ar[i] = INT_MAX;

    uint32_t sum = 0, pp = 10099u;
    for (int i = 1; i <= q; ++i) {
        int p = gen(); uint32_t x = gen();
        p %= n;
        uint32_t o = ar[p];
        ar[p] = x;
        if (o == curmin) {
            curmin = INT_MAX;
            for (int z = 0; z < n; ++z) {
                curmin = min(curmin, ar[z]);
            }
        }
        curmin = min(curmin, x);
        
        sum += curmin * pp;
        pp *= 10099u;
    }

    cout << sum << endl;
}
