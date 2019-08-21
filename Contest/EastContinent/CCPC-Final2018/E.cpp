#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const int maxk = 1000 + 5;
vector<pair<int, long long>> g[maxn];
vector<int> wt[maxn];
vector<long long> pref[maxn];
int dfn[maxn], low[maxn], bcc[maxn], tk, tc, take[maxn];
int change[maxn];
short fr[maxn][maxk];
long long dp[maxk], epref[maxn];
stack<int> stk;

void dfs(int x, int p) {
    dfn[x] = low[x] = tk++;
    stk.push(x);
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i].first;
        if (u == p) continue;
        if (dfn[u] == -1) {
            dfs(u, x);
            low[x] = min(low[x], low[u]);
        } else {
            low[x] = min(low[x], dfn[u]);
        }
    }
    if (low[x] == dfn[x]) {
        while (stk.size()) {
            int u = stk.top();
            stk.pop();
            bcc[u] = tc;
            if (u == x) break;
        }
        tc++;
    }
}

int main() {
    int t; scanf("%d", &t);
    for (int _ = 1; _ <= t; ++_) {
        printf("Case %d: ", _);
        int n, m, k; scanf("%d%d%d", &n, &m, &k);

        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < m; ++i) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            --u, --v;
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }

        for (int i = 0; i < n; ++i) {
            sort(g[i].begin(), g[i].end());
            vector<pair<int, long long>> h;
            for (int j = 0, k = 0; j < (int)g[i].size(); ) {
                long long sum = 0;
                for (k = j; k < (int)g[i].size() && g[i][k].first == g[i][j].first; ++k)
                    sum += g[i][k].second;

                h.emplace_back(g[i][j].first, sum);
                j = k;
            }
            g[i] = h;
        }

        for (int i = 0; i < n; ++i) dfn[i] = -1;
        tk = tc = 0;
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (dfn[i] == -1) {
                cnt++;
                dfs(i, -1);
            }
        }

        k -= cnt;

        if (k <= 0) {
            printf("0\n");
            continue;
        }
        for (int i = 0; i < tc; ++i) wt[i].clear();
        
        vector<int> edge;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < (int)g[i].size(); ++j) {
                int u = g[i][j].first, w = g[i][j].second;
                if (u > i) continue;
                if (bcc[u] == bcc[i])
                    wt[bcc[i]].push_back(w);
                else
                    edge.push_back(w);
            }
        }
        sort(edge.begin(), edge.end());
        for (int i = 1; i <= k; ++i) dp[i] = 1e18;
        dp[0] = 0;
        for (int i = 0; i < tc; ++i) {
            for (int j = 0; j <= k; ++j)
                fr[i][j] = j;
            long long cost = wt[i][0];
            for (int j = 1; j < (int)wt[i].size(); ++j) {
                cost += wt[i][j];
                for (int p = k; p >= j; --p) {
                    if (dp[p - j] + cost < dp[p]) {
                        dp[p] = dp[p - j] + cost;
                        fr[i][p] = p - j;
                    }
                }
            }
        }
        long long ans = 1e18;
        long long sum = 0;
        for (int i = 1; i <= k; ++i)
            epref[i] = 1e18;
        for (int i = 1; i <= (int)edge.size(); ++i)
            epref[i] = epref[i - 1] + edge[i - 1];
        vector<int> ine;
        int best = -1;
        for (int i = 0; i <= k; ++i) {
            if (dp[i] + epref[k - i] < ans) {
                ans = dp[i] + epref[k - i];
                best = i;
            }
        }

        int eds = k - best;

        for (int i = tc - 1; i >= 0; --i) {
            take[i] = best - fr[i][best];
            best = fr[i][best];
        }

        multiset<int> ms;
        for (int i = 0; i < eds; ++i) {
            ms.insert(edge[i]); 
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < (int)g[i].size(); ++j) {
                int u = g[i][j].first, w = g[i][j].second;
                if (bcc[u] != bcc[i]) {
                    if (ms.count(w)) {
                        ms.erase(ms.find(w));
                        change[i] = u;
                        cnange[u] = i;
                    }
                }
            }
        }

        printf("%lld\n", ans);
        for (int i = 0; i < n; ++i) printf("%d ", clr[i] + 1);
        puts("");
    }
    return 0;
}
