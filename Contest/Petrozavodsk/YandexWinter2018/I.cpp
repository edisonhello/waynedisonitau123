#include <bits/stdc++.h>
using namespace std;

int top[10005], sz[10005];

int main() {
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; ++i) sz[i] = k;
    while (true) {
        for (int i = 1; i <= n; ++i) cin >> top[i];
        vector<pair<int, int>> v;
        int total_weight = 0;
        for (int i = 1; i <= n; ++i) if (sz[i]) v.emplace_back(top[i], 1 << sz[i]);
        for (int i = 1; i <= n; ++i) if (sz[i]) total_weight += (1 << sz[i]);
        int now_weight = 0;
        sort(v.begin(), v.end());
        int take = -1;
        for (auto &p : v) {
            now_weight += p.second;
            if (now_weight >= total_weight / 2) {
                take = p.first;
                break;
            }
        }
        // assert(take != -1);
        if (take == -1) take = v[0].first;
        cout << take << endl;
        string ans; cin >> ans;
        if (ans == "End") break;
        if (ans == "<=") {
            for (int i = 1; i <= n; ++i) if (sz[i] && top[i] <= take) --sz[i];
        } else {
            for (int i = 1; i <= n; ++i) if (sz[i] && top[i] >= take) --sz[i];
        }
    }
}
