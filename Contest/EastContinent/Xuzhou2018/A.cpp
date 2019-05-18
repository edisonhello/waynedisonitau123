#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int maxn = 100005;

vector<tuple<unsigned long long, int, int>> g;
int djs[maxn];

int F(int x){ return x == djs[x] ? x : djs[x] = F(djs[x]); }

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, m;
        unsigned long long k1, k2; 
        auto rand = [&] () {
            unsigned long long k3 = k1, k4 = k2;
            k1 = k4;
            k3 ^= k3 << 23;
            k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
            return k2 + k4;
        };
        g.clear();
        scanf("%d%d%llu%llu", &n, &m, &k1, &k2);
        for (int i = 1; i <= m; ++i) {
            int u = rand() % n + 1;
            int v = rand() % n + 1;
            unsigned long long w = rand();
            g.emplace_back(w, u, v);
        }
        sort(g.begin(), g.end());
        for (int i = 1; i <= n; ++i) djs[i] = i;
        unsigned long long ans = 0;
        int cnt = 0;
        for (auto &e : g) {
            unsigned long long w;
            int u, v; 
            tie(w, u, v) = e;
            if (F(u) == F(v)) continue;
            // cout << u << " " << v << " " << w << endl;
            ans = (ans + w % mod) % mod;
            djs[F(u)] = F(v);
            ++cnt;
        }
        if (cnt != n - 1) puts("0");
        else printf("%llu\n", ans);
    }
}
