#include <bits/stdc++.h>
using namespace std;

const int kN = 20000;

map<int, int> city_id_inverse;

struct Dinic {
    struct Edge {
        int to, cap, rev;
        Edge(int a, int b, int c) : to(a), cap(b), rev(c) {}
    };

    vector<Edge> g[kN];
    int lev[kN], qu[kN];

    void AddEdge(int a, int b, int c) {
        g[a].emplace_back(b, c, (int)g[b].size() - 0);
        g[b].emplace_back(a, 0, (int)g[a].size() - 1);
    }

    bool Bfs(int s, int t) {
        memset(lev, -1, sizeof(lev));
        lev[s] = 0;
        int ql = 0, qr = 0;
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

    int Dfs(int x, int t, int flow) {
        if (x == t) return flow;
        int res = 0;
        for (Edge &e : g[x]) {
            if (lev[e.to] == lev[x] + 1 && e.cap > 0) {
                int fl = Dfs(e.to, t, min(flow - res, e.cap));
                e.cap -= fl;
                g[e.to][e.rev].cap += fl;
                res += fl;
            }
        }
        if (res == 0) lev[x] = -1;
        return res;
    }

    int operator()(int s, int t) {
        int res = 0;
        for (; Bfs(s, t); res += Dfs(s, t, 1e9));
        return res;
    }

    int used_edge_id[kN];
    int GetConnectingCity(int x) {
        for (int &i = used_edge_id[x]; i < (int)g[x].size(); ++i) {
            if (city_id_inverse.count(g[x][i].to) && g[x][i].cap) {
                g[x][i].cap = 0;
                return city_id_inverse[g[x][i].to];
            }
        }
        return -1;
    }
} fl;


int to[2005];
vector<int> okset[2005];
vector<int> g[2005];
vector<int> loop;
bitset<2005> vis;
bitset<2005> inloop;

bool dfs(int now, int pa) {
    // cerr << "dfs = " << now << endl;
    if (vis[now]) {
        loop.push_back(now);
        inloop[now] = 1;
        return true;
    }
    vis[now] = 1;
    for (int i : g[now]) if (i != pa) {
        int r = dfs(i, now);
        if (r) {
            if (now == loop[0]) return false;
            else {
                loop.push_back(now);
                inloop[now] = 1;
                return true;
            }
        } else if (loop.size()) return false;
    }
    return false;
}

int nn;
int city_edge_id[2005];
int oworker_type[2005];
int worker_type[2005];
int worker_type_id[22005];
vector<int> worker_type_worker[22005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<int> all_worker_type;
    for (int i = 1; i <= n; ++i) {
        int u; cin >> u; to[i] = u;
        int t; cin >> t; okset[i].resize(t);
        for (int j = 0; j < t; ++j) cin >> okset[i][j];
        for (int j = 0; j < t; ++j) all_worker_type.push_back(okset[i][j]);
        g[i].push_back(u);
        g[u].push_back(i);
    }
    for (int i = 1; i <= k; ++i) cin >> worker_type[i];
    for (int i = 1; i <= k; ++i) oworker_type[i] = worker_type[i];
    for (int i = 1; i <= k; ++i) all_worker_type.push_back(worker_type[i]);

    sort(all_worker_type.begin(), all_worker_type.end());
    all_worker_type.resize(unique(all_worker_type.begin(), all_worker_type.end()) - all_worker_type.begin());
    auto get_new_id = [&] (int v) {
        return upper_bound(all_worker_type.begin(), all_worker_type.end(), v) - all_worker_type.begin();
    };


    for (int i = 1; i <= n; ++i) {
        int t = okset[i].size();
        for (int j = 0; j < t; ++j) okset[i][j] = get_new_id(okset[i][j]);
    }
    for (int i = 1; i <= k; ++i) worker_type[i] = get_new_id(worker_type[i]);
    for (int i = 1; i <= k; ++i) worker_type_worker[worker_type[i]].push_back(i);

    dfs(1, 0);

    int S = nn++, T = nn++;
    int s = nn++, t = nn++;
    int LOOP = nn++;
    for (int i = 1; i <= n; ++i) city_edge_id[i] = nn++;
    for (int i = 1; i <= n; ++i) city_id_inverse[city_edge_id[i]] = i;
    // for (int i = 1; i <= n; ++i) city_edge_id[i][0] = nn++, city_edge_id[i][1] = nn++;
    for (int i = 1; i <= (int)all_worker_type.size(); ++i) worker_type_id[i] = nn++;

    fl.AddEdge(s, LOOP, 1);
    for (int i : loop) fl.AddEdge(LOOP, city_edge_id[i], 1);
    for (int i = 1; i <= n; ++i) if (!inloop[i]) fl.AddEdge(s, city_edge_id[i], 0);
    for (int i = 1; i <= n; ++i) {
        int t = okset[i].size();
        for (int j = 0; j < t; ++j) fl.AddEdge(city_edge_id[i], worker_type_id[okset[i][j]], 1);
    }
    for (int i = 1; i <= (int)all_worker_type.size(); ++i) fl.AddEdge(worker_type_id[i], t, worker_type_worker[i].size());

    fl.AddEdge(S, LOOP, (int)loop.size() - 1);
    fl.AddEdge(s, T, n - 1);
    for (int i = 1; i <= n; ++i) if (!inloop[i]) fl.AddEdge(S, city_edge_id[i], 1);

    fl.AddEdge(t, s, 1e9);

    // cerr << "after addedge" << endl;

    int f = fl(S, T);
    if (f != n - 1) {
        cout << -1 << endl;
        exit(0);
    }

    int ff = fl(s, t);

    // cerr << "after flow" << endl;

    for (int i = 1; i <= k; ++i) {
        int type = worker_type[i];
        int city_edge = fl.GetConnectingCity(worker_type_id[type]);
        if (city_edge == -1) cout << "0 0" << '\n';
        else {
            cout << city_edge << ' ' << to[city_edge] << '\n';
        }
    }
}
