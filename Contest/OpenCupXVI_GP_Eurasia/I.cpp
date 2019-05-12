#include <bits/stdc++.h>
using namespace std;

void getinv(uint32_t x) {
    cout << "inv of " << x << " = ";
    for (uint32_t i = 2; ; ++i) {
        if (i * x == 1) {
            cout << i << endl;
            return;
        }
    }
}

const unsigned inv1025 = 3222273025;
const unsigned inv9 = 954437177;
const unsigned inv65537 = 4294901761;
const long long mod = (1ll << 32);

unsigned calc(unsigned x, int bit) {
    unsigned y = x;
    for (int i = 31 - bit; i >= 0; --i) {
        int b = (y >> i & 1ll) ^ (y >> (i + bit) & 1ll);
        if (y >> i & 1ll)
            y ^= (1ll << i);
        if (b)
            y ^= (1ll << i);
    }
    return y;
}

unsigned hashs(unsigned v) {
    v = v + (v << 10);
    v = v ^ (v >> 6);
    v = v + (v << 3);
    v = v ^ (v >> 11);
    v = v + (v << 16);
    return v;
}

int main() {
    int q; cin >> q;
    while (q--) {
        // unsigned  _ = rand() * 1ll * rand() % mod;
        // unsigned x = hashs(_);
        unsigned x; cin >> x;
        // unsigned y = x;
        x = x * inv65537;
        x = calc(x, 11);
        x = x * inv9;
        x = calc(x, 6);
        x = x * inv1025;
        cout << x << endl;
    }
}
