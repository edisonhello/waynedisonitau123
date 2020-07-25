#include <bits/stdc++.h>
using namespace std;

int Solve() {
    int64_t n, s;
    int k;
    cin >> n >> s >> k;
    vector<int> a(k);
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
    }
    constexpr int kM = 200000 + 1;
    vector<int64_t> v = {0};
    while (true) {
        // cout << "n = " << n << " s = " << s << endl;
        // cout << "before: "; for (auto u : v) cout << u << " "; cout << endl;
        if (n & 1) {
            bitset<kM> nbs, bs;
            for (auto u : v) bs.set(u);
            for (int i = 0; i < k; ++i) nbs ^= bs << a[i];
            v.clear();
            for (int j = 0; j < kM; ++j) {
                if (nbs[j]) {
                    v.push_back(j);
                }
            }
        }
        if (n == 1) break;
        // cout << "after: "; for (auto u : v) cout << u << " "; cout << endl;
        if (s & 1) {
            for (auto &u : v) u--;
            s--;
        }
        vector<int64_t> nv;
        for (auto u : v) {
            if (u >= 0 && u % 2 == 0) nv.push_back(u / 2);
        }
        v = nv;
        s >>= 1;
        n >>= 1;
    }
    return find(v.begin(), v.end(), s) != v.end();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) cout << Solve() << "\n";
}

