#include <bits/stdc++.h>
using namespace std;

struct Q {
    long long cap;
    int x, y, i;
};

vector<pair<int, long long>> G[200005];
vector<int> oil;
long long near[200005];
bitset<200005> vis;
int ans[200005];
int djs[200005];

int F(int x) { return x == djs[x] ? x : djs[x] = F(djs[x]); }
void U(int x, int y) { djs[F(x)] = F(y); }
bool C(int x, int y) { return F(x) == F(y); }

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, s, m; cin >> n >> s >> m;
    for (int i = 1; i <= n; ++i) djs[i] = i;
    while (s--) {
        int t; cin >> t; oil.push_back(t);
    }
    for (int i = 1; i <= m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    memset(near, 0x3f, sizeof(near));
    for (int i : oil) {
        pq.emplace(0, i);
        near[i] = 0;
    }
    while (pq.size()) {
        int now = pq.top().second; pq.pop();
        if (vis[now]) continue;
        vis[now] = 1;
        for (auto &p : G[now]) {
            if (near[p.first] > near[now] + p.second) {
                near[p.first] = near[now] + p.second;
                pq.emplace(near[p.first], p.first);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (auto &p : G[i]) {
            p.second += near[p.first] + near[i];
        }
    }
    int q; cin >> q;
    vector<Q> qs;
    for (int i = 1; i <= q; ++i) {
        int x, y, b; cin >> x >> y >> b;
        qs.push_back(Q{b, x, y, i});
    }
    sort(qs.begin(), qs.end(), [&] (const Q &a, const Q &b) -> bool { return a.cap < b.cap; });
    vector<Q> es;
    for (int i = 1; i <= n; ++i) {
        for (auto &p : G[i]) if (p.first > i) {
            es.push_back(Q{p.second, i, p.first, 0});
        }
    }
    sort(es.begin(), es.end(), [&] (const Q &a, const Q &b) -> bool { return a.cap < b.cap; });
    reverse(es.begin(), es.end());
    for (Q q : qs) {
        while (es.size() && es.back().cap <= q.cap) {
            U(es.back().x, es.back().y);
            es.pop_back();
        }
        ans[q.i] = C(q.x, q.y);
    }
    for (int i = 1; i <= q; ++i) {
        if (ans[i]) cout << "TAK\n";
        else cout << "NIE\n";
    }
}
