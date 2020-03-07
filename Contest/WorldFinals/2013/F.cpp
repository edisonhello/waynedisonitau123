#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    const int m = 2 * n * k;
    vector<int> p(m);
    for (int i = 0; i < m; ++i) scanf("%d", &p[i]);
    sort(p.begin(), p.end());

    auto Check = [&](int d) {
        int gr = 0;
        for (int i = 0; gr < n && i + 1 < m; ++i) {
            if (p[i + 1] - p[i] <= d) {
                if ((m - i) >= 2 * (n - gr) * k) {
                    i++;
                    gr++;
                }
            } 
        }
        return gr == n;
    };

    int ans = 1'000'000'000;
    for (int d = 30; d >= 0; --d) {
        if (ans - (1 << d) < 0) continue;
        if (Check(ans - (1 << d))) ans -= (1 << d);
    }
    printf("%d\n", ans);
}
