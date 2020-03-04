#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
vector<int> g[maxn], pass;
int a[maxn][2], c[maxn], v[maxn];
int l[maxn][2], r[maxn][2];

bool dfs(int x, int z = 0) {
    c[x] = z;
    bool res = true;
    pass.push_back(x);
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (c[u] == -1) {
            res &= dfs(u, z ^ 1);
        } else {
            if (c[u] == c[x])
                res = false;
        }
    }
    return res;
}

int main() {
    int t; scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) 
            g[i].clear();

        for (int i = 0; i < m; ++i) {
            int u, v; scanf("%d%d", &u, &v);
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        for (int i = 0; i < n; ++i) scanf("%d%d", &a[i][0], &a[i][1]);

        bool bip = true;
        for (int i = 0; i < n; ++i) c[i] = -1;

        int p = 0;
        vector<tuple<int, int, int>> segs;
        for (int i = 0; i < n; ++i) {
            if (c[i] == -1) {
                pass.clear();
                bip &= dfs(i);
                for (int j = 0; j < 2; ++j) {
                    l[p][j] = 2e9, r[p][j] = -1;
                    for (int k = 0; k < (int)pass.size(); ++k) {
                        l[p][j] = min(l[p][j], a[pass[k]][c[pass[k]] ^ j]);
                        r[p][j] = max(r[p][j], a[pass[k]][c[pass[k]] ^ j]);
                    }
                }
                if (l[p][0] > l[p][1]) {
                    swap(l[p][0], l[p][1]);
                    swap(r[p][0], r[p][1]);
                }
                if (r[p][0] >= r[p][1]) {
                    l[p][0] = l[p][1];
                    r[p][0] = r[p][1];
                    v[p] = 0;
                } else {
                    v[p] = 1;
                }
                segs.emplace_back(l[p][0], p, 0);
                segs.emplace_back(l[p][1], p, 1);

                ++p;
            }
        }
        printf("Case %d: ", tc);
        if (!bip) {
            printf("IMPOSSIBLE\n");
            continue;
        }

        multiset<int> ms;
        for (int i = 0; i < p; ++i) ms.insert(r[i][0]);
        sort(segs.begin(), segs.end());
        int ans = 2e9;
        bool stp = false;
        for (int i = 0, j = 0; i < (int)segs.size(); ++i) {
            while (j < (int)segs.size() && get<0>(segs[j]) < get<0>(segs[i])) {
                if (get<2>(segs[j]) == v[get<1>(segs[j])]) {
                    stp = true;
                    break;
                } else {
                    ms.erase(ms.find(r[get<1>(segs[j])][0]));
                    ms.insert(r[get<1>(segs[j])][1]);
                }
                ++j;
            }
            if (stp) break;
            ans = min(ans, *ms.rbegin() - get<0>(segs[i]));
        }
        printf("%d\n", ans);

    }
}
