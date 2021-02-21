#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<vector<int>> g(N);
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> Max(N), Min(N);
    vector<bool> IsBinary(N);

    auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
        Max[x] = Min[x] = x;
        vector<int> child;
        for (int u : g[x]) {
            if (u == p) continue;
            dfs(dfs, u, x);
            Max[x] = max(Max[x], Max[u]);
            Min[x] = min(Min[x], Min[u]);
            child.push_back(u);
        }
        if (child.size() <= 2) {
            IsBinary[x] = true;
            for (int u : child) {
                if (!IsBinary[u]) IsBinary[x] = false;
            }
            bool Ok = false;
            if (child.size() == 0) {
                Ok = true;
            } else if (child.size() == 1) {
                if (Max[child[0]] < x || Min[child[0]] > x) Ok = true;
            } else {
                for (int i = 0; i < 2; ++i) {
                    if (Max[child[0]] < x && Min[child[1]] > x) Ok = true;
                    swap(child[0], child[1]);
                }
            }
            if (!Ok) IsBinary[x] = false;
        }
    };

    Dfs(Dfs, 0);
    vector<int> ans;
    if (IsBinary[0]) ans.push_back(0);

    auto Dfs2 = [&](auto dfs, int x, int Mx, int Mn, int p = -1) -> void {
        vector<int> child;
        for (int u : g[x]) {
            if (u == p) continue;
            child.push_back(u);
        }
        if (x != 0) {
            if (child.size() == 0) {
                if (x == N - 1) ans.push_back(x);
            } else if (child.size() == 1) {
                if (Max[child[0]] < x && IsBinary[child[0]]) {
                    if (Mn > x) ans.push_back(x);
                } else if (Min[child[0]] > x && IsBinary[child[0]]) {
                    if (Mx < x) ans.push_back(x);
                }
            }
        }
        if (child.size() > 3) return;
        if (child.size() == 0) return;
        if (child.size() == 1) {
            if (Mx < x || Mn > x) dfs(dfs, child[0], max(Mx, x), min(Mn, x), x);
        } else if (child.size() == 2) {
            for (int i = 0; i < 2; ++i) {
                int nchild = child[i ^ 1];
                if (!IsBinary[nchild]) continue;
                if (Max[nchild] < x && Mn > x)
                    dfs(dfs, child[i], max(Mx, max(x, Max[nchild])), min(Mn, min(x, Min[nchild])), x);
                else if (Min[nchild] > x && Mx < x)
                    dfs(dfs, child[i], max(Mx, max(x, Max[nchild])), min(Mn, min(x, Min[nchild])), x);
            }
        } else {
            if (x != 0) return;
            for (int i = 0; i < 3; ++i) {
                vector<int> nchild;
                for (int j = 0; j < 3; ++j) {
                    if (i != j) nchild.push_back(child[j]);
                }
                bool IsAlmostBinary = IsBinary[nchild[0]] && IsBinary[nchild[1]];
                bool Ok = false;
                for (int j = 0; j < 2; ++j) {
                    if (Max[nchild[0]] < x && Min[nchild[1]] > x) Ok = true;
                    swap(nchild[0], nchild[1]);
                }
                if (!Ok) IsAlmostBinary = false;
                if (IsAlmostBinary) {
                    int Mxx = max(Mx, x);
                    int Mnn = min(Mn, x);
                    Mxx = max(Mxx, max(Max[nchild[0]], Max[nchild[1]]));
                    Mnn = min(Mnn, min(Min[nchild[0]], Min[nchild[1]]));
                    dfs(dfs, child[i], Mxx, Mnn, x);
                }
            }
        }
    };

    Dfs2(Dfs2, 0, -1, N);

    if (ans.empty()) {
        cout << "-1\n";
    } else {
        sort(ans.begin(), ans.end());
        for (int u : ans) cout << u + 1 << " ";
        cout << "\n";
    }
    return 0;
}

