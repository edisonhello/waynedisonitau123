#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N, M;
        cin >> N >> M;
        vector<int> st(M), ed(M), w(M);
        for (int i = 0; i < M; ++i) {
            cin >> st[i] >> ed[i] >> w[i];
            st[i]--;
            ed[i]--;
        }
        vector<int> order(M);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int i, int j) { return w[i] > w[j]; });

        vector<int> uf(N);
        iota(uf.begin(), uf.end(), 0);

        function<int(int)> Find = [&](int x) {
            if (x == uf[x]) return x;
            return uf[x] = Find(uf[x]);
        };

        int64_t MST = 0;
        int V = 0;
        for (int i = 0; i < M; ++i) {
            int x = Find(st[order[i]]), y = Find(ed[order[i]]);
            if (x == y) {
                V = max(V, w[order[i]]);
                continue;
            }
            MST += w[order[i]];
            uf[x] = y;
        }
        MST = accumulate(w.begin(), w.end(), 0LL) - MST;
        cout << "Case #" << t << ": " << MST << " " << V << "\n";
    }
}
