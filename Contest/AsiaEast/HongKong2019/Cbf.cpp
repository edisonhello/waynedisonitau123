#include <bits/stdc++.h>
using namespace std;

vector<int> g[100];
int a[100], sum[100], mx[100];

void Dfs(int x, int p) {
    mx[x] = max(mx[x], a[x]);
    sum[x] += a[x];
    for (int u : g[x]) {
        if (u == p) continue;
        mx[u] = mx[x];
        sum[u] = sum[x];
        Dfs(u, x);
    }
}

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < n - 1; ++i) {
            int u, v; cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                memset(sum, 0, sizeof(sum));
                memset(mx, 0, sizeof(mx));
                Dfs(i, -1);
                if (2 * mx[j] < sum[j]) ++ans;
            }
        }
        cout << ans << '\n';
    }
}
