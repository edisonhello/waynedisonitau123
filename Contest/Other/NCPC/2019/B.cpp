#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
vector<pair<int, int>> g[maxn];
int d[maxn], upd[maxn], inq[maxn];

int main() {
    int m; cin >> m;
    while (m--) {
        int n, r; cin >> n >> r;
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < r; ++i) {
            int x, y, w; cin >> x >> y >> w;
            g[x].emplace_back(y, w);
        }
        for (int i = 0; i < n; ++i) d[i] = upd[i] = inq[i] = 0;
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            q.push(i);
            inq[i] = 1;
        }
        bool ans = false;
        while (!ans && !q.empty()) {
            int x = q.front(); q.pop();
            inq[x] = 0;
            for (auto e : g[x]) {
                if (d[e.first] > d[x] + e.second) {
                    if (++upd[e.first] > n) ans = true;
                    d[e.first] = d[x] + e.second;
                    if (!inq[e.first]) {
                        inq[e.first] = true;
                        q.push(e.first);
                    }
                }
            }
        }
        if (ans) puts("Wonderful Tour");
        else puts("No Wonderful Tours");
    }
}
