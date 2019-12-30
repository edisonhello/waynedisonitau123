#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int t, u, v, w;
};

int djs[100005];
int savedjs[100005];
int dirt[100005];
int sz[100005];
// int save[100005];
unordered_set<int> gp[100005];

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

int saveF(int x) {
    return x == savedjs[x] ? x : savedjs[x] = saveF(savedjs[x]);
}
void saveU(int x, int y) {
    savedjs[saveF(y)] = saveF(x);
}
    
void AddEdge(int u, int v) {
    u = F(u);
    v = F(v);
    if (u == v) return;
    dirt[u] = dirt[v] = 1;
    gp[saveF(u)].insert(saveF(v));
    gp[saveF(v)].insert(saveF(u));
}

vector<int> wait_dirt;
int now_w;

void ProcessDirt() {
    // cerr << __func__ << endl;
    for (int i : wait_dirt) for (int j : gp[saveF(F(i))]) {
        if (F(j) != F(i)) dirt[F(i)] = 1;
    }
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
    gp[saveF(u)].erase(saveF(v));
    gp[saveF(v)].erase(saveF(u));

    if (CheckDirt(u) && !CheckDirt(v)) swap(u, v);

    djs[v] = u;
    sz[u] += sz[v];

    wait_dirt.push_back(u);

    if (gp[saveF(u)].size() < gp[saveF(v)].size()) {
        cerr << "merging " << u << " to " << v << ", head is " << u << endl;
        for (int i : gp[saveF(u)]) {
            if (saveF(i) != saveF(v)) gp[saveF(v)].insert(saveF(i));
        }
        gp[saveF(u)].clear();
        saveU(v, u);
    } else {
        cerr << "merging " << v << " to " << u << ", head is " << u << endl;
        for (int i : gp[saveF(v)]) {
            if (saveF(i) != saveF(u)) gp[saveF(u)].insert(saveF(i));
        }
        gp[saveF(v)].clear();
        saveU(u, v);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<Edge> g;
    while (m--) {
        int t, u, v, w; cin >> t >> u >> v >> w;
        g.push_back(Edge{t, u, v, w});
    }
    sort(g.begin(), g.end(), [] (const Edge &a, const Edge &b) {
        if (a.w == b.w) return a.t > b.t;
        return a.w > b.w;
    });
    for (int i = 1; i <= n; ++i) djs[i] = i;
    for (int i = 1; i <= n; ++i) sz[i] = 1;
    // for (int i = 1; i <= n; ++i) save[i] = i;
    for (int i = 1; i <= n; ++i) savedjs[i] = i;
    for (Edge e : g) {
        if (now_w != e.w) {
            ProcessDirt();
            // for (int i = 1; i <= n; ++i) cerr << "i " << i << " djs[i] " << djs[i] << " CheckDirt(i) " << CheckDirt(i) << endl;
        }
        now_w = e.w;

        cerr << "e: " << e.t << ' ' << e.u << ' ' << e.v << ' ' << e.w << endl;
        if (e.t == 1) 
            Merge(e.u, e.v);
        else 
            AddEdge(e.u, e.v);

        for (int i = 1; i <= n; ++i) {
            cerr << "gp[" << i << "] = ";
            for (int j : gp[i]) cerr << j << " ";
            cerr << ", dirt = " << dirt[i] << ", savedjs[i] = " << savedjs[i] << " djs = " << djs[i] << endl;
        }
    }
    ProcessDirt();
    // for (int i = 1; i <= n; ++i) cerr << "i " << i << " djs[i] " << djs[i] << " CheckDirt(i) " << CheckDirt(i) << endl;

    set<int> ans;
    for (int i = 1; i <= n; ++i) if (!CheckDirt(i)) ans.insert(i);
    cout << ans.size() << endl;
    for (int i : ans) cout << i << ' ';
    cout << endl;
}
