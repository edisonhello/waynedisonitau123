#include <bits/stdc++.h>
using namespace std;

bool Solve() {
    int N, M;
    cin >> N >> M;
    vector<int> t(N), h(N);
    vector<int> E;
    for (int i = 0; i < N; ++i) {
        cin >> t[i] >> h[i];
        h[i] = min(h[i], M);
    }
    int64_t S = M;
    for (int i = 0; i < N; ++i) {
        if (h[i] >= t[i]) S += h[i] - t[i];
        else E.push_back(i);
    }
    if (E.empty()) return true;
    sort(E.begin(), E.end(), [&](int i, int j) { return h[i] < h[j]; });
    int64_t sum = S;
    for (int e : E) sum += h[e] - t[e];
    int K = E.size();
    vector<tuple<int, int, int>> tree(4 * K);

    auto Build = [&]() {
        auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
            if (r - l == 1) {
                tree[o] = make_tuple(h[E[l]] - t[E[l]], h[E[l]], l);
                return;
            }
            int m = (l + r) >> 1;
            dfs(dfs, l, m, o * 2 + 1);
            dfs(dfs, m, r, o * 2 + 2);
            tree[o] = min(tree[o * 2 + 1], tree[o * 2 + 2]);
        };

        return dfs(dfs, 0, K);
    };

    constexpr int kInf = 2'000'000'000 + 1;

    auto Erase = [&](int p) {
        auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
            if (r - l == 1) {
                tree[o] = make_tuple(kInf, kInf, -1);
                return;
            }
            int m = (l + r) >> 1;
            if (p < m) dfs(dfs, l, m, o * 2 + 1);
            else dfs(dfs, m, r, o * 2 + 2);
            tree[o] = min(tree[o * 2 + 1], tree[o * 2 + 2]);
        };

        return dfs(dfs, 0, K);
    };

    auto Query = [&](int ql, int qr) {
        auto dfs = [&](auto dfs, int l, int r, int o = 0) -> tuple<int, int, int> {
            if (l >= qr || ql >= r) return make_tuple(kInf, kInf, -1);
            if (l >= ql && r <= qr) return tree[o];
            int m = (l + r) >> 1;
            return min(dfs(dfs, l, m, o * 2 + 1), dfs(dfs, m, r, o * 2 + 2));
        };

        return dfs(dfs, 0, K);
    };

    Build();

    for (int i = 0; i < E.size(); ++i) {
        int j = upper_bound(E.begin(), E.end(), sum, [&](int64_t x, int p) { return h[p] > x; }) - E.begin();
        auto f = Query(0, j);
        int y = get<2>(f);
        if (y == -1) return false;
        sum -= h[E[y]];
        sum += t[E[y]];
        if (sum < 0) return false;
        Erase(y);
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cout << (Solve() ? "YES" : "NO") << "\n";
    }
}

