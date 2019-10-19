#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<int> g[maxn];
int d[maxn];

int main() {
    int tc; scanf("%d", &tc);
    memset(d, -1, sizeof(d));
    while (tc--) {
        int s, t; scanf("%d%d", &s, &t);
        int r; scanf("%d", &r);
        vector<int> used = {s, t};
        while (r--) {
            int k; scanf("%d", &k);
            vector<int> v(k);
            for (int i = 0; i < k; ++i) {
                scanf("%d", &v[i]);
                used.push_back(v[i]);
            }
            for (int i = 0; i < k; ++i) {
                for (int j = i + 1; j < k; ++j) {
                    g[v[i]].push_back(v[j]);
                    g[v[j]].push_back(v[i]);
                }
            }
        }
        queue<int> q;
        q.push(s);
        d[s] = 0;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int u : g[x]) {
                if (d[u] == -1) {
                    d[u] = d[x] + 1;
                    q.push(u);
                }
            }
        }
        printf("%d\n", d[t]);
        for (int u : used) {
            g[u].clear();
            d[u] = -1;
        }
    }
}
