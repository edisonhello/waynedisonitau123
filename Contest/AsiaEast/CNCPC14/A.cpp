#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(N);
        vector<bool> Vis(1 << 18), Used(1 << 18);
        vector<int> Which(1 << 18, -1);
        vector<int> uf(N);
        iota(uf.begin(), uf.end(), 0);

        function<int(int)> Find = [&](int x) {
            if (x == uf[x]) return x;
            return uf[x] = Find(uf[x]);
        };

        vector<vector<int>> g(N);

        for (int i = 0; i < N; ++i) {
            cin >> A[i];
            Vis[A[i]] = true;
            if (Which[A[i]] != -1) {
                uf[Find(i)] = Find(Which[A[i]]); 
                g[i].push_back(Which[A[i]]);
                g[Which[A[i]]].push_back(i);
            }
            Which[A[i]] = i;
        }
        vector<queue<int>> Que(18);
        vector<int> Dist(1 << 18, 20);
        vector<int> From(1 << 18, -1);
        Dist[A[0]] = 0;
        Que[0].push(A[0]);
        From[A[0]] = A[0];
        vector<pair<int, int>> Edges;
        while (true) {
            bool NonEmpty = false;
            for (int i = 0; i < 18; ++i) {
                if (!Que[i].empty()) {
                    NonEmpty = true;
                    int x = Que[i].front();
                    Que[i].pop();
                    if (!Used[x]) {
                        Used[x] = true;
                        for (int j = 0; j < 18; ++j) {
                            int y = x ^ (1 << j);
                            if (Vis[y]) {
                                Edges.emplace_back(From[x], y);
                                if (Dist[y] > 0) {
                                    Dist[y] = 0;
                                    From[y] = y;
                                    Que[Dist[y]].push(y);
                                }
                            }
                            if (Dist[y] <= Dist[x] + 1) continue;
                            Dist[y] = Dist[x] + 1;
                            From[y] = From[x];
                            Que[Dist[y]].push(y);
                        }
                    }
                    break;
                }
            }
            if (!NonEmpty) break;
        }
        sort(Edges.begin(), Edges.end(), [&](auto X, auto Y) {
            int A = __builtin_popcount(X.first ^ X.second);
            int B = __builtin_popcount(Y.first ^ Y.second);
            return A < B;
        });

        int MST = 0;

        for (int i = 0; i < Edges.size(); ++i) {
            int X = Edges[i].first;
            int Y = Edges[i].second;
            if (Find(Which[X]) != Find(Which[Y])) {
                MST += __builtin_popcount(X ^ Y);
                X = Which[X];
                Y = Which[Y];
                g[X].push_back(Y);
                g[Y].push_back(X);
                uf[Find(X)] = Find(Y);
            }
        }
        for (int i = 0; i < N; ++i) assert(Find(i) == Find(0));
        cout << MST << "\n";

        vector<int> Parent(N, -1);
        vector<int> Order;
        auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
            Parent[x] = p;
            Order.push_back(x);
            for (int u : g[x]) {
                if (u == p) continue;
                dfs(dfs, u, x);
           } 
        };

        Dfs(Dfs, 0);
        for (int u : Order) cout << u + 1 << " ";
        cout << "\n";
        cout << 1 << " ";
        for (int i = 1; i < N; ++i) cout << Parent[Order[i]] + 1 << " ";
        cout << "\n";
    }
}

