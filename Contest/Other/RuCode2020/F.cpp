#include <bits/stdc++.h>
using namespace std;

queue<int> q[100005];
int djs[100005];

int F(int x) { return x == djs[x] ? x : djs[x] = F(djs[x]); }

vector<pair<int, int>> g[100005];

int pa[20][100005], mx[20][100005];
int dep[100005];

void dfs(int now, int p, int d) {
    pa[0][now] = p;
    for (int i = 1; pa[i - 1][now]; ++i) {
        pa[i][now] = pa[i - 1][pa[i - 1][now]];
        mx[i][now] = max(mx[i - 1][now], mx[i - 1][pa[i - 1][now]]);
    }
    dep[now] = d;

    for (auto e : g[now]) if (e.first != p) {
        mx[0][e.first] = e.second;
        dfs(e.first, now, d + 1);
    }
}

int Query(int a, int b) {
    assert(a != b);
    if (dep[a] > dep[b]) swap(a, b);
    int x = 0;
    for (int i = 19; i >= 0; --i) if ((dep[b] - dep[a]) & (1 << i)) {
        x = max(x, mx[i][b]);
        b = pa[i][b];
    }
    if (a == b) return x;
    for (int i = 19; i >= 0; --i) if (pa[i][a] != pa[i][b]) {
        x = max(x, max(mx[i][a], mx[i][b]));
        a = pa[i][a];
        b = pa[i][b];
    }
    return max(x, max(mx[0][a], mx[0][b]));
}

void Print(queue<int> q) {
    cerr << "[";
    while (q.size()) {
        cerr << q.front() << ' ';
        q.pop();
    }
    cerr << "]" << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<tuple<int, int, int>> es;
    for (int i = 1; i < n; ++i) {
        int u, v, w; cin >> u >> v >> w;
        es.emplace_back(w, u, v);
        g[u].emplace_back(v, 1 << w);
        g[v].emplace_back(u, 1 << w);
    }

    sort(es.begin(), es.end());
    // reverse(es.begin(), es.end());

    for (int i = 1; i <= n; ++i) q[i].push(i);
    for (int i = 1; i <= n; ++i) djs[i] = i;

    for (auto &e : es) {
        int _, u, v; tie(_, u, v) = e;
        // cerr << "_ u v " << _ << ' ' << u << ' ' << v << endl;
        u = F(u), v = F(v);

        if (q[v].size() > q[u].size()) swap(u, v);
        // u > v

        while (q[v].size()) {
            q[u].push(q[v].front());
            q[v].pop();
            q[u].push(q[u].front());
            q[u].pop();
        }
        // Print(q[u]);

        djs[v] = u;
    }

    // cerr << "la" << endl;

    dfs(1, 0, 0);    

    int x = F(1);
    int p = q[x].front(); q[x].pop();
    // cerr << "p = " << p;

    long long ans = 0;
    while (q[x].size()) {
        ans += Query(p, q[x].front());
        p = q[x].front();
        q[x].pop();
        // cerr << " " << p;
    }
    // cerr << endl;

    cout << ans << endl;


}

