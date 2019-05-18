#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
const int mod = 998244353;
vector<pair<int, int>> g[maxn];
vector<int> vt[maxn];
int fa[maxn], sz[maxn], ed[maxn], deg[maxn];
int fi[maxn], se[maxn], nxt[maxn], prv[maxn], cnxt[maxn], cprv[maxn];
pair<int, int> dp[maxn][2];
bool inq[maxn], cyc[maxn];

int find(int x) {
    if (x == fa[x]) return fa[x];
    return fa[x] = find(fa[x]);
}

void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (sz[x] > sz[y]) swap(x, y);
    sz[y] += sz[x];
    fa[x] = y;
}

pair<int, int> solve_cycle(int root) {
    // printf("solve cycle root = %d\n", root);
    queue<int> q;

    for (int i = 0; i < (int)vt[root].size(); ++i) {
        int x = vt[root][i];
        deg[x] = (int)g[x].size();

        if (deg[x] == 1) {
            inq[x] = true;
            q.push(x);
        }
    }

    int cost = 0, way = 1;

    while (q.size()) {
        int x = q.front(); q.pop();
        for (int i = 0; i < (int)g[x].size(); ++i) {
            int u = g[x][i].first, j = g[x][i].second;
            if (inq[u]) continue;
            if (fi[j] == u) ++cost;
            --deg[u];
            if (deg[u] == 1) {
                q.push(u);
                inq[u] = true;
            }
            
        }
    } 

    // puts("here");

    vector<int> cycle;
    for (int i = 0; i < (int)vt[root].size(); ++i) {
        int x = vt[root][i];
        if (!inq[x]) {
            cyc[x] = true;
            cycle.push_back(x);
        }
    }

    assert(!cycle.empty());

    if (cycle.size() == 2) {
        set<int> s;
        for (int i = 0; i < (int)g[cycle[0]].size(); ++i) {
            if (g[cycle[0]][i].first == cycle[1])
                s.insert(fi[g[cycle[0]][i].second]);
        }
        if (s.size() == 1)
            return make_pair(cost + 1, way + 1);
        else
            return make_pair(cost, way);
    }
    if (cycle.size() == 1) {
        return make_pair(cost, way);
    }
    int x = cycle[0];
    set<int> s;
    s.insert(x);
    for (int i = 1; i < (int)cycle.size(); ++i) {
        for (int j = 0; j < (int)g[x].size(); ++j) {
            int u = g[x][j].first, p = g[x][j].second;
            if (!cyc[u]) continue;
            if (s.count(u)) continue;
            // printf("%d -> %d\n", x, u);
            // printf("p = %d\n", p);
            nxt[x] = u;
            cnxt[x] = fi[p] == u;
            prv[u] = x;
            cprv[u] = fi[p] == x;
            x = u;
            s.insert(x);
            break;
        }
    }

    // puts("here");

    nxt[x] = cycle[0];
    prv[cycle[0]] = x;

    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i].first, j = g[x][i].second;
        if (u == cycle[0]) {
            cnxt[x] = (fi[j] == cycle[0]);
            cprv[cycle[0]] = (fi[j] == x);
            break;
        }
    }

    int qnxt = 0;

    for (int i = cycle[0], j = 0; j < (int)cycle.size(); ++j, i = nxt[i]) {
        qnxt += cnxt[i];
        // printf("i = %d nxt = %d cnxt = %d\n", i, nxt[i], cnxt[i]);
    }

    int qprv = 0;

    for (int i = cycle[0], j = 0; j < (int)cycle.size(); ++j, i = prv[i]) {
        qprv += cprv[i];
        // printf("i = %d prv = %d cprv = %d\n", i, prv[i], cprv[i]);
    }


    cost += min(qnxt, qprv);
    if (qnxt == qprv) ++way;

    return make_pair(cost, way);
}

int fpow(int x, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1)
            res = res * 1ll * x % mod;
        x = x * 1ll * x % mod;
        n >>= 1;
    }
    return res;
}

int inverse(int x) {
    if (x == 0)
        throw;

    return fpow(x, mod - 2);
}

void dfs(int x, int p, int f) {
    dp[x][0].second = 1;
    dp[x][1].second = 1;
    dp[x][0].first = 0;
    dp[x][1].first = 0;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i].first, j = g[x][i].second;
        if (u == p) continue;
        dfs(u, x, fi[j] == x);

        dp[x][0].first += dp[u][0].first;
        dp[x][0].second = dp[x][0].second * 1ll * dp[u][0].second % mod;

        dp[x][1].first += dp[u][0].first;
        dp[x][1].second = dp[x][0].second * 1ll * dp[u][0].second % mod;
    }

    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i].first;
        if (u == p) continue;

        int cost = dp[u][1].first - dp[u][0].first + dp[x][0].first;
        int way = dp[x][0].second * 1ll * dp[u][1].second % mod * inverse(dp[u][0].second) % mod;
        if (cost < dp[x][1].first) {
            dp[x][1].first = cost;
            dp[x][1].second = way;
        } else if (cost == dp[x][1].first) {
            dp[x][1].second += way;
            dp[x][1].second %= mod;
        }
    }

    dp[x][0].first += f;
    dp[x][1].first += 1 - f;
}

pair<int, int> solve_tree(int root) {
    dfs(root, -1, 1);
    return dp[root][1];
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < 2 * n; ++i) {
            g[i].clear();
            fa[i] = i;
            sz[i] = 1;
            ed[i] = 0;
            vt[i].clear();
            inq[i] = false;
            cyc[i] = false;
        }

        vector<pair<int, int>> edge;
        for (int i = 0; i < n; ++i) {
            int x, y; scanf("%d%d", &x, &y);
            --x, --y;
            edge.emplace_back(x, y);
            merge(x, y);
            g[x].emplace_back(y, i);
            g[y].emplace_back(x, i);

            fi[i] = x;
            se[i] = y;
        }

        for (int i = 0; i < n; ++i) {
            int x = edge[i].first;
            ++ed[find(x)];
        }

        for (int i = 0; i < 2 * n; ++i) 
            vt[find(i)].push_back(i);

        bool imp = false;
        int ans1 = 0, ans2 = 1;

        for (int i = 0; i < 2 * n; ++i) {
            if (find(i) != i) continue;
            if (ed[i] != sz[i] && ed[i] != sz[i] - 1) {
                imp = true;
                break;
            }

            pair<int, int> p;
            if (ed[i] == sz[i]) p = solve_cycle(i);
            else p = solve_tree(i);

            ans1 += p.first;
            ans2 = ans2 * 1ll * p.second % mod;
        }

        if (imp) printf("-1 -1\n");
        else printf("%d %d\n", ans1, ans2);
    }

    return 0;
}
