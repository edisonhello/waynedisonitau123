#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    vector<int64_t> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    vector<int> S(M), E(M);
    vector<int64_t> U(M);
    for (int i = 0; i < M; ++i) {
        cin >> S[i] >> E[i] >> U[i];
        S[i]--;
        E[i]--;
    }
    vector<tuple<int64_t, int, int>> vec;
    for (int i = 0; i < N; ++i) {
        int64_t sum = 0;
        for (int j = i; j <= N; ++j) {
            sum += A[j];
            vec.emplace_back(sum, i, j);
        }
    }
    sort(vec.begin(), vec.end());
    vector<int> ord(M);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) { return U[i] < U[j]; });

    constexpr int64_t kInf = 1'000'000'000'000'000'000;
    vector<vector<int64_t>> fenw(N + 1, vector<int64_t>(N + 1, -kInf));

    auto Update = [&](int x, int y, int64_t v) {
        for (int i = x + 1; i <= N; i += i & -i) {
            for (int j = y + 1; j <= N; j += j & -j) fenw[i][j] = max(fenw[i][j], v);
        }
    };

    auto Query = [&](int x, int y) {
        int64_t res = -kInf;
        for (int i = x + 1; i > 0; i -= i & -i) {
            for (int j = y + 1; j > 0; j -= j & -j) res = max(res, fenw[i][j]);
        }
        return res;
    };

    vector<int64_t> ans(M);
    for (int i = 0, j = 0; i < M; ++i) {
        while (j < vec.size() && get<0>(vec[j]) <= U[ord[i]]) {
            Update(N - 1 - get<1>(vec[j]), get<2>(vec[j]), get<0>(vec[j]));
            j++;
        }
        ans[ord[i]] = Query(N - 1 - S[ord[i]], E[ord[i]]);
    }
    for (int i = 0; i < M; ++i) {
        if (ans[i] == -kInf) cout << "NONE\n";
        else cout << ans[i] << "\n";
    }
    return 0;
}

