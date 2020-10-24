#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int FirstFit(int N, int C, const vector<int> &A) {
    vector<int> tree(N * 4, C);

    auto Update = [&](auto dfs, int l, int r, int v, int o = 0) {
        if (r - l == 1) {
            assert(tree[o] >= v);
            tree[o] -= v;
            return;
        }
        int m = (l + r) >> 1;
        if (tree[o * 2 + 1] >= v) dfs(dfs, l, m, v, o * 2 + 1);
        else dfs(dfs, m, r, v, o * 2 + 2);
        tree[o] = max(tree[o * 2 + 1], tree[o * 2 + 2]);
    };

    auto Dfs = [&](auto dfs, int l, int r, int o = 0) -> int {
        if (r - l == 1) return tree[o] < C;
        int m = (l + r) >> 1;
        return dfs(dfs, l, m, o * 2 + 1) + dfs(dfs, m, r, o * 2 + 2);
    };

    for (int i = 0; i < N; ++i) {
        Update(Update, 0, N, A[i]);
    }

    return Dfs(Dfs, 0, N);
}

int BestFit(int N, int C, const vector<int> &A) {
    set<pair<int, int>> s;
    for (int i = 0; i < N; ++i) s.insert(make_pair(C, i));
    for (int i = 0; i < N; ++i) {
        auto it = s.lower_bound(make_pair(A[i], -1));
        assert(it != s.end());
        auto P = *it;
        s.erase(it);
        P.first -= A[i];
        if (P.first > 0) s.insert(P);
    }
    int res = N;
    for (auto it : s) {
        if (it.first == C) res--;
    }
    return res;
}

void Solve() {
    int N, C;
    cin >> N >> C;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    cout << FirstFit(N, C, A) << " " << BestFit(N, C, A) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) Solve();
}

