#include <bits/stdc++.h>
using namespace std;

vector<int> G[100005], iG[100005];
vector<int> a, b;
int d[100005], da[100005], db[100005];

bitset<100005> vis;
void dijk(int n, vector<int> G[], int d[], vector<int> s) {
    vis.reset();
    for (int i = 1; i <= n; ++i) d[i] = 1e8;
    queue<int> q;
    for (int ss : s) d[ss] = 0, q.push(ss), vis[ss] = 1;
    while (q.size()) {
        int now = q.front(); q.pop();
        for (int i : G[now]) if (!vis[i]) {
            vis[i] = 1;
            d[i] = d[now] + 1;
            q.push(i);
        }
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, ca, cb; cin >> n >> ca >> cb;
    while (ca--) { int t; cin >> t; a.push_back(t); }
    while (cb--) { int t; cin >> t; b.push_back(t); }
    for (int i = 1; i <= n; ++i) {
        int t; cin >> t; while (t--) {
            int u; cin >> u;
            G[i].push_back(u);
            iG[u].push_back(i);
        }
    }
    dijk(n, G, d, vector<int>{1});
    dijk(n, iG, da, a);
    dijk(n, iG, db, b);
    int mn = 1e9;
    for (int i = 1; i <= n; ++i) {
        mn = min(mn, d[i] + da[i] + db[i]);
    }
    if (mn >= 100000000) cout << "impossible" << endl;
    else cout << mn << endl;
}
