#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    // t = 100;
    mt19937 rng(7122);
    constexpr int kB = 500;
    constexpr int kM = 10000;
    while (t--) {
        int n, m;
        // n = 10000;
        // m = 500000;
        cin >> n >> m;
        uint64_t x, y, z;
        cin >> x >> y >> z;
        // x = rng() % (1 << 30);
        // y = rng() % (1 << 30);
        // z = rng() % (1 << 30);

        auto Rng = [&]() {
            x = (x ^ (x << 11)) & ((1ULL << 32) - 1);
            x = x ^ (x >> 4);
            x = x ^ (x << 5) & ((1ULL << 32) - 1);
            x = x ^ (x >> 14);
            uint64_t w = (x ^ (y ^ z)) & ((1ULL << 32) - 1);
            x = y;
            y = z;
            z = w;
            return z;
        };

        vector<int> a(n);
        vector<int> l(m), r(m), v(m);
        vector<tuple<int, int, int>> s;
        vector<vector<int>> ev(n);
        for (int i = 0; i < m; ++i) {
            l[i] = Rng() % n, r[i] = Rng() % n;
            if (l[i] > r[i]) swap(l[i], r[i]);
            v[i] = Rng() % (1 << 30);
            s.emplace_back(-v[i], l[i], r[i]);
        }
        const int kS = min(m, kM);
        nth_element(s.begin(), s.begin() + kS, s.end());
        for (int i = 0; i < kS; ++i) {
            ev[get<1>(s[i])].push_back(-get<0>(s[i]));
            if (get<2>(s[i]) + 1 < n) ev[get<2>(s[i]) + 1].push_back(get<0>(s[i]));
        }
        for (int i = kS; i < m; ++i) {
            if (get<1>(s[i]) <= n / kB) {
                ev[get<1>(s[i])].push_back(-get<0>(s[i]));
                if (get<2>(s[i]) + 1 < n) ev[get<2>(s[i]) + 1].push_back(get<0>(s[i]));
            }
            if (get<2>(s[i]) >= n - n / kB) {
                ev[get<1>(s[i])].push_back(-get<0>(s[i]));
                if (get<2>(s[i]) + 1 < n) ev[get<2>(s[i]) + 1].push_back(get<0>(s[i]));
            }
        }
        // int dist = max(1, n / kB);
        // vector<bool> cv(m);
        // vector<vector<int>> ev(n);
        // for (int i = 0; i < n; i += dist) {
        //     int g = 0, z = -1;
        //     for (int j = 0; j < m; ++j) {
        //         if (l[j] <= i && r[j] >= i) {
        //             cv[j] = true;
        //             if (v[j] > g) {
        //                 g = v[j];
        //                 z = j;
        //             }
        //         }
        //     }
        //     if (z != -1) {
        //         ev[l[z]].push_back(z);
        //         if (r[z] + 1 < n) ev[r[z] + 1].push_back(~z);
        //     }
        // }
        // for (int i = 0; i < m; ++i) {
        //     if (cv[i]) continue;
        //     ev[l[i]].push_back(i);
        //     if (r[i] + 1 < n) ev[r[i] + 1].push_back(~i);
        // }
        // for (int i = 0; i < kM; ++i) {
        //     int p = rng() % m;
        //     ev[l[p]].push_back(p);
        //     if (r[p] + 1 < n) ev[r[p] + 1].push_back(~p);
        // }
        multiset<int> ss;
        uint64_t res = 0;
        for (int i = 0; i < n; ++i) {
            for (int u : ev[i]) {
                if (u >= 0)  ss.insert(u);
                else ss.erase(ss.find(-u));
            }
            int v = ss.empty() ? 0 : *ss.rbegin();
            // cout << "v = " << v << endl;
            res ^= 1LL * v * (i + 1);
        }
        cout << res << "\n";
    }
}

