#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N), C(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> C[i];
    }
    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) { return A[i] < A[j]; });

    set<int> used;
    vector<pair<int, int>> V;
    for (int i = 0, j = 0; i < N; i = j) {
        while (j < N && C[order[i]] == C[order[j]]) j++;
        if (used.count(C[order[i]])) {
            cout << "0\n";
            return 0;
        }
        used.insert(C[order[i]]);
        V.emplace_back(A[order[i]] - 1, A[order[j - 1]] - 1);
    }

    struct Range { int L, R, V; };
    constexpr int kInf = 2'100'000'000;

    auto Get = [&](int X) {
        vector<int> R = {1};
        while (true) {
            int T = R.back();
            if (X < T + 1) break;
            int G = X / (X / (T + 1));
            R.push_back(G);
        }
        reverse(R.begin(), R.end());
        vector<Range> res = {(Range){1, 1, X}};
        for (int i = 1; i < R.size(); ++i) {
            res.push_back((Range){res.back().R + 1, X / R[i], R[i]});
        }
        res.push_back((Range){X + 1, kInf, 0});
        return res;
    };

    int K = V.size();
    vector<vector<Range>> LV(K), RV(K);
    for (int i = 0; i < K; ++i) {
        LV[i] = Get(V[i].first);
        RV[i] = Get(V[i].second);
    }

    set<pair<int, int>> cand;

    auto Intersect = [&](Range A, Range B) {
        if (A.L > B.R || B.L > A.R) return make_pair(-1, -1);
        int L = max(A.L, B.L);
        int R = min(A.R, B.R);
        return make_pair(L, R);
    };

    vector<pair<int, int>> event;

    for (int i = 0; i < K; ++i) {
        for (int j = 0, k = 0; j < LV[i].size(); ++j) {
            while (k < RV[i].size() && RV[i][k].V > LV[i][j].V) k++;
            if (k < RV[i].size() && RV[i][k].V == LV[i][j].V) {
                auto I = Intersect(RV[i][k], LV[i][j]);
                if (I.first == -1) continue;
                event.emplace_back(I.first, 1);
                event.emplace_back(I.second + 1, -1);
            }
        }
        if (i + 1 < K) {
            vector<pair<int, int>> S;
            for (int j = 0, k = 0; j < RV[i].size(); ++j) {
                while (k < LV[i + 1].size() && LV[i + 1][k].V > RV[i][j].V) {
                    S.emplace_back(LV[i + 1][k].L, LV[i + 1][k].R);
                    k++;
                }
                if (!S.empty()) {
                    int L = RV[i][j].L;
                    int R = RV[i][j].R;
                    auto it = upper_bound(S.begin(), S.end(), make_pair(L, kInf));
                    if (it != S.begin()) {
                        auto pit = prev(it);
                        if (pit->second >= L) {
                            it = pit;
                        }
                    }
                    while (it != S.end()) {
                        int TL = it->first;
                        int TR = it->second;
                        if (TL > R || L > TR) break;
                        event.emplace_back(max(L, TL), 1);
                        event.emplace_back(min(R, TR) + 1, -1);
                        it = next(it);
                    }
                }
            }
        }
    }
    sort(event.begin(), event.end());
    vector<pair<int, int>> OK;
    int sum = 0, prv = -1, mp = 0;
    for (int i = 0, j = 0; i < event.size(); i = j) {
        if (sum == K + K - 1) OK.emplace_back(prv, event[i].first - 1);
        mp = max(mp, sum);
        while (j < event.size() && event[j].first == event[i].first) {
            sum += event[j].second;
            j++;
        }
        prv = event[i].first;
    }
    if (!OK.empty() && OK.back().second == kInf) {
        cout << "-1\n";
        return 0;
    }
    int res = 0;
    for (auto u : OK) {
        res += u.second - u.first + 1;
        // for (int x = u.first; x <= u.second; ++x) {
        //     for (int i = 0; i < K; ++i) {
        //         assert(V[i].first / x == V[i].second / x);
        //         if (i + 1 < K) {
        //             assert(V[i].second / x < V[i + 1].first / x);
        //         }
        //     }
        // }
    }
    cout << res << "\n";
    // {
    //     vector<pair<int, int>> NOK;
    //     for (int i = 0, j = 0; i < OK.size(); i = j) {
    //         int expect = OK[i].first;
    //         while (j < OK.size() && OK[j].first == expect) {
    //             expect = OK[j].second + 1;
    //             j++;
    //         }
    //         NOK.emplace_back(OK[i].first, OK[j - 1].second);
    //     }
    //     OK = NOK;
    // }
    return 0;
}

