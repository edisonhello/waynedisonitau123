#include <bits/stdc++.h>
using namespace std;

const int maxn = 256;
const double eps = 1e-7;
int v[maxn], r[maxn], cnt[maxn];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> v[i];
    double ans = 1e9;
    int si = -1, ai = -1, ci = -1;
    for (int s = 0; s < 16; ++s) {
        for (int a = 0; a < 16; ++a) {
            for (int c = 0; c < 16; ++c) {
                r[0] = s;
                memset(cnt, 0, sizeof(cnt));
                for (int i = 1; i <= n; ++i) {
                    r[i] = (a * r[i - 1] + c) % 256;
                }
                for (int i = 1; i <= n; ++i) {
                    int o = (v[i - 1] + r[i]) % 256;
                    ++cnt[o];
                }
                double entropy = 0.0;
                for (int i = 0; i < 256; ++i) {
                    double p = 1.0 * cnt[i] / n;
                    if (cnt[i] > 0) entropy -= p * log(p);
                }
                if (entropy < ans - eps) {
                    ans = entropy;
                    si = s;
                    ai = a;
                    ci = c;
                }
            }
        }
    }
    printf("%d %d %d\n", si, ai, ci);
}
