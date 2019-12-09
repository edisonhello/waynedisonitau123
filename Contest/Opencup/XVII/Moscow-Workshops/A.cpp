#include <bits/stdc++.h>
using namespace std;

int djs[1005];
vector<int> G[1005], cG[1005];
int dis[1005];
bool vis[1005];
vector<int> cur;
int sz[1005], mxsz[1005], mxch[1005];

int F(int x) { return x == djs[x] ? x : djs[x] = F(djs[x]); }
void U(int x, int y) { djs[F(x)] = F(y); }

void dfs(int now, int pa, vector<int> *G) {
    for (int i : G[now]) if (i != pa) {
        dis[i] = dis[now] + 1;
        dfs(i, now, G);
    }
}

void cdfs2(int now, int pa) {
    cur.push_back(now);
    sz[now] = 1;
    mxsz[now] = 0;
    for (int i : G[now]) if (i != pa && !vis[i]) {
        cdfs2(i, now);
        sz[now] += sz[i];
        if (sz[i] > sz[mxsz[now]]) mxsz[now] = i;
    }
}

int cdfs(int now, int pa) {
    cur.clear();
    cdfs2(now, pa);
    int cen = cur[0], val = INT_MAX;
    for (int i : cur) if (max(sz[mxsz[i]], (int)cur.size() - sz[i]) <= val) {
        if (max(sz[mxsz[i]], (int)cur.size() - sz[i]) == val) {
            if (i < cen) cen = i;
        } else {
            val = max(sz[mxsz[i]], (int)cur.size() - sz[i]);
            cen = i;
        }
    }
    vis[cen] = 1;
    for (int i : G[cen]) if (!vis[i]) {
        int z = cdfs(i, cen);
        cG[cen].push_back(z);
        cG[z].push_back(cen);
    }
    return cen;
}

int tdep[10005];
bool isleav[10005];
void tdfs(int now, int pa, vector<int> *G) {
    sz[now] = 1;
    mxch[now] = 0;
    isleav[now] = true;
    for (int i : G[now]) if (i != pa) {
        tdep[i] = tdep[now] + 1;
        tdfs(i, now, G);
        sz[now] += sz[i];
        isleav[now] = false;
        if (sz[mxch[now]] < sz[i]) mxch[now] = i;
    }
}
bool chkdfs(int now, int pa, vector<int> *G) {
    for (int i : G[now]) if (i != pa) {
        // cerr << "chkdfs " << now << " pa " << pa << " sz[now] " << sz[now] << " sz[i] " << sz[i] << endl;
        if (sz[i] > sz[now] / 2) return false;
        if (!chkdfs(i, now, G)) return false;
    }
    return true;
}
bool test(int n, vector<int> *G) {
    tdfs(1, 0, G);
    for (int i = 1; i <= n; ++i) if (max(sz[mxch[i]], n - sz[i]) <= n / 2) {
        // cerr << "root = " << i << endl;
        tdep[i] = 0;
        tdfs(i, 0, G);
        if (chkdfs(i, 0, G)) return 1;
    }
    return 0;
}

void MAIN() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t, n; cin >> t >> n;
    while (t--) {
        for (int i = 1; i <= n; ++i) G[i].clear();
        for (int i = 1; i < n; ++i) {
            int u, v; cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        if (test(n, G)) cout << "Centroid" << '\n';
        else cout << "Random" << '\n';
    }
    exit(0);
}

int main() {
    MAIN();
    exit(0);
    srand(time(0) * clock());
    int n = 1000; 
    for (int i = 1; i <= n; ++i) djs[i] = i;
    for (int i = 1; i < n; ++i) {
        int u = rand() % n + 1, v = rand() % n + 1;
        while (F(u) == F(v)) u = rand() % n + 1, v = rand() % n + 1;
        U(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    // int n; cin >> n;
    // for (int i = 1; i < n; ++i) {
    //     int u, v; cin >> u >> v;
    //     G[u].push_back(v);
    //     G[v].push_back(u);
    // }

    dfs(1, 0, G);
    int mx = max_element(dis, dis + 1 + n) - dis;
    dis[mx] = 0;
    dfs(mx, 0, G);
    mx = *max_element(dis, dis + 1 + n);

    // cout << mx << endl;
    int rand = mx;

    int rt = cdfs(1, 0);
    dis[rt] = 0;
    dfs(rt, 0, cG);
    mx = max_element(dis, dis + 1 + n) - dis;
    dis[mx] = 0;
    dfs(mx, 0, cG);
    mx = *max_element(dis, dis + 1 + n);

    // cout << mx << endl;
    int cen = mx;

    // for (int i = 1; i <= n; ++i) for (int j : G[i]) if (i < j) cerr << "G: " << i << " <-> " << j << endl;
    // for (int i = 1; i <= n; ++i) for (int j : cG[i]) if (i < j) cerr << "cG: " << i << " <-> " << j << endl;
    // cout << __lg(n) * 2 << endl;
    // assert(__lg(n) * 2 + 4 >= cen && __lg(n) * 2.2 < rand);

    assert(test(n, G) == 0);
    assert(test(n, cG) == 1);
}
