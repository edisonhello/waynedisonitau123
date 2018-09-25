#pragma GCC optimize("Ofast", "no-stack-protector", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int maxn = 800 + 5;
const double inf = 1e6;
vector<pair<int, double>> g[maxn];
double d[maxn];
bool v[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    while (m--) {
        int a, b;
        double c;
        cin >> a >> b >> c;
        --a, --b;
        c = -log(c);
        g[a].emplace_back(b, c);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) d[j] = inf;
        d[i] = 0;
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        memset(v, false, sizeof(v));
        pq.emplace(0.0, i);
        while (pq.size()) {
            int x = pq.top().second;
            double dd = pq.top().first;
            pq.pop();
            if (v[x]) continue;
            v[x] = true;
            for (auto u : g[x]) {
                if (d[u.first] > dd + u.second) {
                    if (u.first == i) {
                        cout << "inadmissible" << endl;
                        return 0;
                    }
                    d[u.first] = dd + u.second;
                    pq.emplace(d[u.first], u.first);
                }
            }
        }
    }
    cout << "admissible" << endl;
}
