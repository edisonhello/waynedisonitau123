#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("simplicity.in", "r", stdin);
    freopen("simplicity.out", "w", stdout);
    int N;
    cin >> N;
    vector<string> adj(N);
    for (int i = 0; i < N; ++i) cin >> adj[i];
    int K;
    cin >> K;
    vector<int> S(K);
    vector<int> which(N, -1);
    for (int i = 0; i < K; ++i) {
        cin >> S[i];
        S[i]--;
        which[S[i]] = i;
    }

    vector<int> D(N);
    vector<int> Y;
    for (int i = 0; i < N; ++i) {
        if (which[i] == -1) Y.push_back(i);
    }
    for (int u : Y) {
        for (int v : Y) {
            if (adj[u][v] == '1') D[u]++;
        }
    }
    sort(Y.begin(), Y.end(), [&D](int i, int j) { return D[i] > D[j]; });
    for (int i = 0; i < Y.size(); ++i) {
        for (int j = i + 1; j < Y.size(); ++j) assert(adj[Y[i]][Y[j]] == '1');
    }

    vector<int> Attach(N);
    vector<bool> Bad(N);
    vector<vector<int>> dp(N, vector<int>(K + 1));
    vector<vector<int>> from(N, vector<int>(K + 1));

    int best = K;
    vector<int> T = S;
    vector<bool> L(N);

    for (int s = 1; s < (1 << K); ++s) {
        vector<int> X;
        for (int i = 0; i < K; ++i) {
            if (s >> i & 1) X.push_back(i); 
        }
        vector<int> deg(K);
        for (int u : X) {
            for (int v : X) {
                if (adj[S[u]][S[v]] == '1') {
                    deg[u]++;
                }
            }
        }
        sort(X.begin(), X.end(), [&deg](int i, int j) { return deg[i] > deg[j]; });
        bool Fail = false;
        for (int i = 0; i < X.size(); ++i) {
            for (int j = i + 1; j < X.size(); ++j) {
                Fail |= adj[S[X[i]]][S[X[j]]] == '0';
            }
        }
        if (Fail) continue;
        if (Y.empty()) {
            if (K - X.size() < best) {
                best = K - X.size();
                T.clear();
                for (int i = 0; i < K; ++i) {
                    if (!(s >> i & 1)) T.push_back(S[i]);
                }
            }
            continue;
        }
        fill(Bad.begin(), Bad.end(), false);
        for (int i = 0; i < Y.size(); ++i) {
            int H = X.size();
            for (int j = 0; j < X.size(); ++j) {
                if (adj[Y[i]][S[X[j]]] == '1') {
                    H = j;
                    break;
                }
            }
            bool F = false;
            for (int j = H + 1; j < X.size(); ++j) {
                if (adj[Y[i]][S[X[j]]] == '0') {
                    F = true;
                    break;
                }
            }
            if (F) Bad[Y[i]] = true;
            Attach[Y[i]] = H;
        }
        for (int i = 0; i < Y.size(); ++i) {
            iota(from[i].begin(), from[i].end(), 0);
            if (i > 0) {
                copy(dp[i - 1].begin(), dp[i - 1].end(), dp[i].begin());
            } else {
                fill(dp[i].begin(), dp[i].end(), 0);
            }
            if (Bad[Y[i]]) continue;
            dp[i][Attach[Y[i]]]++;
            for (int j = 1; j <= K; ++j) {
                if (dp[i][j - 1] > dp[i][j]) {
                    from[i][j] = from[i][j - 1];
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
        if (K - X.size() + Y.size() - dp[Y.size() - 1][K] < best) {
            best = K - X.size() + Y.size() - dp[Y.size() - 1][K];
            int A = Y.size() - 1, B = K;
            fill(L.begin(), L.end(), false);
            while (A >= 0 && B >= 0) {
                if (from[A][B] == B && dp[A][B] > (A > 0 ? dp[A - 1][B] : 0)) L[A] = true;
                if (from[A][B] == B) A--;
                else B = from[A][B];
            }
            vector<int> New;
            for (int i = 0; i < K; ++i) {
                if (!(s >> i & 1)) New.push_back(S[i]);
            }
            for (int i = 0; i < Y.size(); ++i) {
                if (!L[i]) New.push_back(Y[i]);
            }
            T = New;
        }
    }
    cout << best << "\n";
    assert(best == T.size());
    for (int u : T) cout << u + 1 << " ";
    cout << "\n";
    return 0;
}

