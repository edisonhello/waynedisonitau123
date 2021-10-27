#include <bits/stdc++.h>
using namespace std;

int main() {
    int64_t y, l;
    cin >> y >> l;
    int64_t ans = 0;
    for (int b = 2; b <= 1'000'000; ++b) {
        int64_t x = y;
        bool ok = true;
        int64_t v = 0;
        int64_t base = 1;
        while (x > 0) {
            int digit = x % b;
            if (digit >= 10) {
                ok = false;
                break;
            }
            v += digit * base;
            base *= 10;
            x /= b;
        }
        if (!ok) continue;
        if (v >= l) {
            ans = max(ans, static_cast<int64_t>(b));
        }
    }
    for (int64_t t = 10; t <= 1000; ++t) {
        if (t < l) continue;
        vector<int64_t> vl;
        int64_t g = t;
        while (g > 0) {
            vl.push_back(g % 10);
            g /= 10;
        }
        int64_t b = 2;
        for (int d = 60; d >= 0; --d) {
            int64_t B = b + (1LL << d);
            int64_t x = y;
            vector<int64_t> dg;
            while (x > 0) {
                dg.push_back(x % B);
                x /= B;
            }
            if (dg.size() > vl.size()) b = B;
            else if (dg.size() == vl.size()) {
                bool larger = true;
                for (int i = dg.size() - 1; i >= 0; --i) {
                    if (dg[i] != vl[i]) {
                        larger = dg[i] > vl[i];
                        break;
                    }
                }
                if (larger) b = B;
            }
        }
        int64_t x = y;
        int64_t v = 0, base = 1;
        bool ok = true;
        while (x > 0) {
            int64_t d = x % b;
            if (d >= 10) {
                ok = false;
                break;
            }
            v += base * d;
            x /= b;
            base *= 10;
        }
        if (ok && v == t) {
            ans = max(ans, b);
        }
    }
    cout << ans << "\n";
}

