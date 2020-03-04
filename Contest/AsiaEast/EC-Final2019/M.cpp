#include <bits/stdc++.h>
using namespace std;
 
const long long kInf = 1'000'000'000'000'000'000;
const int kN = 100;
 
struct Dinic {
    struct Edge {
        int to, cap, rev;
        Edge(int a, int b, int c) : to(a), cap(b), rev(c) {}
    };
 
    vector<Edge> g[kN];
    int lev[kN];
 
    void AddEdge(int a, int b, int c) {
        g[a].emplace_back(b, c, (int)g[b].size() - 0);
        g[b].emplace_back(a, 0, (int)g[a].size() - 1);
    }
 
    bool Bfs(int s, int t) {
        memset(lev, -1, sizeof(lev));
        lev[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (Edge &e : g[x]) {
                if (lev[e.to] == -1 && e.cap > 0) {
                    lev[e.to] = lev[x] + 1;
                    q.push(e.to);
                }
            }
        }
        return lev[t] != -1;
    }
 
    long long Dfs(int x, int t, long long flow) {
        if (x == t) return flow;
        long long res = 0;
        for (Edge &e : g[x]) {
            if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
                long long f = Dfs(e.to, t, min(flow - res, 1LL * e.cap));
                res += f;
                e.cap -= f;
                g[e.to][e.rev].cap += f;
            }
        }
        if (!res) lev[x] = -1;
        return res;
    }
 
    long long operator()(int s, int t) {
        long long res = 0;
        for (; Bfs(s, t); res += Dfs(s, t, kInf));
        return res;
    }
};
 
vector<int> g[100005];
int djs[100005];
vector<int> mem[100005];
 
int F(int x) {
    return djs[x] == x ? x : djs[x] = F(djs[x]);
}
void U(int x, int y) {
    djs[F(x)] = F(y);
}
 
long long a[100005], b[100005];
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) djs[i] = i;
    set<int> s;
    for (int i = 2; i <= n; ++i) {
        long long now = i;
        for (int k = 2; ; ++k) {
            now *= i;
            if (now > n) break;
            U(i, now);
        }
    }
 
    for (int i = 1; i <= n; ++i) {
        mem[F(i)].push_back(i);
    }
 
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        auto &v = mem[i];
        int sz = v.size();
        // cout << "i = " << i << " v = ";
        // for (int i : v) cout << i << ' '; cout << endl;
        long long mx = 0;
        for (int z = 0; z < (1 << sz); ++z) {
            long long now = 0;
            for (int y = 0; y < sz; ++y) if ((1 << y) & z) now += a[v[y]];
            for (int i = 0; i < sz; ++i) if (((1 << i) & z) && v[i] >= 2) {
                long long ii = v[i];
                for (int k = 2; ; ++k) {
                    ii *= v[i];
                    if (ii > n) break;
                    for (int j = 0; j < sz; ++j) if (v[j] == ii && ((1 << j) & z) && v[j] >= 2) {
                        now -= b[v[j]];
                        break;
                    }
                }
            }
            mx = max(mx, now);
        }
        ans += mx;
    }
 
    cout << ans << endl;
 
    return 0;
}
