#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int a[maxn], b[maxn];

int main() {
    int t; scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        for (int i = 0; i < n; ++i) b[i] = 1;
        int z = m;
        m -= n;
        priority_queue<pair<double, int>> pq;
        for (int i = 0; i < n; ++i) pq.emplace(1.0 * a[i] * a[i] / (1.0 * b[i] * (b[i] + 1)), i);

        while (m--) {
            int x = pq.top().second; pq.pop();
            ++b[x];
            pq.emplace(1.0 * a[x] * a[x] / (1.0 * b[x] * (b[x] + 1)), x);
        }

        double avg = 1.0 * accumulate(a, a + n, 0ll) / z;

        double sum = 0.0;
        for (int i = 0; i < n; ++i) {
            double d = (a[i] * 1.0 / b[i] - avg) * (a[i] * 1.0 / b[i] - avg);
            sum += b[i] * d;
        }
        printf("Case #%d: %.20lf\n", tc, sum / z);
    }
}
