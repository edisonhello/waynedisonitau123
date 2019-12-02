#include <bits/stdc++.h>
using namespace std;

const int kN = 200'000 + 5;
int dg[kN];

int main() {
    int n, m, ka, kb;
    scanf("%d%d%d%d", &n, &m, &ka, &kb);
    vector<int> x(ka), y(kb);
    for (int i = 0; i < ka; ++i) {
        scanf("%d", &x[i]);
        x[i]--;
    }
    for (int i = 0; i < kb; ++i) {
        scanf("%d", &y[i]);
        y[i]--;
    }
    if (ka > m - 1 || kb > n - 1) {
        puts("No");
        return 0;
    }
    while (x.size() < m - 1) x.push_back(0);
    while (y.size() < n - 1) y.push_back(n);
    for (int i = 0; i < n + m; ++i) dg[i] = 1;
    for (int u : x) ++dg[u];
    for (int u : y) ++dg[u];
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n + m; ++i) {
        if (dg[i] == 1) pq.push(i);
    }
    puts("Yes");
    int i = 0, j = 0;
    while (!pq.empty()) {
        int v = pq.top(); pq.pop();
        --dg[v];
        if (v < n) {
            if (j == n - 1) {
                int q = -1;
                for (int i = n; i < n + m; ++i) {
                    if (dg[i] == 1) {
                        assert(q == -1);
                        q = i;
                    }
                }
                assert(q != -1);
                printf("%d %d\n", v + 1, q + 1);
                break;
            }
            int z = y[j++];
            printf("%d %d\n", v + 1, z + 1);
            if (--dg[z] == 1) pq.push(z);
        } else {
            if (i == m - 1) {
                int q = -1;
                for (int i = 0; i < n; ++i) {
                    if (dg[i] == 1) {
                        assert(q == -1);
                        q = i;
                    }
                }
                assert(q != -1);
                printf("%d %d\n", v + 1, q + 1);
                break;
            }
            int z = x[i++];
            printf("%d %d\n", v + 1, z + 1);
            if (--dg[z] == 1) pq.push(z);
        }
    }
    return 0;
}
