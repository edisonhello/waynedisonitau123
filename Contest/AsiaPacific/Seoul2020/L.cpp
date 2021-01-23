#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    vector<int> Left = {0};
    for (int i = 1; i < N; ++i) {
        if (A[i] > A[Left.back()]) Left.push_back(i);
    }
    vector<int> Right = {N - 1};
    for (int i = N - 2; i >= 0; --i) {
        if (A[i] > A[Right.back()]) Right.push_back(i);
    }

    auto Eval = [&](int x, int y) -> int64_t {
        return 1LL * (A[x] + A[y]) * (y - x);
    };

    reverse(Right.begin(), Right.end());

    int j = -1;
    int64_t res = 0;
    for (int i = 0; i < Left.size(); ++i) {
        int64_t v = Eval(Left[i], Right[0]);
        if (v >= res) {
            res = v;
            j = i;
        }
    }
    deque<tuple<int, int, int>> Que;
    Que.emplace_back(j, 0, Right.size() - 1);
    // cerr << "j = " << j << endl;
    j++;
    for (int i = 0; i < Right.size(); ++i) {
        while (!Que.empty() && get<2>(Que[0]) < i) Que.pop_front();
        if (!Que.empty()) {
            // cerr << "Right = " << Right[i] << " Left = " << Left[get<0>(Que[0])] << endl;
            res = max(res, Eval(Left[get<0>(Que[0])], Right[i]));
        }
        if (i + 1 == Right.size()) continue;
        while (!Que.empty() && get<2>(Que[0]) < i + 1) Que.pop_front();
        if (!Que.empty()) get<1>(Que[0]) = i + 1;
        while (j < Left.size() && Left[j] < Right[i + 1]) {
            // cerr << "Try " << Left[j] << endl;
            tuple<int, int, int> s = make_tuple(j, i + 1, Right.size() - 1);
            while (!Que.empty() && Eval(Left[get<0>(s)], Right[get<1>(Que.back())]) >= Eval(Left[get<0>(Que.back())], Right[get<1>(Que.back())])) Que.pop_back();
            if (!Que.empty()) {
                int to = get<1>(Que.back());
                // cerr << "to = " << to << endl;
                for (int bit = 20; bit >= 0; --bit) {
                    if (to + (1 << bit) <= get<2>(Que.back()) && Eval(Left[get<0>(s)], Right[to + (1 << bit)]) < Eval(Left[get<0>(Que.back())], Right[to + (1 << bit)])) to += (1 << bit);
                }
                get<2>(Que.back()) = to;
                get<1>(s) = to + 1;
            }
            // cerr << "Push s = " << get<0>(s) << " " << get<1>(s) << " " << get<2>(s) << endl;
            if (get<1>(s) < Right.size()) Que.push_back(s);
            j++;
        }
    }

    // int j = 0;
    // for (int u : Left) {
    //     while (j < Right.size() && Right[j] <= u) j++;
    //     while (j + 1 < Right.size() && Eval(u, Right[j]) <= Eval(u, Right[j + 1])) j++;
    //     res = max(res, Eval(u, Right[j]));
    // }
    cout << res << "\n";
}

