#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

int Read() {
    int v = 0;
    char c = 0;
    while (c = getchar(), !isdigit(c));
    v = c - '0';
    while (c = getchar(), isdigit(c)) v = v * 10 + (c - '0');
    return v;
}

vector<int> Solve(vector<int> ql, vector<int> qr, vector<int> qk, vector<int> type, vector<int> H) {
    int N = H.size();
    vector<int> ds;
    for (int i = 0; i < N; ++i) {
        if (type[i] == 2) ds.push_back(H[i]);
    }
    if (ds.empty()) return vector<int>();
    sort(ds.begin(), ds.end());
    ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
    for (int i = 0; i < N; ++i) {
        if (type[i] == 2) H[i] = lower_bound(ds.begin(), ds.end(), H[i]) - ds.begin();
    }
    int M = ds.size();
    int Q = ql.size();
    for (int i = 0; i < Q; ++i) qk[i]--;

    int ptr = 0;
    vector<int> sum, lc, rc;

    auto Get = [&](int z = -1) {
        if (z == -1) {
            sum.push_back(0);
            lc.push_back(-1);
            rc.push_back(-1);
            return ptr++;
        } else {
            sum.push_back(sum[z]);
            lc.push_back(lc[z]);
            rc.push_back(rc[z]);
            return ptr++;
        }
    };

    auto Build = [&]() -> int {
        auto dfs = [&](auto dfs, int l, int r, int o = 0) -> int {
            int g = Get();
            if (r - l == 1) return g;
            int m = (l + r) >> 1;
            lc[g] = dfs(dfs, l, m);
            rc[g] = dfs(dfs, m, r);
            return g;
        };
        return dfs(dfs, 0, M);
    };

    auto Update = [&](int x, int p) {
        auto dfs = [&](auto dfs, int x, int l, int r) -> int {
            int y = Get(x);
            sum[y]++;
            if (r - l == 1) {
                return y;
            }
            int m = (l + r) >> 1;
            if (p < m) {
                lc[y] = dfs(dfs, lc[x], l, m);
            } else {
                rc[y] = dfs(dfs, rc[x], m, r);
            }
            sum[y] = sum[lc[y]] + sum[rc[y]];
            return y;
        };

        return dfs(dfs, x, 0, M);
    };

    vector<int> idx;
    for (int i = 0; i < N; ++i) {
        if (type[i] == 2) idx.push_back(i);
    }

    vector<int> root(idx.size() + 1);
    
    root[0] = Build();
    for (int i = 0; i < idx.size(); ++i) {
        root[i + 1] = Update(root[i], H[idx[i]]);
    }

    vector<int> res(Q);

    auto Query = [&](int ql, int qr, int qk) {
        auto dfs = [&](auto dfs, int l, int r, int x, int y) {
            if (r - l == 1) return l;
            int m = (l + r) >> 1;
            if (sum[lc[y]] - sum[lc[x]] <= qk) {
                qk -= sum[lc[y]] - sum[lc[x]];
                return dfs(dfs, m, r, rc[x], rc[y]);
            } else {
                return dfs(dfs, l, m, lc[x], lc[y]);
            }
        };

        return dfs(dfs, 0, M, root[ql], root[qr]);
    };

    for (int i = 0; i < Q; ++i) {
        int L = lower_bound(idx.begin(), idx.end(), ql[i]) - idx.begin();
        int R = lower_bound(idx.begin(), idx.end(), qr[i]) - idx.begin();
        res[i] = ds[Query(L, R, qk[i])];
    }

    // auto Dfs = [&](auto dfs, int L, int R, const vector<int> &p, const vector<int> &q) -> void {
    //     // cerr << "L = " << L << " R = " << R << endl;
    //     if (R - L == 1) {
    //         for (int u : q) res[u] = ds[L];
    //         return;
    //     }
    //     if (q.empty()) return;
    //     if (p.empty()) {
    //         // cout << "fuck" << endl;
    //         for (int u : q) res[u] = ds[R - 1];
    //         // cout << "fuck2" << endl;
    //         return;
    //     }
    //     int M = (L + R) >> 1;
    //     vector<int> V, W;
    //     for (int i = 0; i < p.size(); ++i) {
    //         if (H[p[i]] < M) {
    //             V.push_back(p[i]);
    //         } else {
    //             W.push_back(p[i]);
    //         }
    //     }
    //     vector<int> Lq, Rq;
    //     for (int i = 0; i < q.size(); ++i) {
    //         int cnt = lower_bound(V.begin(), V.end(), qr[q[i]]) - lower_bound(V.begin(), V.end(), ql[qr[i]]);
    //         if (cnt <= qk[q[i]]) {
    //             qk[q[i]] -= cnt;
    //             Rq.push_back(q[i]);
    //         } else {
    //             Lq.push_back(q[i]);
    //         }
    //     }
    //     dfs(dfs, L, M, V, Lq);
    //     dfs(dfs, M, R, W, Rq);
    // };

    return res;
}

void Solve() {
    int N = Read();
    int Q = Read();
    vector<int> h(N);
    for (int i = 0; i < N; ++i) {
        h[i] = Read();
    }
    vector<int> type(N);
    vector<vector<int>> pos(3);
    for (int i = 0; i < N; ++i) {
        type[i] = Read();
        type[i]--;
    }

    vector<vector<int>> pref(3, vector<int>(N + 1));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < N; ++j) {
            pref[i][j + 1] = pref[i][j] + (type[j] == i);
        }
    }
    // cout << "here" << endl;

    auto Merge = [&](auto X, auto Y) {
        return make_pair(max(X.first, Y.first), min(X.second, Y.second));
    };

    vector<vector<vector<pair<int, int>>>> sp(3);
    constexpr int kInf = 2'000'000'000;
    for (int i = 0; i < 3; ++i) {
        sp[i].emplace_back(N);
        for (int j = 0; j < N; ++j) {
            if (type[j] == i) {
                sp[i][0][j] = make_pair(h[j], h[j]);
            } else {
                sp[i][0][j] = make_pair(0, kInf);
            }
        }
        for (int k = 1; (1 << k) <= N; ++k) {
            sp[i].emplace_back(N);
            for (int j = 0; j + (1 << k) <= N; ++j) {
                sp[i][k][j] = Merge(sp[i][k - 1][j], sp[i][k - 1][j + (1 << (k - 1))]);
            }
        }
    }
    // cout << "here" << endl;

    auto Query = [&](const auto &sp, int L, int R) {
        int p = 31 - __builtin_clz(R - L);
        return Merge(sp[p][L], sp[p][R - (1 << p)]);
    };

    vector<int> ql, qr, qk;
    ql.reserve(4 * Q);
    qr.reserve(4 * Q);
    qk.reserve(4 * Q);
    vector<int> s(Q);
    vector<bool> dead(Q);
    vector<int> res(Q);

    auto Calc = [&](int A, int B, int C, int D) {
        return A - B + C - D + min(min(abs(A - C), abs(A - D)), min(abs(B - C), abs(B - D)));
    };

    vector<int> LL(Q), RR(Q);
    vector<pair<int, int>> YY1(Q), YY2(Q), YY3(Q);

    for (int i = 0; i < Q; ++i) {
        int L, R;
        L = Read();
        R = Read();
        L--;
        LL[i] = L;
        RR[i] = R;
        int X1 = pref[0][R] - pref[0][L];
        int X2 = pref[1][R] - pref[1][L];
        int X3 = pref[2][R] - pref[2][L];
        // cout << "X1 = " << X1 << " X2 = " << X2 << " X3 = " << X3 << endl;
        pair<int, int> Y1 = Query(sp[0], L, R);
        pair<int, int> Y2 = Query(sp[1], L, R);
        pair<int, int> Y3 = Query(sp[2], L, R);
        YY1[i] = Y1;
        YY2[i] = Y2;
        YY3[i] = Y3;
        int T = (R - L) / 2;
        // cout << "T = " << T << endl;
        
        dead[i] = true;
        if (X1 > T || X2 > T) {
            res[i] = -1;
            continue;
        }

        if (X3 == 0) {
            res[i] = Calc(Y1.first, Y1.second, Y2.first, Y2.second);
            continue;
        }
        
        if (X1 == T) {
            auto Z = Merge(Y2, Y3);
            res[i] = Calc(Y1.first, Y1.second, Z.first, Z.second);
            continue;
        }
        if (X2 == T) {
            auto Z = Merge(Y1, Y3);
            res[i] = Calc(Z.first, Z.second, Y2.first, Y2.second);
            continue;
        }
        if (X1 == 0 && X2 == 0) {
            res[i] = Y3.first - Y3.second;
            continue;
        }
        dead[i] = false;
        s[i] = ql.size();
        if (X1 == 0 || X2 == 0) {
            ql.push_back(L);
            qr.push_back(R);
            qk.push_back(T);

            ql.push_back(L);
            qr.push_back(R);
            qk.push_back(T + 1);

            ql.push_back(L);
            qr.push_back(R);
            qk.push_back(X3 - T + 1);

            ql.push_back(L);
            qr.push_back(R);
            qk.push_back(X3 - T);
        } else {
            int K = T - X1;
            s[i] = ql.size();
            ql.push_back(L);
            qr.push_back(R);
            qk.push_back(K);

            ql.push_back(L);
            qr.push_back(R);
            qk.push_back(K + 1);

            ql.push_back(L);
            qr.push_back(R);
            qk.push_back(X3 - K + 1);

            ql.push_back(L);
            qr.push_back(R);
            qk.push_back(X3 - K);
        }
    }
    
    // cerr << "Here" << endl;

    cerr << static_cast<double>(clock()) / CLOCKS_PER_SEC << "\n";
    auto J = Solve(ql, qr, qk, type, h);
    cerr << static_cast<double>(clock()) / CLOCKS_PER_SEC << "\n";
    // cout << "done" << endl;
    for (int i = 0; i < Q; ++i) {
        if (dead[i]) continue;
        assert(s[i] + 3 < J.size());
        int A = J[s[i]];
        int B = J[s[i] + 1];
        int C = J[s[i] + 2];
        int D = J[s[i] + 3];
        int L = LL[i];
        int R = RR[i];
        int X1 = pref[0][R] - pref[0][L];
        int X2 = pref[1][R] - pref[1][L];
        int X3 = pref[2][R] - pref[2][L];

        // // swap(A, C);
        // // swap(B, D);
        auto Y1 = YY1[i];
        auto Y2 = YY2[i];
        auto Y3 = YY3[i];
        // pair<int, int> Y1 = Query(sp[0], L, R);
        // pair<int, int> Y2 = Query(sp[1], L, R);
        // pair<int, int> Y3 = Query(sp[2], L, R);
        // cerr << "i = " << i << " A = " << A << " B = " << B << " C = " << C << " D = " << D << endl;
        // cerr << "X1 = " << X1 << " X2 = " << X2 << " X3 = " << X3 << endl;
        if (X1 == 0) {
            int G = Calc(A, Y3.second, max(Y2.first, Y3.first), min(Y2.second, B));
            int H = Calc(Y3.first, C, max(Y2.first, D), min(Y2.second, Y3.second));
            res[i] = min(G, H);
        } else if (X2 == 0) {
            int G = Calc(A, Y3.second, max(Y1.first, Y3.first), min(Y1.second, B));
            int H = Calc(Y3.first, C, max(Y1.first, D), min(Y1.second, Y3.second));
            res[i] = min(G, H);
        } else {
            int G = Calc(max(Y1.first, A), min(Y1.second, Y3.second), max(Y2.first, Y3.first), min(Y2.second, B ));
            int H = Calc(max(Y1.first, Y3.first), min(Y1.second, C), max(Y2.first, D), min(Y2.second, Y3.second));
            res[i] = min(G, H);
        }
    }
    for (int i = 0; i < Q; ++i) {
        cout << res[i] << "\n";
    }
}

int main() {
    int T;
    T = Read();
    while (T--) {
        Solve();
    }
}
