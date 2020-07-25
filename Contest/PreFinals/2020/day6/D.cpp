#include <bits/stdc++.h>
using namespace std;

vector<tuple<int, int, pair<int, int>>> hi[10005];

int p[10005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;

    for (int i = 1; i < n; ++i) {
        int j = 1;
        int x; while (cin >> x, x) {
            hi[x].emplace_back(i, i + 1, make_pair(i, j++));
        }
    }

    for (int i = 1; i <= n; ++i) p[i] = i;
    for (int i = 1; i <= 1000; ++i) {
        for (auto &pp : hi[i]) {
            swap(p[get<0>(pp)], p[get<1>(pp)]);
        }
    }

    vector<pair<int, int>> ans;
    for (int i = 1000; i >= 1; --i) {
        for (auto &pp : hi[i]) {
            if (p[get<0>(pp)] > p[get<1>(pp)]) {
                swap(p[get<0>(pp)], p[get<1>(pp)]);
                ans.push_back(get<2>(pp));
            }
        }
    }

    cout << ans.size() << endl;
    for (auto &p : ans) cout << p.first << ' ' << p.second << '\n';
    

}

