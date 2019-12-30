#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
 
struct Edge {
    int t, u, v, w;
};
 
int n;
int djs[100005];
int dirt[100005];
int sz[100005];
int save[100005];
cc_hash_table<int, int> gp[100005];
 
int F(int x) { 
    if (x == djs[x]) return x;
    // return F(djs[x]);
    int fa = F(djs[x]);
    // if (dirt[djs[x]] == 1 && dirt[x] == 0) {
    //     cerr << "Find dirts " << x << ", djs[x] = " << djs[x] << ", top = " << fa << endl;
    // }
    dirt[x] |= dirt[djs[x]];
    return djs[x] = fa;
}
    
inline void AddEdge(int u, int v) {
    u = F(u);
    v = F(v);
    if (u == v) return;
    dirt[u] = dirt[v] = 1;
    gp[save[u]][save[v]] = 1;
    gp[save[v]][save[u]] = 1;
}
 
vector<int> wait_dirt;
int now_w;
 
inline void ProcessDirt() {
    // cerr << __func__ << endl;
    for (int i : wait_dirt) if (gp[save[F(i)]].size()) dirt[F(i)] = 1;
    wait_dirt.clear();
}
 
bool CheckDirt(int x) {
    if (x == djs[x]) return dirt[x];
    return dirt[x] | CheckDirt(djs[x]);
}
 
void Merge(int u, int v) {
    u = F(u);
    v = F(v);
    assert(u != v);
    gp[save[u]].erase(save[v]);
    gp[save[v]].erase(save[u]);
 
    if (CheckDirt(u) && !CheckDirt(v)) swap(u, v);
 
    djs[v] = u;
    sz[u] += sz[v];
 
    wait_dirt.push_back(u);
 
    if (gp[save[u]].size() < gp[save[v]].size()) {
        for (auto &p : gp[save[u]]) {
            gp[save[p.first]].erase(save[u]);
            gp[save[p.first]][save[v]] = 1;
            gp[save[v]][save[p.first]] = 1;
        }
        gp[save[u]].clear();
        save[u] = save[v];
    } else {
        for (auto &p : gp[save[v]]) {
            gp[save[p.first]].erase(save[v]);
            gp[save[p.first]][save[u]] = 1;
            gp[save[u]][save[p.first]] = 1;
        }
        // gp[save[v]].clear();
    }
}

inline int Readchar() {
    constexpr int kB = 131072;
    static char buf[kB];
    static char *p = buf, *e = buf;
    if (p == e) {
        e = buf + fread(buf, 1, kB, stdin);
        p = buf;
    }
    return *p++;
}

inline int ReadInt() {
    int x = 0, c = 0;
    while (c = Readchar(), !isdigit(c));
    x = c & 15;
    while (c = Readchar(), isdigit(c)) x = x * 10 + (c & 15);
    return x;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int m; n = ReadInt(), m = ReadInt();
    vector<Edge> g;
    while (m--) {
        int t, u, v, w; t = ReadInt(), u = ReadInt(), v = ReadInt(), w = ReadInt();
        g.push_back(Edge{t, u, v, w});
    }
    sort(g.begin(), g.end(), [] (const Edge &a, const Edge &b) {
        if (a.w == b.w) return a.t > b.t;
        return a.w > b.w;
    });
    for (int i = 1; i <= n; ++i) djs[i] = i, sz[i] = 1, save[i] = i;
    for (Edge e : g) {
        if (now_w != e.w) {
            ProcessDirt();
            // for (int i = 1; i <= n; ++i) cerr << "i " << i << " djs[i] " << djs[i] << " CheckDirt(i) " << CheckDirt(i) << endl;
        }
        now_w = e.w;
 
        // cerr << "e: " << e.t << ' ' << e.u << ' ' << e.v << ' ' << e.w << endl;
        if (e.t == 1) 
            Merge(e.u, e.v);
        else 
            AddEdge(e.u, e.v);
 
        // for (int i = 1; i <= n; ++i) {
        //     cerr << "gp[" << i << "] = ";
        //     for (int j : gp[i]) cerr << j << " ";
        //     cerr << ", dirt = " << dirt[i] << ", save[i] = " << save[i] << " djs = " << djs[i] << endl;
        // }
    }
    ProcessDirt();
    // for (int i = 1; i <= n; ++i) cerr << "i " << i << " djs[i] " << djs[i] << " CheckDirt(i) " << CheckDirt(i) << endl;
 
    vector<int> ans;
    for (int i = 1; i <= n; ++i) if (!CheckDirt(i)) ans.push_back(i);
    cout << ans.size() << endl;
    for (int i : ans) cout << i << ' ';
    cout << endl;
}
