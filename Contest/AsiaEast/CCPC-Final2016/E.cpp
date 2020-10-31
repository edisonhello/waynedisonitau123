#include <bits/stdc++.h>
using namespace std;

void Solve() {
    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(N), C(M);
    vector<pair<int, int>> event;
    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
        event.emplace_back(A[i], i);
        event.emplace_back(B[i] + 1, ~i);
    }
    for (int i = 0; i < M; ++i) {
        cin >> C[i];
        event.emplace_back(C[i], 1000000);
    }
    sort(event.begin(), event.end());
    int cover = 0, ans = N;
    vector<bool> removed(N);
    set<pair<int, int>> S;
    for (int i = 0; i < event.size(); ++i) {
        if (event[i].second == 1000000) {
            if (S.empty()) {
                cout << "IMPOSSIBLE!\n";
                return;
            }
            ans = min(ans, static_cast<int>(S.size())); 
            removed[S.begin()->second] = true;
            S.erase(S.begin());
        } else if (event[i].second >= 0) {
            S.insert(make_pair(B[event[i].second], event[i].second));
        } else {
            if (!removed[~event[i].second]) {
                S.erase(make_pair(B[~event[i].second], ~event[i].second));
            }
        }
    }
    cout << N - ans + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ": ";
        Solve();
    }
}

