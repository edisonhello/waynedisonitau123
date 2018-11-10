#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e15;

int main() {
    int p; cin >> p;
    if (p <= 20) {
        cout << 0 << endl;
        return 0;
    }
    int n, m, k; cin >> n >> m >> k;
    vector<pair<int, int>> x, y, z;
    long long e1 = 0, e2 = 0, e3 = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        int a, b; cin >> a >> b;
        x.emplace_back(a, b);
        e1 += b;
        ans += a;
    }
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        y.emplace_back(a, b);
        e2 += b;
        ans += a;
    }
    for (int i = 0; i < k; ++i) {
        int a, b; cin >> a >> b;
        z.emplace_back(a, b);
        e3 += b;
        ans += a;
    }
    double s = cbrt(1.0 * e1 * e2 * e3);
    if ((s + 1) * (s + 4) * (s + 5) < p) {
        cout << "DEAREST DROP" << endl;
        return 0;
    }
    clock_t c = clock();
    vector<int> v1, v2, v3;
    for (int i = 0; i < n; ++i) v1.push_back(i);
    for (int i = 0; i < m; ++i) v2.push_back(i);
    for (int i = 0; i < k; ++i) v3.push_back(i);
    while (1.0 * (clock()) / CLOCKS_PER_SEC < 0.980) {
        int a = n == 0 ? 0 : rand() % (n + 1);
        int b = m == 0 ? 0 : rand() % (m + 1);
        int c = k == 0 ? 0 : rand() % (k + 1);
        random_shuffle(v1.begin(), v1.end());
        random_shuffle(v2.begin(), v2.end());
        random_shuffle(v3.begin(), v3.end());
        long long cost = 0, e1 = 0, e2 = 0, e3 = 0;
        for (int i = 0; i < a; ++i) {
            cost += x[v1[i]].first; 
            e1 += x[v1[i]].second;
        }
        for (int i = 0; i < b; ++i) {
            cost += y[v2[i]].first; 
            e2 += y[v2[i]].second;
        }
        for (int i = 0; i < c; ++i) {
            cost += z[v3[i]].first; 
            e3 += z[v3[i]].second;
        }
        double s = cbrt(e1 * 1ll * e2 * e3);
        if ((s + 1) * (s + 4) * (s + 5) >= p) ans = min(ans, cost);
    }
    printf("%lld\n", ans);
    return 0;
}
