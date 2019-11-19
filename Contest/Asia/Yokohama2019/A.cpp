#include <bits/stdc++.h>
using namespace std;

int main() {
    long long t; cin >> t;
    long long ans = t;
    long long speed = 1;
    long long tl = 1, last = 1;
    vector<long long> p = {1};
    while (p.back() <= 1'000'000'000'000'000) p.push_back(p.back() * 3);
    for (int k = 1; ; ++k) {
        speed *= 3;
        tl += speed;
        if (tl + last - 1 <= t) {
            long long rem = t - tl - last + 1;
            long long tt = 2 * k;
            while (rem > 0) {
                long long k = *prev(upper_bound(p.begin(), p.end(), min(speed, rem)));
                long long tk = rem / k;
                rem -= tk * k;
                tt += tk;
            }
            ans = min(ans, 1LL * tt);
        } else {
            break;
        }
        last = tl;
    }
    cout << ans << endl;
    return 0;
}
