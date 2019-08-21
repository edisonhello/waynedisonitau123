#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int a[maxn], b[maxn], c[maxn];

int main() {
    int t; scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d%d", &a[i], &b[i]);
        for (int i = 0; i < n; ++i) {
            int sum = 0, p = 1;
            while (sum < a[i]) {
                sum += p;
                p++;
            }
            c[i] = p - 1;
        }
        vector<int> v(n);
        iota(v.begin(), v.end(), 0);
        sort(v.begin(), v.end(), [&](int i, int j) {
            return c[i] * 1ll * b[j] < c[j] * 1ll * b[i];
        });

        long long ans = 0;
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += c[v[i]];
            ans += b[v[i]] * sum;
        }
        printf("Case #%d: %lld\n", tc, ans);
    }
}
