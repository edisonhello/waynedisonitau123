#include <bits/stdc++.h>
using namespace std;

bool Solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    vector<int> ds(A.begin(), A.end());
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    for (int i = 0; i < N; ++i) {
        A[i] = lower_bound(ds.begin(), ds.end(), A[i]) - ds.begin();
    }

    vector<int> tree(N * 4), tag(N * 4);

    auto Update = [&](int ql, int qr, int v) {
        auto dfs = [&](auto dfs, int l, int r, int o = 0) {
            if (l >= qr || ql >= r) return;
            if (l >= ql && r <= qr) {
                tree[o] += v;
                tag[o] += v;
                return;
            }
            for (int k = 1; k <= 2; ++k) {
                tree[o * 2 + k] += tag[o];
                tag[o * 2 + k] += tag[o];
            }
            tag[o] = 0;
            int m = (l + r) >> 1;
            dfs(dfs, l, m, o * 2 + 1);
            dfs(dfs, m, r, o * 2 + 2);
            tree[o] = min(tree[o * 2 + 1], tree[o * 2 + 2]);
        };

        dfs(dfs, 0, N);
    };

    auto Query = [&](int ql, int qr) {
        auto dfs = [&](auto dfs, int l, int r, int o = 0) {
            if (l >= qr || ql >= r) return N + 1;
            if (l >= ql && r <= qr) return tree[o];
            for (int k = 1; k <= 2; ++k) {
                tree[o * 2 + k] += tag[o];
                tag[o * 2 + k] += tag[o];
            }
            tag[o] = 0;
            int m = (l + r) >> 1;
            return min(dfs(dfs, l, m, o * 2 + 1), dfs(dfs, m, r, o * 2 + 2));
        };

        return dfs(dfs, 0, N);
    };

    const int M = ds.size();
    vector<vector<int>> pos(M);
    vector<int> ptr(N);
    for (int i = 0; i < N; ++i) {
        ptr[i] = pos[A[i]].size();
        pos[A[i]].push_back(i);
    }
    for (int i = 0; i < M; ++i) {
        int nxt = pos[i].size() > 1 ? pos[i][1] : N;
        Update(pos[i][0], nxt, 1);
    }
    for (int i = 0; i < N; ++i) {
        if (Query(i, N) <= 0) return false;
        int nxt = ptr[i] == pos[A[i]].size() - 1 ? N : pos[A[i]][ptr[i] + 1];
        Update(i, nxt, -1);
        if (ptr[i] + 1 < pos[A[i]].size()) {
            int r = ptr[i] + 2 < pos[A[i]].size() ? pos[A[i]][ptr[i] + 2] : N;
            Update(pos[A[i]][ptr[i] + 1], r, 1);
        }
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cout << (Solve() ? "non-boring" : "boring") << "\n";
    }
}

