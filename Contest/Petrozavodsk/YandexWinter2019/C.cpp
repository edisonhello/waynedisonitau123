#include <bits/stdc++.h>
using namespace std;

const int maxn = 25000;

struct Dinic {
    struct Edge {
        int to, cap, rev;
        Edge(int a, int b, int c) : to(a), cap(b), rev(c) {}
    };

    vector<Edge> g[maxn];
    int qu[maxn], lev[maxn], ql, qr;

    void add_edge(int a, int b, int c) {
        g[a].emplace_back(b, c, (int)g[b].size() - 0);
        g[b].emplace_back(a, 0, (int)g[a].size() - 1);
    }

    bool bfs(int s, int t) {
        memset(lev, -1, sizeof(lev));
        lev[s] = 0;
        ql = qr = 0;
        qu[qr++] = s;
        while (ql < qr) {
            int x = qu[ql++];
            for (Edge &e : g[x]) {
                if (lev[e.to] == -1 && e.cap > 0) {
                    lev[e.to] = lev[x] + 1;
                    qu[qr++] = e.to;
                }
            }
        }
        return lev[t] != -1;
    }

    int dfs(int x, int t, int flow) {
        if (x == t) return flow;
        int res = 0;
        for (Edge &e : g[x]) {
            if (e.cap > 0 && lev[e.to] == lev[x] + 1) {
                int f = dfs(e.to, t, min(e.cap, flow - res));
                res += f;
                e.cap -= f;
                g[e.to][e.rev].cap += f;
            }
        }
        if (res == 0) lev[x] = -1;
        return res;
    }

    int operator()(int s, int t) {
        int flow = 0;
        for (; bfs(s, t); flow += dfs(s, t, 1e9));
        return flow;
    }
} flow;

pair<int, int> isl[25000], ils[25000];
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    int nn = 0;
    int s = nn++, t = nn++;
    vector<int> pid(n + 1), sid(m + 1);
    for (int i = 1; i <= n; ++i) pid[i] = nn++;
    for (int i = 1; i <= m; ++i) sid[i] = nn++;

    for (int i = 1; i <= n; ++i) flow.add_edge(s, pid[i], 1000000);
    for (int i = 1; i <= m; ++i) flow.add_edge(sid[i], t, 1000000);

    map<tuple<int, int, int>, int> sgs;
    map<pair<int, int>, int> sl, ls;

    for (int i = 1; i <= k; ++i) {
        int a, b, c; cin >> a >> b >> c;
        sgs[make_tuple(a, b, c)] = i;
        if (!sl.count(make_pair(a, c))) 
            sl[make_pair(a, c)] = nn, isl[nn] = make_pair(a, c), flow.add_edge(pid[a], sl[make_pair(a, c)], 1), ++nn;
        if (!ls.count(make_pair(c, b))) 
            ls[make_pair(c, b)] = nn, ils[nn] = make_pair(c, b), flow.add_edge(ls[make_pair(c, b)], sid[b], 1), ++nn;
        flow.add_edge(sl[make_pair(a, c)], ls[make_pair(c, b)], 1);
    }

    // cout << "sl = " << endl;;
    // for (auto &p : sl) cout << "(" << p.first.first << "," << p.first.second << ") = " << p.second << endl;
    // cout << "ls = " << endl;;
    // for (auto &p : ls) cout << "(" << p.first.first << "," << p.first.second << ") = " << p.second << endl;

    int S = nn++, T = nn++;
    flow.add_edge(s, T, n);
    flow.add_edge(S, t, m);
    for (int i = 1; i <= n; ++i) flow.add_edge(S, pid[i], 1);
    for (int i = 1; i <= m; ++i) flow.add_edge(sid[i], T, 1);

    flow.add_edge(t, s, 100000000);
    int sumin = n + m;
    int f = flow(S, T);
    if (f != sumin) {
        cout << "-1" << '\n';
    } else {
        flow(s, t);
        vector<int> song;
        for (auto &pp : sl) {
            int i = pp.second;
            for (auto &e : flow.g[i]) {
                if (ils[e.to].first != 0 && e.cap == 0) {
                    song.push_back(sgs[make_tuple(pp.first.first, ils[e.to].second, pp.first.second)]);
                }
            }
        }
        cout << song.size() << endl;
        for (int i : song) cout << i << ' ';
        cout << endl;
    }
}
