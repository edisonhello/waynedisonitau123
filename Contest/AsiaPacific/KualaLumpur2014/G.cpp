#include <bits/stdc++.h>
using namespace std;

int Solve() {
    int N, M, B;
    cin >> N >> M >> B;
    vector<int> cost(26, -1);
    vector<int> which(26, -1);
    for (int i = 0; i < N; ++i) {
        string H;
        int C;
        cin >> H >> C;
        assert(H.size() == 1);
        cost[i] = C;
        which[H[0] - 'A'] = i;
    }

    vector<vector<int>> Child;
    vector<int> Fail, Profit;

    auto GetNode = [&]() {
        int z = Child.size();
        Child.emplace_back(N, -1);
        Fail.push_back(-1);
        Profit.push_back(0);
        return z;
    };

    int root = GetNode();

    for (int i = 0; i < M; ++i) {
        string S;
        cin >> S;
        for (int j = 0; j < S.size(); ++j) {
            assert(which[S[j] - 'A'] != -1);
            S[j] = which[S[j] - 'A'];
        }
        int W;
        cin >> W;
        int X = root;
        for (int j = 0; j < S.size(); ++j) {
            if (Child[X][S[j]] == -1) {
                Child[X][S[j]] = GetNode();
            }
            X = Child[X][S[j]];
        }
        // cerr << "ends at X = " << X << endl;
        Profit[X] += W;
    }
    vector<int> que(1, root);
    for (int it = 0; it < que.size(); ++it) {
        int X = que[it];
        for (int i = 0; i < N; ++i) {
            if (Child[X][i] == -1) continue;
            int p = Child[X][i], fp = Fail[X];
            while (fp != -1 && Child[fp][i] == -1) fp = Fail[fp];
            int pd = fp != -1 ? Child[fp][i] : root;
            Fail[p] = pd;
            que.push_back(p);
        }
    }

    int K = Child.size();
    vector<vector<int>> To(K);
    for (int i = 0; i < K; ++i) {
        if (Fail[i] >= 0) To[Fail[i]].push_back(i);
    }
    for (int i = 0; i < K; ++i) {
        for (int u : To[i]) Profit[u] += Profit[i];
    }
    // for (int i = 0; i < K; ++i) cerr << Profit[i] << " " << Fail[i] << endl;

    vector<vector<int>> dp(K, vector<int>(B + 1));
    for (int b = 1; b <= B; ++b) {
        for (int i = 0; i < K; ++i) {
            dp[i][b] = dp[i][b - 1];
            for (int j = 0; j < N; ++j) {
                if (Child[i][j] != -1) {
                    if (b >= cost[j]) {
                        dp[i][b] = max(dp[i][b], dp[Child[i][j]][b - cost[j]] + Profit[Child[i][j]]);
                    }
                } else {
                    if (i == root) continue;
                    int z = Fail[i];
                    while (z != root && Child[z][j] == -1) z = Fail[z];
                    int p = Child[z][j] == -1 ? root : Child[z][j];
                    if (b >= cost[j]) {
                        dp[i][b] = max(dp[i][b], dp[p][b - cost[j]] + Profit[p]);
                    }
                }
            }
            // cerr << "dp[" << i << "][" << b << "] = " << dp[i][b] << endl;
        }
    }
    return dp[0][B];
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        cout << Solve() << "\n";
    }
}
