#include <bits/stdc++.h>
using namespace std;

int main() {
#ifdef ONLINE_JUDGE
    freopen("comparator.in", "r", stdin);
    freopen("comparator.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; while (cin >> n) {
        if (n == 0) break;
        vector<int> v(n);
        for (int i = 0; i < n; ++i) cin >> v[i];
        bool sorted = true;
        for (int i = 1; i < n; ++i) {
            if (v[i - 1] > v[i]) sorted = false;
        }
        if (sorted) {
            cout << -1 << '\n';
            continue;
        }
        vector<pair<int, int>> ans;

        auto apply = [&] (int a, int b) {
            if (a > b) swap(a, b);
            ans.emplace_back(a + 1, b + 1);
            if (v[a] == 1 && v[b] == 0) swap(v[a], v[b]);
        };

        int st = 0;
        while (true) {
            int zero = 0;
            for (int i = st; i < n; ++i) if (v[i] == 0) ++zero;
            if (zero > 1) {
                vector<int> zeros, ones;
                for (int i = st; i < n; ++i) {
                    if (v[i] == 0) zeros.push_back(i);
                    else ones.push_back(i);
                }
                for (int i = 0; i < (int)ones.size(); ++i) {
                    for (int j = 0; j < (int)ones.size() - i - 1; ++j) {
                        // ans.emplace_back(ones[j], ones[j + 1]);
                        apply(ones[j], ones[j + 1]);
                    }
                }
                for (int i = 0; i < (int)zeros.size(); ++i) {
                    for (int j = 0; j < (int)zeros.size() - i - 1; ++j) {
                        // ans.emplace_back(zeros[j], zeros[j + 1]);
                        apply(zeros[j], zeros[j + 1]);
                    }
                }
                apply(zeros[0], ones[0]);
                // ans.emplace_back(zeros[0], ones[0]);
                // if (zeros[0] > ones[0]) swap(v[zeros[0]], v[ones[0]]);
                ++st;
            } else {
                vector<int> pos;
                for (int i = st; i < n; ++i) if (v[i]) pos.push_back(i);
                for (int i = 0; i < (int)pos.size(); ++i) {
                    for (int j = 0; j < (int)pos.size() - i - 1; ++j) {
                        apply(pos[j], pos[j + 1]);
                    }
                }
                pos.clear();
                for (int i = st; i < n; ++i) if (i != st) pos.push_back(i);
                for (int i = 0; i < (int)pos.size(); ++i) {
                    for (int j = 0; j < (int)pos.size() - i - 1; ++j) {
                        apply(pos[j], pos[j + 1]);
                    }
                }
                break;
            }
        }

        cout << ans.size() << '\n';
        for (auto &p : ans) cout << p.first << ' ' << p.second << '\n';
    }
}
