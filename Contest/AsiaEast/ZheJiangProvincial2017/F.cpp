#include <bits/stdc++.h>
using namespace std;

void Solve() {
    int N;
    cin >> N;
    vector<int> X(N + 1), Y(N + 1);
    for (int i = 0; i <= N; ++i) cin >> X[i];
    for (int i = 0; i <= N; ++i) cin >> Y[i];

    for (int i = 0; i < N; ++i) {
        if (X[i] > 0 && Y[i] < 0) {
            for (int j = 0; j < N; ++j) {
                if (j == i) cout << 9998;
                else cout << 0;
                cout << " ";
            }
            cout << "\n";
            return;
        }
        if (X[i] < 0 && Y[i] > 0) {
            for (int j = 0; j < N; ++j) {
                if (j == i) cout << 9998;
                else cout << 0;
                cout << " ";
            }
            cout << "\n";
            return;
        }
    }

    bool ZX = all_of(X.begin(), X.begin() + N, [&](int x) { return x == 0; });
    bool ZY = all_of(Y.begin(), Y.begin() + N, [&](int x) { return x == 0; });

    if (ZX && X[N] == 0) {
        cout << "No\n";
        return;
    }
    if (ZY && Y[N] == 0) {
        cout << "No\n";
        return;
    }
    
    if (ZX && ZY) {
        if (X[N] * Y[N] < 0) {
            for (int i = 0; i < N; ++i) cout << 0 << " ";
            cout << "\n";
            return;
        }
        cout << "No\n";
        return;
    }

    if (ZX) {
        swap(ZX, ZY);
        swap(X, Y);
    }
    assert(!ZX);

    if (ZY) {
        assert(Y[N] != 0);
        int p = -1;
        for (int i = 0; i < N; ++i) {
            if (X[i] != 0) p = i;
        }
        assert(p != -1);
        if ((Y[N] > 0) ^ (X[p] > 0)) {
            for (int i = 0; i < N; ++i) {
                if (i == p) cout << 9998;
                else cout << 0;
                cout << " ";
            }
        } else {
            for (int i = 0; i < N; ++i) {
                if (i == p) cout << -9998;
                else cout << 0;
                cout << " ";
            }
        }
        cout << "\n";
        return;
    }

    int p = -1;
    for (int i = 0; i < N; ++i) {
        if (X[i] == 0 && Y[i] != 0 || Y[i] == 0 && X[i] != 0) p = i;
    }
    if (p != -1) {
        if (X[p] != 0) swap(X, Y);
        assert(X[p] == 0 && Y[p] != 0);
        int Xs = X[N], Ys = Y[N];
        if (Xs > 0) {
            for (int i = 0; i < N; ++i) {
                if (i == p) cout << (Y[i] > 0 ? -9998 : 9998);
                else cout << 0;
                cout << " ";
            }
        } else if (Xs < 0) {
            for (int i = 0; i < N; ++i) {
                if (i == p) cout << (Y[i] < 0 ? -9998 : 9998);
                else cout << 0;
                cout << " ";
            }
        } else {
            bool f = false;
            for (int i = 0; i < N; ++i) {
                if (i == p) {
                    cout << (Y[i] > 0 ? 9998 : -9998);
                } else if (X[i] != 0 && !f) {
                    f = true;
                    if (X[i] > 0) cout << "-0.000001";
                    else cout << "0.000001";
                } else {
                    cout << 0;
                }
                cout << " ";
            }
            assert(f);
        }
        cout << "\n";
        return;
    }

    for (int i = 0; i < N; ++i) {
        if (X[i] == 0) assert(Y[i] == 0);
        if (Y[i] == 0) assert(X[i] == 0);
    }

    if (X[N] == 0 && Y[N] == 0) {
        int p = -1, q = -1;
        for (int i = 0; i < N; ++i) {
            if (X[i] == 0) continue;
            for (int j = i + 1; j < N; ++j) {
                if (X[j] == 0) continue;
                if (X[i] * Y[j] != X[j] * Y[i]) {
                    p = i;
                    q = j;
                    break;
                }
            }
        }
        if (p == -1) {
            cout << "No\n";
            return;
        }
        for (int i = 0; i < N; ++i) {
            if (i == p) cout << X[q] + Y[q];
            else if (i == q) cout << -X[p] - Y[p];
            else cout << 0;
            cout << " ";
        }
        cout << "\n";
        return;
    }

    if (X[N] == 0) swap(X, Y);
    assert(X[N] != 0);

    if (Y[N] == 0) {
        int p = -1;
        for (int i = 0; i < N; ++i) {
            if (Y[i] != 0) p = i;
        }
        assert(p != -1);
        if (X[N] > 0) {
            for (int i = 0; i < N; ++i) {
                if (i == p) {
                    if (Y[i] > 0) cout << "-0.000001";
                    else cout << "0.000001";
                } else {
                    cout << 0;
                }
                cout << " ";
            }
        } else {
            for (int i = 0; i < N; ++i) {
                if (i == p) {
                    if (Y[i] < 0) cout << "-0.000001";
                    else cout << "0.000001";
                } else {
                    cout << 0;
                }
                cout << " ";
            }
        }
        cout << "\n";
        return;
    }

    p = -1;
    for (int i = 0; i < N; ++i) {
        if (X[i] == 0) continue;
        if (X[i] * Y[N] != Y[i] * X[N]) {
            p = i;
        }
    }
    if (p == -1) {
        cout << "No\n";
        return;
    }
    if (X[p] + Y[p] == 0) {
        for (int i = 0; i < N; ++i) {
            if (i == p) {
                double v = static_cast<double>(-2 * X[N] - Y[N]) / (2 * X[i] + Y[i]);
                cout << fixed << setprecision(8) << v;
            } else {
                cout << 0;
            }
            cout << " ";
        }
    } else {
        for (int i = 0; i < N; ++i) {
            if (i == p) {
                double v = static_cast<double>(-X[N] - Y[N]) / (X[i] + Y[i]);
                cout << fixed << setprecision(8) << v;
            } else {
                cout << 0;
            }
            cout << " ";
        }
    }
    cout << "\n";
}

int main() {
    int T;
    cin >> T;
    while (T--) Solve();
}

