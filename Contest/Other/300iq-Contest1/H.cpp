#include <bits/stdc++.h>
using namespace std;

void Solve(int n, int k) {
    // cout << "n = " << n << " k = " << k << endl;
    int m = n;
    vector<pair<int, int>> ans;
    vector<int> adj(n);
    int nk = (1 << n) - k - 1;
    for (int i = n; nk > 0 && i > 0; --i) {
        int ck = 1, sum = 0, ksum = -1, z = -1;
        for (int j = 0; j < i; ++j) {
            sum += ck;
            if (sum <= nk) {
                ksum = sum;
                z = j + 1;
            }
            // cout << "ck = " << ck << endl;
            ck = ck * (i - 1 - j);
            ck = ck / (j + 1);
        }
        assert(z != -1);
        for (int j = 1; j <= z; ++j) {
            ans.emplace_back(i, j);
            adj[i - 1] |= (1 << (j - 1));
            // cout << i << ' ' << j << endl;
        }
        nk -= ksum;
    }
    assert(nk == 0);
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); ++i) cout << ans[i].first << ' ' << ans[i].second << "\n";
    // int res = 0;
    // for (int s = 0; s < (1 << n); ++s) {
    //     int nb = 0;
    //     for (int i = 0; i < n; ++i) {
    //         if (s >> i & 1) nb |= adj[i];
    //     }
    //     if (__builtin_popcount(s) > __builtin_popcount(nb)) res++;
    // }
    // cout << "res = " << res << " k = " << k << endl;
    // assert(k == res);
}

int main() {
    int n, k;
    cin >> n >> k;
    Solve(n, k);
}

