#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("powersum.in", "r", stdin);
    freopen("powersum.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<string> adj(N);
    vector<int> In(N), Out(N);
    for (int i = 0; i < N; ++i) {
        cin >> adj[i];
        for (int j = 0; j < N; ++j) {
            if (adj[i][j] == '1') {
                In[j]++;
                Out[i]++;
            }
        }
    }
    vector<int> InOrder(N), OutOrder(N);
    iota(InOrder.begin(), InOrder.end(), 0);
    sort(InOrder.begin(), InOrder.end(), [&In](int i, int j) { return In[i] < In[j]; });
    iota(OutOrder.begin(), OutOrder.end(), 0);
    sort(OutOrder.begin(), OutOrder.end(), [&Out](int i, int j) { return Out[i] < Out[j]; });

    vector<int> S(N), T(N);
    for (int i = 0, j = 0, k = 0; i < N; i = j, k++) {
        while (j < N && In[InOrder[i]] == In[InOrder[j]]) {
            T[InOrder[j]] = k;
            j++;
        }
    }
    for (int i = 0, j = 0, k = 0; i < N; i = j, k++) {
        while (j < N && Out[OutOrder[i]] == Out[OutOrder[j]]) {
            S[OutOrder[j]] = k;
            j++;
        }
    }
    int Upper = 1'000'000'000;
    int Lower = -1'000'000'000;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (adj[i][j] == '1') Upper = min(Upper, S[i] + T[j]);
            else Lower = max(Lower, S[i] + T[j]);
        }
    }
    if (Upper <= Lower) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (int i = 0; i < N; ++i) cout << S[i] << " " << T[i] << "\n";
    cout << Upper << "\n";
}

