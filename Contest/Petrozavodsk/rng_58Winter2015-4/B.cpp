#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> X(N), Y(N);
    for (int i = 0; i < N; ++i) {
        cin >> X[i] >> Y[i];
    }

    int A = 0, B = 0, C = 0, D = 0;
    for (int i = 0; i < N; ++i) {
        if (X[i] + Y[i] > X[A] + Y[A]) A = i;
        if (X[i] - Y[i] > X[B] - Y[B]) B = i;
        if (-X[i] + Y[i] > -X[C] + Y[C]) C = i;
        if (-X[i] - Y[i] > -X[D] - Y[D]) D = i;
    }

    vector<tuple<int, int, int>> edge;

    auto AddEdge = [&](int u, int v) {
        int dist = abs(X[u] - X[v]) + abs(Y[u] - Y[v]);
        edge.emplace_back(dist, u, v);
    };

    for (int i = 0; i < N; ++i) {
        if (i != A) AddEdge(i, A);
        if (i != B) AddEdge(i, B);
        if (i != C) AddEdge(i, C);
        if (i != D) AddEdge(i, D);
    }

    // auto Solve = [&] {
    //     vector<int> ds(N);
    //     for (int i = 0; i < N; ++i) {
    //         ds[i] = X[i] - Y[i];
    //     }
    //     sort(ds.begin(), ds.end());
    //     ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    //     vector<int> ord(N);
    //     iota(ord.begin(), ord.end(), 0);
    //     sort(ord.begin(), ord.end(), [&](int i, int j) {
    //         return X[i] == X[j] ? Y[i] > Y[j] : X[i] > X[j];
    //     });

    //     vector<pair<int, int>> fw(ds.size() + 1, make_pair(-2'000'000'000, -1));

    //     auto Query = [&](int p) {
    //         pair<int, int> res = make_pair(-2'000'000'000, -1);
    //         for (int i = p + 1; i > 0; i -= i & -i) {
    //             res = max(res, fw[i]);
    //         }
    //         return res;
    //     };

    //     auto Update = [&](int p, pair<int, int> v) {
    //         for (int i = p + 1; i < fw.size(); i += i & -i) {
    //             fw[i] = max(fw[i], v);
    //         }
    //     };

    //     for (int i = 0, j = 0; i < N; ++i) {
    //         int p = lower_bound(ds.begin(), ds.end(), X[ord[i]] - Y[ord[i]]) - ds.begin();
    //         auto q = Query(p);
    //         if (q.second >= 0) AddEdge(ord[i], q.second);
    //         Update(p, make_pair(X[ord[i]] + Y[ord[i]], ord[i]));
    //     }
    // };

    // Solve();
    // for (int i = 0; i < N; ++i) swap(X[i], Y[i]);
    // Solve();
    // for (int i = 0; i < N; ++i) X[i] = -X[i];
    // Solve();
    // for (int i = 0; i < N; ++i) swap(X[i], Y[i]);
    // Solve();

    sort(edge.begin(), edge.end());
    reverse(edge.begin(), edge.end());
    vector<int> uf(N);
    iota(uf.begin(), uf.end(), 0);

    function<int(int)> Find = [&](int x) {
        if (x == uf[x]) return x;
        return uf[x] = Find(uf[x]);
    };

    auto Merge = [&](int u, int v) {
        u = Find(u);
        v = Find(v);
        uf[u] = v;
    };

    int res = -1;
    for (int i = 0; i < edge.size(); ++i) {
        int w, u, v;
        tie(w, u, v) = edge[i];
        if (Find(u) != Find(v)) {
            res = w;
            Merge(u, v);
        }
    }
    cout << res << "\n";
}

