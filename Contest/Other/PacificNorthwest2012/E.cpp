#include <bits/stdc++.h>
#define int int64_t
using namespace std;

void Solve() {
    int N, M;
    cin >> N >> M;
    vector<tuple<int, int, int>> V;
    for (int i = 0; i < M; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        assert(d == 0);
        V.emplace_back(a, b, c);
    }
    vector<vector<pair<int, int>>> constraints(2 * N);
    bool Null = false, Miss = false, Rep = false;
    for (int i = 0; i < M; ++i) {
        int a, b, c;
        tie(a, b, c) = V[i];
        if (a == 0 || b == 0 || c == 0) {
            Null = true;
            continue;
        }
        int x = abs(a), y = abs(b), z = abs(c);
        if (x > N || y > N || z > N) {
            Miss = true;
            continue;
        }
        if (x == y || y == z || x == z) {
            Rep = true;
            continue;
        }
        vector<int> W = {a, b, c};
        sort(W.begin(), W.end(), [&](int a, int b) { return abs(a) < abs(b); });
        W[0] = W[0] > 0 ? W[0] - 1 : ~(-W[0] - 1);
        W[1] = W[1] > 0 ? W[1] - 1 : ~(-W[1] - 1);
        W[2] = W[2] > 0 ? W[2] - 1 : ~(-W[2] - 1);
        if (W[2] >= 0) {
            constraints[W[2]].emplace_back(W[0], W[1]);
        } else {
            constraints[~W[2] + N].emplace_back(W[0], W[1]);
        }
    }

    if (Null) {
        cout << "INVALID: NULL RING\n";
        return;
    }
    if (Miss) {
        cout << "INVALID: RING MISSING\n";
        return;
    }
    if (Rep) {
        cout << "INVALID: RUNE CONTAINS A REPEATED RING\n";
        return;
    }

    vector<bool> True(N);

    function<bool(int)> Dfs = [&](int p) {
        if (p == N) return true;
        bool Y = true;
        True[p] = false;
        for (auto X : constraints[p]) {
            bool Ok = false;
            if (X.first >= 0 && True[X.first]) Ok = true;
            if (X.first < 0 && !True[~X.first]) Ok = true;
            if (X.second >= 0 && True[X.second]) Ok = true;
            if (X.second < 0 && !True[~X.second]) Ok = true;
            Y &= Ok;
        }
        if (Y && Dfs(p + 1)) return true;
        True[p] = true;
        Y = true;
        for (auto X : constraints[p + N]) {
            bool Ok = false;
            if (X.first >= 0 && True[X.first]) Ok = true;
            if (X.first < 0 && !True[~X.first]) Ok = true;
            if (X.second >= 0 && True[X.second]) Ok = true;
            if (X.second < 0 && !True[~X.second]) Ok = true;
            Y &= Ok;
        }
        if (Y && Dfs(p + 1)) return true;
        return false;
    };

    if (Dfs(0)) cout << "RUNES SATISFIED!\n";
    else cout << "RUNES UNSATISFIABLE! TRY ANOTHER GATE!\n";
}

int32_t main() {
    int T;
    cin >> T;
    while (T--) {
        Solve();
    }
}
