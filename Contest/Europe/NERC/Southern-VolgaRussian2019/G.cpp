#include <bits/stdc++.h>
using namespace std;

const int kN = 200'000 + 5;
const int kInf = 1'000'000'000;
long long c[kN], d[kN], e[kN];
int a[kN], b[kN], r[kN];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, k; scanf("%d%d", &n, &k);
        // int n = rand() % 10 + 1, k = rand() % 20 + 2;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            // a[i] = rand() % (k - 1) + 1;
            c[i] = c[i - 1] + a[i];
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &b[i]);
            // b[i] = rand() % (k - 1) + 1;
            d[i] = d[i - 1] + b[i];
        }
        for (int i = 1; i <= n; ++i) e[i] = min(c[i], d[i]);
        int x = 0, y = 0;
        bool win = false;
        vector<int> pk;
        /* {
            int x = 0, y = 0;
            bool gg = false;
            for (int i = 1; i <= n; ++i) {
                x += a[i], y += b[i];
                if (x < k && y >= k) {
                    gg = false;
                    break;
                }
                if (x >= k) {
                    gg = true;
                    break;
                }
                int z = min(x, y);
                x -= z;
                y -= z;
                if (x < k && y >= k) {
                    gg = false;
                    break;
                }
                if (x >= k) {
                    gg = true;
                    break;
                }
            }
            if (gg) {
                puts("-1");
                continue;
            }
        } */
        for (int i = 1; i <= n; ++i) {
            x += a[i], y += b[i];
            if (x < k && y >= k && pk.empty()) {
                win = true;
                break;
            }
            if (x >= k || y >= k) {
                pk.push_back(i - 1);
                int z = min(x - a[i], y - b[i]);
                x -= z, y -= z;
                r[i] = r[i - 1] + 1;
            } else {
                r[i] = r[i - 1];
            }
        }
        if (win) {
            puts("0");
            puts("");
            continue;
        }
        int ans = kInf, t = -1, z = -1;
        for (int i = 1; i <= n; ++i) {
            if (c[i] >= d[i - 1] + k) break;
            if (c[i] < k && d[i] < k) continue;
            long long lft = c[i] - k + 1;
            long long rgt = d[i] - k;
            if (rgt < lft) continue;
            int j = 0;
            for (int d = 20; d >= 0; --d) {
                if (j + (1 << d) + 1 < i && e[j + (1 << d)] < lft) j += (1 << d);
            }
            if (j + 1 < i && e[j + 1] >= lft && e[j + 1] <= rgt) {
                if (r[j + 1] + 1 < ans) {
                    ans = r[j + 1] + 1;
                    t = j + 1;
                    z = i;
                }
            }
        }
        assert(t < n);
        if (ans == kInf) {
            puts("-1");
            continue;
        }
        vector<int> v;
        for (int i = 0; i < pk.size(); ++i) {
            if (pk[i] < t) v.push_back(pk[i]);
        }
        v.push_back(t);
        assert(v.size() == ans);
        printf("%d\n", ans);
        for (int u : v) printf("%d ", u);
        puts("");
    }
    return 0;
}
