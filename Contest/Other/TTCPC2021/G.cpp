#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) cin >> v[i];

    vector<tuple<int, int, int>> e;
    for (int i = 0; i < m; ++i) {
        int y, a, b; cin >> y >> a >> b;
        e.emplace_back(y, a, b);
    }

    sort(e.begin(), e.end());
    reverse(e.begin(), e.end());

    for (auto [y, a, b] : e) {
        swap(v[a], v[b]);
    }

    for (int i = 1; i <= n; ++i) cout << v[i] << " \n"[i == n];

}
