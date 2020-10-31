#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
    vector<vector<vector<vector<int>>>> X;

    SparseTable() = default;
    SparseTable(const vector<vector<int>> &A) {
        // cout << "OK" << endl;
        int N = A.size(), M = A[0].size();
        X.assign(10, vector<vector<vector<int>>>(10));
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                X[i][j].assign(N, vector<int>(M));
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                X[0][0][i][j] = A[i][j];
            }
        }
        for (int i = 0; (1 << i) <= N; ++i) {
            for (int j = 0; (1 << j) <= M; ++j) {
                if (i == 0 && j == 0) continue;
                if (i > 0) {
                    for (int k = 0; k + (1 << i) <= N; ++k) {
                        for (int l = 0; l < M; ++l) {
                            X[i][j][k][l] = max(X[i - 1][j][k][l], X[i - 1][j][k + (1 << (i - 1))][l]);
                        }
                    }
                } else {
                    for (int k = 0; k < N; ++k) {
                        for (int l = 0; l + (1 << j) <= M; ++l) {
                            X[i][j][k][l] = max(X[i][j - 1][k][l], X[i][j - 1][k][l + (1 << (j - 1))]);
                        }
                    }
                }
            }
        }
        // cout << "SAFE" << endl;
    }

    int Query(int x1, int y1, int x2, int y2) {
        int p = 31 - __builtin_clz(x2 - x1);
        int q = 31 - __builtin_clz(y2 - y1);
        return max(max(X[p][q][x1][y1], X[p][q][x1][y2 - (1 << q)]),
                   max(X[p][q][x2 - (1 << p)][y1], X[p][q][x2 - (1 << p)][y2 - (1 << q)]));
    }
};

tuple<int64_t, int64_t, int64_t> ExtGCD(int64_t a, int64_t b) {
    if (!b) return make_tuple(a, 1, 0);
    int64_t d, x, y;
    tie(d, x, y) = ExtGCD(b, a % b);
    return make_tuple(d, y, x - (a / b) * y);
}

int64_t ChineseRemainderThm(vector<pair<int, int>> V) {
    int64_t M = V[0].first, res = V[0].second;
    for (int i = 1; i < V.size(); ++i) {
    }
    return res;
}

pair<int64_t, int64_t> Merge(int64_t Mod, int64_t res, int64_t A, int64_t B) {
    if (Mod == -1) return make_pair(Mod, res);
    if (Mod == 0) return make_pair(A, B);
    int64_t d, x, y;
    tie(d, x, y) = ExtGCD(Mod, A);
    if ((B - res) % d != 0) return make_pair(-1, -1);
    int64_t NewM = Mod / __gcd(Mod, A) * A;
    res += (__int128)x * ((B - res) / d) % NewM * Mod % NewM;
    Mod = NewM;
    ((res %= Mod) += Mod) %= Mod;
    return make_pair(Mod, res);
}

void Solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> A(N, vector<int>(M));
    vector<vector<int>> B(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) cin >> A[i][j];
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) cin >> B[i][j];
    }
    for (int b = 1; b <= 40; ++b) {
    }

    int Q;
    cin >> Q;
    vector<int> x1(Q), y1(Q), x2(Q), y2(Q);
    vector<int64_t> Mod(Q), res(Q);
    SparseTable Max, Min;
    for (int i = 0; i < Q; ++i) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        x1[i]--;
        y1[i]--;
    }
    for (int b = 1; b <= 40; ++b) {
        vector<vector<int>> X(N, vector<int>(M));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (B[i][j] != b) X[i][j] = -1;
                else X[i][j] = A[i][j];
            }
        }
        Max = SparseTable(X);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (B[i][j] != b) X[i][j] = -100;
                else X[i][j] = -A[i][j];
            }
        }
        Min = SparseTable(X);
        for (int i = 0; i < Q; ++i) {
            int X = Max.Query(x1[i], y1[i], x2[i], y2[i]);
            int Y = Min.Query(x1[i], y1[i], x2[i], y2[i]);
            if (X == -1) continue;
            if (X != -Y) Mod[i] = res[i] = -1;
            else tie(Mod[i], res[i]) = Merge(Mod[i], res[i], b, X);
        }
    }

    for (int i = 0; i < Q; ++i) {
        cout << res[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ":\n";
        Solve();
    }
}

