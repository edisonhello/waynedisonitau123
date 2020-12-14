#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cap, rev;
    Edge(int t, int c, int r) : to(t), cap(c), rev(r) {}
};

int Flow(vector<vector<Edge>> &g, int s, int t) {
    int n = g.size(), res = 0;
    vector<int> lev(n, -1), iter(n);
    vector<int> que;
    while (true) {
        que.resize(1); que[0] = s;
        fill(lev.begin(), lev.end(), -1);
        fill(iter.begin(), iter.end(), 0);
        lev[s] = 0;
        for (int it = 0; it < que.size(); ++it) {
            int x = que[it];
            for (Edge &e : g[x]) {
                if (e.cap > 0 && lev[e.to] == -1) {
                    lev[e.to] = lev[x] + 1;
                    que.push_back(e.to);
                }
            }
        }
        if (lev[t] == -1) break;
        auto Dfs = [&] (auto dfs, int x, int f = 1000000000) {
            if (x == t) return f;
            int res = 0;
            for (int &it = iter[x]; it < g[x].size(); ++it) {
                Edge &e = g[x][it];
                if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
                    int p = dfs(dfs, e.to, min(f - res, e.cap));
                    res += p;
                    e.cap -= p;
                    g[e.to][e.rev].cap += p;
                }
            }
            if (res == 0) lev[x] = -1;
            return res;
        };
        res += Dfs(Dfs, s);
    }
    return res;
}

#define gch getchar
int rit() {
    int x = 0;
    char c;
    while ((c = gch()), c < '0' || c > '9');
    x = c & 15;
    while ((c = gch()), c >= '0' && c <= '9') x = x * 10 + (c & 15);
    return x;
}

int main() {
    vector<int> sumdigit(100000);

    for (int i = 0; i < 100000; ++i) {
        int ii = i;
        int c = 0;
        while (ii) {
            c += ii % 10;
            ii /= 10;
        }
        sumdigit[i] = c;
    }

    int t = rit(); while (t--) {
        int m = rit(), n = rit();
        int s = rit();

        int mx = 1;
        for (int i = 0; i < m; ++i) mx *= 10;

        vector<int> ban(mx + 2);


        while (n--) {
            int v = rit();
            ban[v] = 1;
        }

        vector<vector<Edge>> g(mx + 2);

        vector<int> pogged(mx + 2, 0);

        auto addedge_ = [&] (int u, int v) {
            g[u].push_back(Edge{v, 1, (int)g[v].size() - 0});
            g[v].push_back(Edge{u, 0, (int)g[u].size() - 1});
        };

        auto addedge = [&] (int u, int v, int r = 0) {
            int dsum = sumdigit[u];
            if ((dsum & 1) ^ r) swap(u, v);
            addedge_(u, v);
        };

        ban[s] = 1;

        for (int i = 0; i < mx; ++i) {
            if (ban[i]) continue;
            for (int z = 0, zb = 1; z < m; ++z, zb *= 10) {
                int ii = i % (zb * 10) / zb;
                int to = i + zb;
                if (ii == 9) { to = i - zb * 9; }

                if (!ban[to]) {
                    if (!pogged[i] && !pogged[to]) {
                        pogged[i] = pogged[to] = 1;
                        addedge(i, to, 1);
                    } else {
                        addedge(i, to);
                    }
                }
            }
        }

        for (int i = 0; i < mx; ++i) {
            if (ban[i]) continue;
            if (sumdigit[i] & 1) {
                if (pogged[i]) addedge_(mx + 1, i);
                else addedge_(i, mx + 1);
            } else {
                if (pogged[i]) addedge_(i, mx);
                else addedge_(mx, i);
            }
        }

        int res = Flow(g, mx, mx + 1);

        ban[s] = 0;

        for (int z = 0, zb = 1; z < m; ++z, zb *= 10) {
            int ii = s % (zb * 10) / zb;
            if (ii == 9) {
                if (!ban[s - zb * 9]) addedge(s, s - zb * 9);
            } else {
                if (!ban[s + zb]) addedge(s, s + zb);
            }

            if (ii == 0) {
                if (!ban[s + zb * 9]) addedge(s, s + zb * 9);
            } else {
                if (!ban[s - zb]) addedge(s, s - zb);
            }
        }

        if (sumdigit[s] & 1) {
            addedge_(s, mx + 1);
        } else {
            addedge_(mx, s);
        }

        int res2 = Flow(g, mx, mx + 1);

        if (res2) {
            cout << "Alice" << '\n';
        } else {
            cout << "Bob" << '\n';
        }
    }
}

