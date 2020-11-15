#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int pw1[1'000'000];
int pw2[1'000'000];
int pref1[1'000'000];
int pref2[1'000'000];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    constexpr int kP1 = 1'000'000'000 + 123;
    constexpr int kP2 = 1'000'000'000 + 87;
    constexpr int kQ1 = 7122;
    constexpr int kQ2 = 880301;
    pw1[0] = pref1[0] = pw2[0] = pref2[0] = 1;
    for (int i = 1; i <= N; ++i) {
        pw1[i] = 1LL * pw1[i - 1] * kQ1 % kP1;
        pref1[i] = (pref1[i - 1] + pw1[i]) % kP1;
        pw2[i] = 1LL * pw2[i - 1] * kQ2 % kP2;
        pref2[i] = (pref2[i - 1] + pw2[i]) % kP2;
    }

    struct Node {
        int Max, Hash1, Hash2, Size;

        Node() = default;
        Node(int v) : Max(v), Hash1(v), Hash2(v), Size(1) {}
        Node(int M, int H1, int H2, int S) : Max(M), Hash1(H1), Hash2(H2), Size(S) {}

        Node operator+(const Node &R) const {
            int H1 = (1LL * Hash1 * pw1[R.Size] + R.Hash1) % kP1;
            int H2 = (1LL * Hash2 * pw2[R.Size] + R.Hash2) % kP2;
            return Node(max(Max, R.Max), H1, H2, Size + R.Size);
        }

        void Increment(int Val) {
            Max += Val;
            Hash1 = (Hash1 + 1LL * Val * pref1[Size - 1]) % kP1;
            Hash2 = (Hash2 + 1LL * Val * pref2[Size - 1]) % kP2;
        }
    };

    vector<Node> Tree(N * 4);
    vector<int> tag(N * 4);

    auto Build = [&]() {
        auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
            if (r - l == 1) {
                Tree[o] = Node(A[l]);
                return;
            }
            int m = (l + r) >> 1;
            dfs(dfs, l, m, o * 2 + 1);
            dfs(dfs, m, r, o * 2 + 2);
            Tree[o] = Tree[o * 2 + 1] + Tree[o * 2 + 2];
        };

        return dfs(dfs, 0, N);
    };

    constexpr int kM = 65536;

    auto CollectMax = [&](int ql, int qr) {
        vector<int> Idx;
        auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
            if (l >= qr || ql >= r) return;
            if (Tree[o].Max < kM - 1) return;
            if (l >= ql && r <= qr) {
                auto collect = [&](auto rec, int tl, int tr, int o) -> void {
                    if (tr - tl == 1) {
                        Idx.push_back(tl);
                        return;
                    }
                    int tm = (tl + tr) >> 1;
                    if (tag[o] > 0) {
                        for (int k = 1; k <= 2; ++k) {
                            Tree[o * 2 + k].Increment(tag[o]);
                            tag[o * 2 + k] += tag[o];
                        }
                        tag[o] = 0;
                    }
                    if (Tree[o * 2 + 1].Max == kM - 1) rec(rec, tl, tm, o * 2 + 1);
                    if (Tree[o * 2 + 2].Max == kM - 1) rec(rec, tm, tr, o * 2 + 2);
                };
                collect(collect, l, r, o);
                return;
            }
            if (tag[o] > 0) {
                for (int k = 1; k <= 2; ++k) {
                    Tree[o * 2 + k].Increment(tag[o]);
                    tag[o * 2 + k] += tag[o];
                }
                tag[o] = 0;
            }
            int m = (l + r) >> 1;
            dfs(dfs, l, m, o * 2 + 1);
            dfs(dfs, m, r, o * 2 + 2);
        };

        dfs(dfs, 0, N);
        return Idx;
    };

    auto Reset = [&](int p) {
        auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
            if (r - l == 1) {
                Tree[o] = Node(0);
                return;
            }
            if (tag[o] > 0) {
                for (int k = 1; k <= 2; ++k) {
                    Tree[o * 2 + k].Increment(tag[o]);
                    tag[o * 2 + k] += tag[o];
                }
                tag[o] = 0;
            }
            int m = (l + r) >> 1;
            if (p < m) dfs(dfs, l, m, o * 2 + 1);
            else dfs(dfs, m, r, o * 2 + 2);
            Tree[o] = Tree[o * 2 + 1] + Tree[o * 2 + 2];
        };
        dfs(dfs, 0, N);
    };

    auto RangeAdd = [&](int ql, int qr) {
        auto dfs = [&](auto dfs, int l, int r, int o = 0) -> void {
            if (l >= qr || ql >= r) return;
            if (l >= ql && r <= qr) {
                Tree[o].Increment(1);
                tag[o] += 1;
                return;
            }
            if (tag[o] > 0) {
                for (int k = 1; k <= 2; ++k) {
                    Tree[o * 2 + k].Increment(tag[o]);
                    tag[o * 2 + k] += tag[o];
                }
                tag[o] = 0;
            }
            int m = (l + r) >> 1;
            dfs(dfs, l, m, o * 2 + 1);
            dfs(dfs, m, r, o * 2 + 2);
            Tree[o] = Tree[o * 2 + 1] + Tree[o * 2 + 2];
        };

        return dfs(dfs, 0, N);
    };

    auto Query = [&](int ql, int qr) {
        auto dfs = [&](auto dfs, int l, int r, int o = 0) -> Node {
            if (l >= ql && r <= qr) return Tree[o];
            if (tag[o] > 0) {
                for (int k = 1; k <= 2; ++k) {
                    Tree[o * 2 + k].Increment(tag[o]);
                    tag[o * 2 + k] += tag[o];
                }
                tag[o] = 0;
            }
            int m = (l + r) >> 1;
            if (qr <= m) return dfs(dfs, l, m, o * 2 + 1);
            if (ql >= m) return dfs(dfs, m, r, o * 2 + 2);
            return dfs(dfs, l, m, o * 2 + 1) + dfs(dfs, m, r, o * 2 + 2);
        };

        return dfs(dfs, 0, N);
    };

    Build();

    for (int i = 0; i < Q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int L, R;
            cin >> L >> R;
            L--;
            auto Idx = CollectMax(L, R);
            RangeAdd(L, R);
            for (int u : Idx) Reset(u);
        } else {
            int x, y, L;
            cin >> x >> y >> L;
            x--;
            y--;
            auto A = Query(x, x + L);
            auto B = Query(y, y + L);
            if (A.Hash1 == B.Hash1 && A.Hash2 == B.Hash2) cout << "yes\n";
            else cout << "no\n";
        }
    }
}

