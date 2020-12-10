#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        int N;
        cin >> N;
        vector<pair<int, int>> V;
        for (int i = 0; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            V.emplace_back(x, y);
        }
        sort(V.begin(), V.end());

        constexpr int kP = 1'000'000'000 + 7;

        auto Dfs = [&](auto dfs, int x, int64_t D = 0) -> pair<int, int> {
            int64_t A = D;
            auto it = lower_bound(V.begin(), V.end(), make_pair(x, -1));
            if (it != V.end() && it->first == x) A += it->second;
            if (A == 0) {
                if (it == V.end()) return make_pair(1, 2);
                auto q = dfs(dfs, it->first, 0);
                return make_pair(q.first, 2 * q.first % kP);
            }

            int64_t E = 0;
            pair<int, int> res;
            if (A % 2 == 0) {
                if (A / 2 - 1 > 0) E = A / 2 - 1;
                auto p = dfs(dfs, x + 1, E);
                res = make_pair((p.first + p.second) % kP, p.second * 2 % kP);
            } else {
                if (A / 2 > 0) E = A / 2;
                auto p = dfs(dfs, x + 1, E);
                res = make_pair(p.first * 2 % kP, (p.first + p.second) % kP);
            }
            return res;
        };

        cout << Dfs(Dfs, V[0].first).first << "\n";
    }
    return 0;
}

