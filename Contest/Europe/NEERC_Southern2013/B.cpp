#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n, r; scanf("%d%d%d", &m ,&n, &r);
    vector<int> cmr(m);
    for (int i = 0; i < m; ++i) {
        int a, b; scanf("%d.%d", &a, &b);
        cmr[i] = a * 10 + b;
    }
    int last = cmr[0];
    long long ans = 0;
    int d = floor(sqrt(r * r - 1) * 10);
    while (n--) {
        int a, b; scanf("%d.%d", &a, &b);
        int at = a * 10 + b;
        int L = at - d, R = at + d;
        if (L <= last && last <= R) continue;
        if (last < L) {
            int npos = *lower_bound(cmr.begin(), cmr.end(), L);
            ans += abs(npos - last);
            last = npos;
        } else {
            int npos = *prev(upper_bound(cmr.begin(), cmr.end(), R));
            ans += abs(npos - last);
            last = npos;
        }
    }
    cout << ans / 10 << "." << ans % 10 << endl;
}
