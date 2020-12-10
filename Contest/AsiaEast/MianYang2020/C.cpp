#include <bits/stdc++.h>
using namespace std;

int Solve() {
    int N;
    cin >> N;
    vector<vector<int>> Trie;
    vector<int> Value;
    Trie.emplace_back(26, -1);
    Value.emplace_back(-1);
    bool Fuck = false;
    for (int i = 0; i < N; ++i) {
        string S;
        int V;
        cin >> S >> V;
        int x = 0;
        for (int j = 0; j < S.size(); ++j) {
            if (Trie[x][S[j] - 'a'] == -1) {
                int z = Trie.size();
                Trie.emplace_back(26, -1);
                Value.emplace_back(-1);
                Trie[x][S[j] - 'a'] = z;
            }
            x = Trie[x][S[j] - 'a'];
        }
        if (Value[x] != -1 && Value[x] != V) Fuck = true;
        Value[x] = V;
    }
    if (Fuck) return -1;
    int M = Trie.size();
    vector<set<int>> dp(M);
    vector<bool> Used(M + 1);
    for (int u : Value) if (u <= M && u != -1) Used[u] = true;

    int ptr = 1;
    auto Dfs = [&](auto dfs, int x) -> bool {
        int D = -1;
        map<int, int> C, E;
        int Child = 0;
        bool Pure = false;
        for (int i = 0; i < 26; ++i) {
            if (Trie[x][i] != -1) {
                Child++;
                if (!dfs(dfs, Trie[x][i])) return false;
                if (dp[Trie[x][i]].size() == 1) {
                    int y = *dp[Trie[x][i]].begin();
                    if (C.find(y) == C.end()) C[y] = 0;
                    C[y]++;
                    Pure = true;
                }
                if (dp[Trie[x][i]].size() > dp[x].size()) dp[x].swap(dp[Trie[x][i]]);
                for (int u : dp[Trie[x][i]]) {
                    if (dp[x].count(u)) {
                        if (D != -1 && D != u) return false;
                        D = u;
                        if (E.find(u) == E.end()) E[u] = 0;
                        E[u]++;
                    }
                    dp[x].insert(u);
                }
            }
        }
        if (D != -1) {
            if (Value[x] != -1 && D != Value[x]) return false;
            int ED = E.find(D) == E.end() ? 0 : E[D];
            assert(C[D] <= ED + 1);
            if (C[D] != ED + 1) return false;
        } else {
            if (Value[x] != -1 && dp[x].count(Value[x])) {
                assert(C[Value[x]] <= 1);
                if (C[Value[x]] != 1) return false;
            } else if (Value[x] != -1) {
                dp[x].insert(Value[x]);
            } else {
                if (!Pure) {
                    while (ptr <= M && Used[ptr]) ptr++;
                    assert(ptr <= M);
                    dp[x].insert(ptr);
                    Used[ptr] = true;
                }
            }
        }
        assert(!dp[x].empty());
        // cout << "Value[" << x << "] = " << Value[x] << endl;
        // cout << "dp[" << x << "] = ";
        // for (int u : dp[x]) cout << u << " ";
        // cout << endl;
        return true;
    };

    if (!Dfs(Dfs, 0)) return -1;
    return dp[0].size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        cout << Solve() << "\n";
    }
    return 0;
}

