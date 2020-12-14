#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<vector<int>> Dv(200000 + 1);
    for (int i = 1; i <= 200000; ++i) {
        for (int j = i; j <= 200000; j += i) {
            Dv[j].push_back(i);
        }
    }
    vector<vector<int>> Adj(200000 + 1);
    for (int i = 1; i <= 200000; ++i) {
        for (int u : Dv[i]) {
            int j = i - u;
            if (j <= 0) continue;
            if (__gcd(i, j) == (i ^ j)) {
                Adj[i].push_back(j);
                Adj[j].push_back(i);
            }
        }
    }

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    vector<int> A(N + M);
    for (int i = 0; i < N; ++i) cin >> A[i];
    vector<int> uf(N + M);
    iota(uf.begin(), uf.end(), 0);
    vector<map<int, int>> cnt(N + M);
    vector<int64_t> ans(N + M);

    function<int(int)> Find = [&](int x) {
        if (x == uf[x]) return x;
        return uf[x] = Find(uf[x]);
    };

    for (int i = 0; i < N; ++i) cnt[i][A[i]] = 1;

    int64_t Res = 0;
    for (int i = 0; i < M; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, v;
            cin >> x >> v;
            x--;
            A[x] = v;
            cnt[x][A[x]] = 1;
        }
        if (t == 2) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            x = Find(x);
            y = Find(y);
            if (x != y) {
                if (cnt[x].size() > cnt[y].size()) swap(x, y);
                Res -= ans[x] + ans[y];
                for (auto [u, c] : cnt[x]) {
                    for (int v : Adj[u]) {
                        if (cnt[y].find(v) != cnt[y].end()) ans[y] += 1LL * c * cnt[y][v];
                    }
                }
                for (auto [u, c] : cnt[x]) cnt[y][u] += c;
                ans[y] += ans[x];
                Res += ans[y];
                uf[x] = y;
            }
        }
        if (t == 3) {
            int x, v;
            cin >> x >> v;
            x--;
            int y = Find(x);
            Res -= ans[y];
            for (int u : Adj[A[x]]) {
                if (cnt[y].find(u) != cnt[y].end()) ans[y] -= cnt[y][u];
            }
            cnt[y][A[x]]--;
            A[x] = v;
            for (int u : Adj[A[x]]) {
                if (cnt[y].find(u) != cnt[y].end()) ans[y] += cnt[y][u];
            }
            cnt[y][A[x]]++;
            Res += ans[y];
        }
        cout << Res << "\n";
    }
    return 0;
}

