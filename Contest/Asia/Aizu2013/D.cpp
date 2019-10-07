#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    int H, h, m, s;
    while (scanf("%lld%lld%lld%lld", &H, &h, &m, &s) != EOF) {
        if (!H && !h && !m && !s) break;
        int t = 3600 * h + 60 * m + s;
        int goal = ((119 * H - 1) * t + 3600 * H - 1) / (3600 * H);
        int g = __gcd(3600 * goal * H, 119 * H - 1);
        int x = 3600 * goal * H / g;
        int y = (119 * H - 1) / g;
        if ((H - 1) * x % (3600 * H * y) == 0) {
            ++goal;
            g = __gcd(3600 * goal * H, 119 * H - 1);
            x = 3600 * goal * H / g;
            y = (119 * H - 1) / g;
        }
        int k = x / y;
        int hh = (k / 3600) % H;
        k %= 3600;
        int mm = k / 60;
        k %= 60;
        int ss = k * y + (x % y);
        printf("%lld %lld %lld %lld\n", hh, mm, ss, y);
    }
}
