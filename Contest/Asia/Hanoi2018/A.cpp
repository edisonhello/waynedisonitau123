#include <bits/stdc++.h>
using namespace std;

int in[105][105], out[105][105];
int itp[40005][2];
int nid;

const int maxn = 4e4;

struct mincost {
    struct edge {
        int dest, cap, w, rev, ocap;
        edge(int a, int b, int c, int d): dest(a), cap(b), w(c), rev(d), ocap(b) {}
    };
    vector<edge> g[maxn];
    int d[maxn], p[maxn], ed[maxn];
    bool inq[maxn];
    void init(int X) {
        for (int i = 0; i <= X; ++i) g[i].clear();
    }
    void add_edge(int a, int b, int c, int d) {
        // cout << "add_edge " << a << " to " << b << " cap " << c << " cost " << d << endl;
        g[a].emplace_back(b, c, d, g[b].size());
        g[b].emplace_back(a, 0, -d, g[a].size() - 1);
    }
    bool spfa(int s, int t, int &f, int &c, int X) {
        for (int i = 0; i <= X; ++i) {
            d[i] = 1e9;
            p[i] = ed[i] = -1;
            inq[i] = 0;
        }
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (q.size()) {
            int x = q.front(); q.pop();
            inq[x] = true;
            for (int i = 0; i < g[x].size(); ++i) {
                edge &e = g[x][i];
                if (e.cap > 0 && d[e.dest] > d[x] + e.w) {
                    d[e.dest] = d[x] + e.w;
                    p[e.dest] = x;
                    ed[e.dest] = i;
                    if (!inq[e.dest]) q.push(e.dest), inq[e.dest] = 1;
                }
            }
        }
        if (d[t] >= 5e8) return false;
        int dlt = 1e9;
        for (int x = t; x != s; x = p[x]) dlt = min(dlt, g[p[x]][ed[x]].cap);
        for (int x = t; x != s; x = p[x]) {
            edge &e = g[p[x]][ed[x]];
            e.cap -= dlt;
            g[e.dest][e.rev].cap += dlt;
        }
        f += dlt; c += d[t] * dlt;
        return true;
    }
    pair<int, int> operator() (int s, int t, int X) {
        int f = 0, c = 0;
        while (spfa(s, t, f, c, X));
        return make_pair(f, c);
    }
    string trace(int t, int s) {
        vector<int> pids = {t};
        while (t != s) {
            for (auto &e : g[t]) {
                if (e.dest == pids.back()) continue;
                if (e.cap > e.ocap) {
                    pids.push_back(e.dest);
                    t = e.dest;
                    break;
                }
            }
        }
        reverse(pids.begin(), pids.end());
        // cout << "trace" << endl;
        // for (auto &p : pids) cout << p << ' ';
        // cout << endl;
        vector<pair<int, int>> poss;
        for (int i : pids) {
            poss.emplace_back(itp[i][0], itp[i][1]);
        }
        poss.resize(unique(poss.begin(), poss.end()) - poss.begin());
        string ans;
        // cout << "trace" << endl;
        // for (auto &p : poss) cout << "(" << p.first << ", " << p.second << ")";
        // cout << endl;
        for (int i = 1; i < (int)poss.size(); ++i) {
            if (poss[i].first == poss[i - 1].first + 1) ans += 'U';
            else if (poss[i].first == poss[i - 1].first - 1) ans += 'D';
            else if (poss[i].second == poss[i - 1].second + 1) ans += 'R';
            else if (poss[i].second == poss[i - 1].second - 1) ans += 'L';
            else assert(0);
        }
        return ans;
    }
} f;


int main() {
    // ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; while (scanf("%d%d", &n, &m) != EOF) {
        if (n == 0 && m == 0) break;

        int bx, by;
        int cx, cy;
        int gx, gy;
        int ux, uy;
        scanf("%d%d%d%d%d%d%d%d", &bx, &by, &cx, &cy, &gx, &gy, &ux, &uy);

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                in[i][j] = ++nid;
                itp[nid][0] = i, itp[nid][1] = j;
                // cout << "in " << i << " " << j << " id = " << nid << endl;
                out[i][j] = ++nid;
                itp[nid][0] = i, itp[nid][1] = j;
                // cout << "out " << i << " " << j << " id = " << nid << endl;
            }
        }

        // cout << "bx = " << bx << " by = " << by << " out b = " << out[bx][by] << endl;
        // cout << "gx = " << gx << " gy = " << gy << " out g = " << out[gx][gy] << endl;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (i != ux || j != uy)
                    f.add_edge(in[i][j], out[i][j], 1, 0);
                if (i > 1) 
                    f.add_edge(out[i - 1][j], in[i][j], 1, 1), 
                    f.add_edge(out[i][j], in[i - 1][j], 1, 1);
                if (j > 1) 
                    f.add_edge(out[i][j - 1], in[i][j], 1, 1), 
                    f.add_edge(out[i][j], in[i][j - 1], 1, 1);
            }
        }

        int s = ++nid;
        int t = ++nid;

        // cout << "bx = " << bx << " by = " << by << " out b = " << out[bx][by] << endl;
        // cout << "gx = " << gx << " gy = " << gy << " out g = " << out[gx][gy] << endl;
        f.add_edge(s, out[cx][cy], 2, 0);
        f.add_edge(out[bx][by], t, 1, 0);
        f.add_edge(out[gx][gy], t, 1, 0);

        // cout << "flow! " << endl;
        auto res = f(s, t, n * m * 2 + 10);
        // cout << "res = " << res.first << " " << res.second << endl;

        if (res.first != 2) cout << "NO" << '\n';
        else {
            cout << "YES" << '\n';
            string s1 = f.trace(out[bx][by], out[cx][cy]);
            string s2 = f.trace(out[gx][gy], out[cx][cy]);
            string is1;
            for (char c : s1) {
                if (c == 'L') is1 += 'R';
                else if (c == 'R') is1 += 'L';
                else if (c == 'U') is1 += 'D';
                else if (c == 'D') is1 += 'U';
                else assert(0);
            }
            reverse(is1.begin(), is1.end());
            cout << is1 << s2 << '\n';
        }
        // for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) in[i][j] = out[i][j] = 0;
        // for (int i = 1; i <= n * m; ++i) itp[i][0] = itp[i][1] = 0;
        nid = 0;
        f.init(n * m * 2 + 10);
    }
}
