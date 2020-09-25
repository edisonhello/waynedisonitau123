#include <bits/stdc++.h>
using namespace std;

int Solve() {
    int N, K;
    cin >> N >> K;
    vector<int> x(N), y(N), c(N);
    vector<vector<int>> p(K);
    for (int i = 0; i < N; ++i) {
        cin >> x[i] >> y[i] >> c[i];
        c[i]--;
        p[c[i]].push_back(i);
    }

    vector<tuple<int, int, int>> rect;

    for (int i = 0; i < K; ++i) {
        sort(p[i].begin(), p[i].end(), [&](int u, int v) { return y[u] < y[v]; });
        set<int> s;
        s.insert(0);
        s.insert(1'000'000'000 + 1);
        for (int j = 0; j < p[i].size(); ++j) {
            if (s.count(x[p[i][j]])) continue;
            auto it = s.lower_bound(x[p[i][j]]);
            assert(it != s.end() && it != s.begin());
            if (*prev(it) + 1 <= *it - 1) {
                rect.emplace_back(y[p[i][j]] - 1, *prev(it) + 1, *it - 1);
            }
            s.insert(x[p[i][j]]); 
        }
        for (auto it = s.begin(); next(it) != s.end(); ++it) {
            if (*it + 1 <= *next(it) - 1) {
                rect.emplace_back(1'000'000'000, *it + 1, *next(it) - 1);
            }
        }
    }

    vector<int> ds(x.begin(), x.end());
    for (auto t : rect) {
        ds.push_back(get<1>(t));
        ds.push_back(get<2>(t));
    }

    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

    sort(rect.begin(), rect.end());
    vector<int> ord(N);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) { return y[i] < y[j]; });

    const int M = ds.size();
    vector<int> fw(M + 1);

    auto Update = [&](int p, int v) {
        for (int i = p + 1; i <= M; i += i & -i) {
            fw[i] += v;
        }
    };

    auto Get = [&](int p) {
        int res = 0;
        for (int i = p + 1; i > 0; i -= i & -i) {
            res += fw[i];
        }
        return res;
    };

    int res = 0;
    for (int i = 0, j = 0; i < rect.size(); ++i) {
        while (j < N && y[ord[j]] <= get<0>(rect[i])) {
            int p = lower_bound(ds.begin(), ds.end(), x[ord[j]]) - ds.begin();
            Update(p, 1);
            j++;
        }
        int L = lower_bound(ds.begin(), ds.end(), get<1>(rect[i])) - ds.begin();
        int R = lower_bound(ds.begin(), ds.end(), get<2>(rect[i])) - ds.begin();
        res = max(res, Get(R) - Get(L - 1));
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cout << Solve() << "\n";
    }
}

