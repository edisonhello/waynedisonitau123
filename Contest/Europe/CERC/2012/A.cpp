#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    vector<bool> vis(1 << 20);
    while (T--) {
        int N;
        cin >> N;
        vector<vector<int>> D(N, vector<int>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> D[i][j];
            }
        }
        fill(vis.begin(), vis.begin() + (1 << N), false);
        vector<int> que(1, (1 << N) - 1);
        vis[(1 << N) - 1] = true;
        for (int it = 0; it < que.size(); ++it) {
            int mask = que[it];
            for (int i = 0; i < N; ++i) {
                if (mask >> i & 1) {
                    int sum = 0;
                    for (int j = 0; j < N; ++j) {
                        if (mask >> j & 1) sum -= D[i][j];
                    }
                    if (sum < 0) {
                        if (!vis[mask ^ (1 << i)]) {
                            vis[mask ^ (1 << i)] = true;
                            que.push_back(mask ^ (1 << i));
                        }
                    }
                }
            }
        }
        vector<int> res;
        for (int i = 0; i < N; ++i) {
            if (vis[1 << i]) {
                res.push_back(i);
            }
        }
        if (res.empty()) {
            cout << "0\n";
        } else {
            for (int u : res) cout << u + 1 << " ";
            cout << "\n";
        }
    }
}

