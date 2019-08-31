#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 5;
const int inf = 1e9 + 5;
int p[3][maxn], tab[maxn];

/* struct MinCost {
   static const int maxn = 10000 + 5;
   struct Edge {
   int to, cap, w, rev;
   Edge(int a, int b, int c, int d) : to(a), cap(b), w(c), rev(d) {}
   };

   vector<Edge> g[maxn];
   int d[maxn], p[maxn], ed[maxn];
   bool v[maxn];

   void AddEdge(int a, int b, int c, int d) {
   g[a].emplace_back(b, c, +d, (int)g[b].size() - 0);
   g[b].emplace_back(a, 0, -d, (int)g[a].size() - 1);
   }

   bool Dijkstra(int s, int t, int &f, int &c) {
   for (int i = 0; i < maxn; ++i) {
   d[i] = -inf;
   ed[i] = p[i] = -1;
   v[i] = false;
   }

   priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
   d[s] = 0;
   pq.emplace(0, s);

   while (!pq.empty()) {
   int z, x; tie(z, x) = pq.top();
   pq.pop();
   if (v[x]) continue;
   v[x] = true;
   for (int i = 0; i < (int)g[x].size(); ++i) {
   Edge &e = g[x][i];
   if (e.cap > 0 && d[e.to] < d[x] + e.w) {
   p[e.to] = x;
   ed[e.to] = i;
   d[e.to] = d[x] + e.w;
   pq.emplace(d[e.to], e.to);
   }
   }
   }
   if (d[t] == -inf) return false;
   int dlt = inf;
   for (int x = t; x != s; x = p[x]) dlt = min(dlt, g[p[x]][ed[x]].cap);
   for (int x = t; x != s; x = p[x]) {
   Edge &e = g[p[x]][ed[x]];
   e.cap -= dlt;
   g[e.to][e.rev].cap += dlt;
   }
   f += dlt;
   c += d[t] * dlt;
// printf("d[t] = %d\n", d[t]);
return true;
}

pair<int, int> operator()(int s, int t) {
int f = 0, c = 0;
while (Dijkstra(s, t, f, c));
return make_pair(f, c);
}
}; */

int w[maxn][maxn], lx[maxn], ly[maxn], slack[maxn], match[maxn];
bool vx[maxn], vy[maxn];

bool dfs(int x, int n) {
    vx[x] = true;
    for (int i = 0; i < n; ++i) {
        if (vy[i]) continue;
        if (lx[x] + ly[i] > w[x][i]) {
            slack[i] = min(slack[i], lx[x] + ly[i] - w[x][i]);
            continue;
        }
        vy[i] = true;
        if (match[i] == -1 || dfs(match[i], n)) {
            match[i] = x;
            return true;
        }
    }
    return false;
}

int solve(int n) {
    fill_n(match, n, -1);
    fill_n(lx, n, -inf);
    fill_n(ly, n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            lx[i] = max(lx[i], w[i][j]);
    }
    for (int i = 0; i < n; ++i) {
        fill_n(slack, n, inf);
        while (true) {
            fill_n(vx, n, false);
            fill_n(vy, n, false);
            if (dfs(i, n)) break;
            int dlt = inf;
            for (int j = 0; j < n; ++j) {
                if (!vy[j]) dlt = min(dlt, slack[j]);
            }
            for (int j = 0; j < n; ++j) {
                if (vx[j]) lx[j] -= dlt;
                if (vy[j]) ly[j] += dlt;
                else slack[j] -= dlt;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++i) res += w[match[i]][i];
    return res;
}

int main() {
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            int x; scanf("%d", &x);
            p[i][x - 1] = j;
        }
    }

    if (k == 2) {
        int ans = 0;
        for (int i = 0; i < n; ++i) ans += min(8, abs(p[0][i] - p[1][i]));
        printf("%d\n", ans);
        return 0;
    }

    // MinCost flow;

    // int s = n + n, t = n + n + 1;
    /* for (int i = 0; i < n; ++i) flow.AddEdge(s, i, 1, 0);
       for (int i = 0; i < n; ++i) flow.AddEdge(i + n, t, 1, 0); */
    for (int i = 0; i < n; ++i) {
        for (int t = 0; t < 3; ++t) {
            for (int k = max(0, p[t][i] - 8); k <= min(n - 1, p[t][i] + 8); ++k) {
                int cost = min(8, abs(p[0][i] - k)) + min(8, abs(p[1][i] - k)) + min(8, abs(p[2][i] - k));
                w[i][k] = max(w[i][k], 24 - cost);
            }
        }
    }
    // int f, c; tie(f, c) = flow(s, t);
    // printf("f = %d c = %d\n", f, c);
    // printf("cost = %d\n", flow(s, t).second);
    int c = solve(n);
    printf("%d\n", 24 * n - c);
}
