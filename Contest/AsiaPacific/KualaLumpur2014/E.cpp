#include <bits/stdc++.h>
using namespace std;

using Bitset = bitset<5000>;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N, M;
        cin >> N >> M;
        vector<Bitset> adj(N);
        vector<int> st(M), ed(M);
        vector<int> deg(N);
        for (int i = 0; i < M; ++i) {
            cin >> st[i] >> ed[i];
            st[i]--;
            ed[i]--;
            adj[st[i]].set(ed[i]);
            adj[ed[i]].set(st[i]);
            deg[st[i]]++;
            deg[ed[i]]++;
        }
        int64_t A = 1LL * M * (N - 2), B = 0;
        for (int i = 0; i < N; ++i) {
            B += 1LL * deg[i] * (deg[i] - 1) / 2;
        }
        int64_t Z = 0;
        for (int i = 0; i < M; ++i) {
            Z += (adj[st[i]] & adj[ed[i]]).count();
        }
        assert(Z % 3 == 0);
        Z /= 3;
        cout << "Case #" << t << ": " << 1LL * N * (N - 1) * (N - 2) / 6 - (A - B + Z) << "\n";
    }
}
