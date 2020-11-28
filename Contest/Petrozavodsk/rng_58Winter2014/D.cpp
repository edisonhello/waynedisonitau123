#include <bits/stdc++.h>
using namespace std;

int main() {
    int H, W, N;
    cin >> H >> W >> N;
    vector<int> A(N), B(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
    }
    vector<int> Order(W);
    iota(Order.begin(), Order.end(), 0);
    for (int i = 0; i < W; i += 2) {
        swap(Order[i], Order[i + 1]);
    }
    for (int i = 1; i + 1 < W; i += 2) {
        swap(Order[i], Order[i + 1]);
    }
    vector<int> To(W);
    for (int i = 0; i < W; ++i) To[Order[i]] = i;
    vector<vector<int>> Cycle;
    vector<bool> Vis(W);
    for (int i = 0; i < W; ++i) {
        if (Vis[i]) continue;
        int x = i;
        vector<int> C;
        while (!Vis[x]) {
            Vis[x] = true;
            C.push_back(x);
            x = To[x];
        }
        Cycle.push_back(move(C));
    }
    vector<int> Pos(W);
    for (auto &C : Cycle) {
        for (int i = 0; i < C.size(); ++i) {
            Pos[C[i]] = C[(i + H / 2) % C.size()];
        }
    }
    for (int i = 0; i < W; ++i) Order[Pos[i]] = i;
    if (H & 1) {
        for (int i = 0; i < W; i += 2) swap(Order[i], Order[i + 1]);
    }
    // cout << "Here" << endl;
    vector<int> Ans = Order;
    // cout << "Debug: ";
    // for (int i = 0; i < W; ++i) cout << Order[i] << " ";
    // cout << endl;
    vector<int> EvenS = Order, OddS, Even, Odd;
    vector<int> P(W);
    iota(P.begin(), P.end(), 0);
    for (int i = 0; i < W; i += 2) swap(P[i], P[i + 1]);
    for (int i = 1; i + 1 < W; i += 2) swap(P[i], P[i + 1]);
    Even = P;
    iota(P.begin(), P.end(), 0);
    for (int i = 1; i + 1 < W; i += 2) swap(P[i], P[i + 1]);
    for (int i = 0; i < W; i += 2) swap(P[i], P[i + 1]);
    Odd = P;

    if (H & 1) {
        for (int i = 0; i < W; i += 2) swap(Order[i], Order[i + 1]);
        OddS = Order;
        // Even = P;
        // iota(P.begin(), P.end(), 0);
        // for (int i = 1; i + 1 < W; i += 2) swap(P[i], P[i + 1]);
        // for (int i = 0; i < W; i += 2) swap(P[i], P[i + 1]);
        // Odd = P;
    } else {
        for (int i = 1; i + 1 < W; i += 2) swap(Order[i], Order[i + 1]);
        OddS = Order;
        swap(Even, Odd);
    }


    vector<vector<int>> Event(H);
    for (int i = 0; i < N; ++i) {
        Event[A[i] - 1].push_back(B[i] - 1);
    }

    auto GetCycle = [&](vector<int> P) {
        vector<vector<int>> Cycle;
        vector<int> To = P;
        // for (int i = 0; i < W; ++i) To[P[i]] = i;
        vector<bool> Vis(W);
        for (int i = 0; i < W; ++i) {
            if (Vis[i]) continue;
            int x = i;
            vector<int> C;
            while (!Vis[x]) {
                Vis[x] = true;
                C.push_back(x);
                x = To[x];
            }
            Cycle.push_back(move(C));
        }
        return Cycle;
    };

    auto GetPos = [&](vector<int> P) {
        vector<int> To(W);
        for (int i = 0; i < W; ++i) To[P[i]] = i;
        return To;
    };

    auto CEven = GetCycle(Even);
    auto COdd = GetCycle(Odd);

    vector<int> WEven(W), QEven(W), WOdd(W), QOdd(W);
    for (int i = 0; i < CEven.size(); ++i) {
        for (int j = 0; j < CEven[i].size(); ++j) {
            WEven[CEven[i][j]] = i;
            QEven[CEven[i][j]] = j;
        }
    }
    for (int i = 0; i < COdd.size(); ++i) {
        for (int j = 0; j < COdd[i].size(); ++j) {
            WOdd[COdd[i][j]] = i;
            QOdd[COdd[i][j]] = j;
        }
    }

    auto PEven = GetPos(EvenS);
    auto POdd = GetPos(OddS);


    vector<int> Fin(W);
    for (int i = 0; i < W; ++i) Fin[Ans[i]] = i;

    // cout << "Fin: ";
    // for (int i = 0; i < W; ++i) cout << Fin[i] << " ";
    // cout << endl;

    // cout << "WEven: ";
    // for (int i = 0; i < W; ++i) cout << WEven[i] << " ";
    // cout << endl;
    // cout << "WOdd: ";
    // for (int i = 0; i < W; ++i) cout << WOdd[i] << " ";
    // cout << endl;
    // 
    // cout << "OddS: ";
    // for (int i = 0; i < W; ++i) cout << OddS[i] << " ";
    // cout << endl;
    // cout << "EvenS: ";
    // for (int i = 0; i < W; ++i) cout << EvenS[i] << " ";
    // cout << endl;

    // cout << "POdd: ";
    // for (int i = 0; i < W; ++i) cout << POdd[i] << " ";
    // cout << endl;
    // cout << "PEven: ";
    // for (int i = 0; i < W; ++i) cout << PEven[i] << " ";
    // cout << endl;

    // cout << "COdd: ";
    // for (auto &C : COdd) {
    //     for (int u : C) cout << u << " ";
    //     cout << endl;
    // }
    // cout << endl;

    // cout << "CEven: ";
    // for (auto &C : CEven) {
    //     for (int u : C) cout << u << " ";
    //     cout << endl;
    // }
    // cout << endl;

    // cout << "Even: ";
    // for (int u : Even) cout << u << " "; cout << endl;
    // cout << "Odd: ";
    // for (int u : Odd) cout << u << " "; cout << endl;

    auto Get = [&](const auto &S, const auto &C, const auto &W, const auto &Q, int X, int L) {
        // cout << "X = " << X << endl;
        int Pos = W[X];
        int Idx = Q[X];
        // cout << "Pos = " << Pos << " Idx = " << Idx << "\n";
        assert(!C[Pos].empty());
        return C[Pos][(Idx + L) % C[Pos].size()];
    };

    for (int i = H - 1; i >= 0; --i) {
        for (int u : Event[i]) {
            int L, R;
            // cout << "u = " << u << endl;
            if (((H - 1) - i) & 1) {
                L = OddS[Get(POdd, COdd, WOdd, QOdd, u, (H - 2 - i) / 2)];
                R = OddS[Get(POdd, COdd, WOdd, QOdd, u + 1, (H - 2 - i) / 2)];
            } else {
                L = EvenS[Get(PEven, CEven, WEven, QEven, u, (H - 1 - i) / 2)];
                R = EvenS[Get(PEven, CEven, WEven, QEven, u + 1, (H - 1 - i) / 2)];
            }
            // cout << "L = " << L << " R = " << R << endl;
            swap(Fin[L], Fin[R]);
        }
        // cout << "Level = " << i + 1 << endl;
        // for (int j = 0; j < W; ++j) cout << Fin[j] + 1 << " ";
        // cout << endl;
    }
    for (int i = 0; i < W; ++i) cout << Fin[i] + 1 << "\n";
    return 0;
}

