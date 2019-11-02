#include <bits/stdc++.h>
using namespace std;

const int kN = 2e5 + 5;
const int kMagic = 7;
const long double kMagicMagic = 2.0 / 3;
vector<int> g[kN];
long double dp[kN];
int v[kN];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    priority_queue<pair<long double, int>, vector<pair<long double, int>>, greater<pair<long double, int>>> pq;
    pq.emplace(0.0, n - 1);

    auto Calc = [&](int x) {
        if (v[x] >= kMagic) return;
        vector<long double> p;
        for (int u : g[x]) {
            if (v[u]) p.push_back(dp[u]);
        }
        sort(p.begin(), p.end());
        for (int i = p.size() - 1; i >= 0; --i) {
            if (p[i] - p[0] < kMagicMagic) {
                long double sum = 3 + p[0];
                for (int j = i; j >= 0; --j) {
                    sum = 0.25 * sum + (long double)(0.75) * (p[j] + 1) + 1;
                }
                dp[x] = sum - 1;
                break;
            }
        }
        v[x] += 1;
        pq.emplace(dp[x], x);
    };

    v[n - 1] = kMagic;
    while (!pq.empty()) {
        int x = pq.top().second; pq.pop();
        for (int u : g[x]) Calc(u);
    }
    printf("%.20Lf\n", dp[0]);
}
 
