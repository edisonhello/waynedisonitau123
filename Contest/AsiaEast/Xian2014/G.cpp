#include <bits/stdc++.h>
using namespace std;

int64_t Solve() {
    string S, T;
    cin >> S >> T;

    constexpr int kMod1 = 1'000'000'000 + 123;
    constexpr int kMod2 = 1'000'000'000 + 87;
    constexpr int kP1 = 87;
    constexpr int kP2 = 131;

    int N = max(S.size(), T.size());
    vector<int> pw1(N + 1, 1);
    vector<int> pw2(N + 1, 1);
    for (int i = 1; i <= N; ++i) {
        pw1[i] = 1LL * pw1[i - 1] * kP1 % kMod1;
        pw2[i] = 1LL * pw2[i - 1] * kP2 % kMod2;
    }

    auto Get = [&](const string &S) {
        vector<int> link, len, dp, hv1, hv2;
        vector<vector<int>> nxt;

        auto Add1 = [&](int h, int l, int c) {
            int X = (1LL * c * pw1[l] + h) % kMod1;
            X = (1LL * X * kP1 + c) % kMod1;
            return X;
        };
        auto Add2 = [&](int h, int l, int c) {
            int X = (1LL * c * pw2[l] + h) % kMod2;
            X = (1LL * X * kP2 + c) % kMod2;
            return X; 
        };

        auto Node = [&](int l, int fl = -1, int ch = -1, int fr = -1) {
            // cout << "Push ch = " << ch << endl;
            int s = link.size();
            len.push_back(l);
            link.push_back(fl);
            nxt.emplace_back(26, -1);
            dp.push_back(0);
            if (l <= 0) {
                hv1.push_back(0); 
                hv2.push_back(0); 
            } else {
                if (l == 1) {
                    hv1.push_back(ch + 1);
                    hv2.push_back(ch + 1);
                } else {
                    hv1.push_back(Add1(hv1[fr], len[fr], ch + 1));
                    hv2.push_back(Add2(hv2[fr], len[fr], ch + 1));
                }
            }
            return s;
        };

        int sf = 1;
        Node(-1, 0);
        Node(0, 0);

        auto Push = [&](int p) {
            int cur = sf, z = S[p] - 'a';
            while (p - 1 - len[cur] < 0 || S[p - 1 - len[cur]] != S[p]) {
                cur = link[cur];
            }
            if (nxt[cur][z] != -1) {
                sf = nxt[cur][z];
            } else {
                int ch = Node(len[cur] + 2, -1, z, cur);
                nxt[cur][z] = sf = ch;
                if (len[ch] == 1) {
                    link[ch] = 1;
                } else {
                    cur = link[cur];
                    while (p - 1 - len[cur] < 0 || S[p - 1 - len[cur]] != S[p]) {
                        cur = link[cur];
                    }
                    link[ch] = nxt[cur][z];
                }
            }
            ++dp[sf];
        };

        for (int i = 0; i < S.size(); ++i) Push(i);
        for (int i = link.size() - 1; i >= 0; --i) {
            if (link[i] != -1) {
                dp[link[i]] += dp[i];
            }
        }

        vector<pair<pair<int, int>, int>> res;
        for (int i = 2; i < hv1.size(); ++i) {
            res.emplace_back(make_pair(hv1[i], hv2[i]), dp[i]);
        }
        return res;
    };

    auto X = Get(S);
    auto Y = Get(T);

    auto Debug = [&](auto X) {
        cout << "debug\n";
        for (auto u : X) cout << "(" << u.first << ", " << u.second << ")\n";
    };

    // Debug(X);
    // Debug(Y);

    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());

    int64_t res = 0;
    for (int i = 0, j = 0; i < X.size(); ++i) {
        while (j < Y.size() && Y[j].first < X[i].first) j++;
        if (j < Y.size() && Y[j].first == X[i].first) {
            res += 1LL * Y[j].second * X[i].second;
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cout << "Case #" << tc << ": " << Solve() << "\n";
    }
}

