#include <bits/stdc++.h>
using namespace std;

vector<int> g[255];
set<int> ng[255];
int djs[255], trash[255], sz[255], o[255], io[255], nn;
int ans;
long long cans;

int F(int x) { return djs[x] == x ? x : djs[x] = F(djs[x]); }

unordered_map<long long, pair<int, long long>> rec[255];
pair<int, long long> dfs(int now, long long fb) {
    if (now == nn) return make_pair(0, 1);
    if (rec[now].count(fb)) return rec[now][fb];
    if (fb & (1ll << now)) { return rec[now][fb] = dfs(now + 1, fb); }
    // cout << "now = " << now << ", io[now] = " << io[now] << endl;
    // cerr << "now = " << now << " , fb = " << fb << endl;
    int mx = 0;
    long long hh = 1;
    long long ofb = fb;
    auto res = dfs(now + 1, fb | (1ll << now)); // no select
    // cerr << "now = " << now << " not select case = " << res.first << endl;
    if (res.second && mx < res.first) {
        hh = res.second;
        mx = res.first;
    }
    else if (res.second && mx == res.first) {
        hh += res.second;
    }

    for (int i : ng[o[now]]) fb |= (1ll << io[i]);
    // cerr << "now = " << now << " take" << endl;
    res = dfs(now + 1, fb | (1ll << now));
    res.first += sz[o[now]];
    // cerr << "now = " << now << ", take case = " << res.first << endl;
    if (res.second && mx < res.first) {
        hh = res.second;
        mx = res.first;
    }
    else if (res.second && mx == res.first) {
        hh += res.second;
    }

    return rec[now][ofb] = make_pair(mx, hh);
}

int main() {
    int n, p, q; cin >> n >> p >> q;
    for (int i = 1; i <= n; ++i) djs[i] = i;
    while (p--) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        djs[F(u)] = F(v);
    }
    while (q--) {
        int u, v; cin >> u >> v;
        if (F(u) == F(v)) trash[F(u)] = 1;
        else ng[F(u)].insert(F(v)), ng[F(v)].insert(F(u));
    }
    for (int i = 1; i <= n; ++i) ++sz[F(i)];
    for (int i = 1; i <= n; ++i) if (sz[i] && !trash[i]) o[nn] = i, io[i] = nn, nn++;
    // for (int i = 1; i <= n; ++i) cerr << i << " bel to " << F(i) << "(" << io[F(i)] << ")" << endl;

    pair<int, long long> ans = dfs(0, 0);

    cout << ans.first << " " << ans.second << endl;
}
