#include <bits/stdc++.h>
using namespace std;

vector<int> g[10005];

int mark[10005];

bool ok(int n, int marked) {
    while (true) {
        int _ = marked;

        for (int i = 0; i < n; ++i) if (g[i].size() > 1u) {
            int cnt = 0;
            for (int j : g[i]) {
                cnt += mark[j];
            }
            // cerr << "looking i = " << i << ", cnt = " << cnt << endl;
            if (cnt == (int)g[i].size() - 1) {
                // cerr << "cnt = " << cnt << ", size = " << g[i].size() << endl;
                for (int j : g[i]) if (!mark[j]) {
                    mark[j] = 1;
                    ++marked;
                    // cerr << "new mark " << j << " base on " << i << endl;
                }
            }
        }

        if (_ == marked) break;
    }
    // cerr << "marked = " << marked << endl;
    return marked == n;
}

int main() {
    int n; cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int mn = n;
    for (int i = 0; i < (1 << n); ++i) {
        // cerr << "new case!" << endl;
        int marked = 0;
        for (int j = 0; j < n; ++j) mark[j] = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                if (!mark[j]) {
                    mark[j] = 1;
                    ++marked;
                }
                // cerr << "initial pick " << j << endl;
                for (int k : g[j]) {
                    // cerr << "mark " << k << endl;
                    if (!mark[k]) {
                        mark[k] = 1;
                        ++marked;
                    }
                }
            }
        }

        if (ok(n, marked)) mn = min(mn, __builtin_popcount(i));
    }

    cout << mn << endl;
}
