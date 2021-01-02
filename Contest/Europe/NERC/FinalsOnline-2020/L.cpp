#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<vector<int>> g(N);
    vector<int> key(N);
    for (int i = 0; i < N; ++i) {
        int l, r;
        cin >> l >> r >> key[i];
        l--;
        r--;
        if (l >= 0) g[i].push_back(l);
        if (r >= 0) g[i].push_back(r);
    }

    vector<int> Min(N), Max(N);

    auto Dfs = [&](auto dfs, int x) -> void {
        Min[x] = Max[x] = key[x];
        for (int u : g[x]) {
            dfs(dfs, u);
            Min[x] = min(Min[x], Min[u]);
            Max[x] = max(Max[x], Max[u]);
        }
    };

    Dfs(Dfs, 0);
    int Q;
    cin >> Q;
    vector<int> L(Q), R(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> L[i] >> R[i];
    }
    vector<int> D(key.begin(), key.end());
    D.insert(D.end(), L.begin(), L.end());
    D.insert(D.end(), R.begin(), R.end());

    sort(D.begin(), D.end());
    D.resize(unique(D.begin(), D.end()) - D.begin());

    for (int &u : Max) u = lower_bound(D.begin(), D.end(), u) - D.begin();
    for (int &u : Min) u = lower_bound(D.begin(), D.end(), u) - D.begin();
    for (int &u : L) u = lower_bound(D.begin(), D.end(), u) - D.begin();
    for (int &u : R) u = lower_bound(D.begin(), D.end(), u) - D.begin();

    vector<int> Order(Q);
    iota(Order.begin(), Order.end(), 0);
    sort(Order.begin(), Order.end(), [&](int i, int j) { return R[i] < R[j]; });
    vector<int> VOrder(N);
    iota(VOrder.begin(), VOrder.end(), 0);
    sort(VOrder.begin(), VOrder.end(), [&](int i, int j) { return Max[i] < Max[j]; });

    int M = D.size();
    vector<int> Fenw(M + 1);

    auto Add = [&](int p, int v) {
        for (int i = p + 1; i <= M; i += i & -i) Fenw[i] += v;
    };

    auto Query = [&](int p) {
        int res = 0;
        for (int i = p + 1; i > 0; i -= i & -i) res += Fenw[i];
        return res;
    };

    vector<int> ans(Q);
    for (int i = 0, j = 0; i < Q; ++i) {
        while (j < N && Max[VOrder[j]] <= R[Order[i]]) Add(Min[VOrder[j++]], 1);
        ans[Order[i]] += Query(R[Order[i]]) - Query(L[Order[i]] - 1);
    }

    sort(Order.begin(), Order.end(), [&](int i, int j) { return L[i] < L[j]; });
    int cnt = 0;
    for (int i = 0, j = 0; i < Q; ++i) {
        while (j < N && Max[VOrder[j]] < L[Order[i]]) cnt++, j++;
        ans[Order[i]] += cnt;
    }
    sort(Order.begin(), Order.end(), [&](int i, int j) { return R[i] > R[j]; });
    sort(VOrder.begin(), VOrder.end(), [&](int i, int j) { return Min[i] > Min[j]; });
    cnt = 0;
    for (int i = 0, j = 0; i < Q; ++i) {
        while (j < N && Min[VOrder[j]] > R[Order[i]]) cnt++, j++;
        ans[Order[i]] += cnt;
    }

    for (int i = 0; i < Q; ++i) {
        cout << (N - ans[i]) * 2 + 1 << "\n";
    }

    return 0;
}

