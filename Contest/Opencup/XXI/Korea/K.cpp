#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> x(N), y(N);
    for (int i = 0; i < N; ++i) {
        cin >> x[i] >> y[i];
    }
    int k = 0;
    for (int i = 1; i < N; ++i) {
        if (x[i] < x[k]) k = i;
        else if (x[i] == x[k] && y[i] < y[k]) k = i;
    }

    map<pair<int, int>, vector<int>> M;

    for (int i = 0; i < N; ++i) {
        if (i == k) continue;
        int dx = x[i] - x[k];
        int dy = y[i] - y[k];
        int g = __gcd(abs(dx), abs(dy));
        dx /= g;
        dy /= g;
        M[make_pair(dx, dy)].push_back(i);
    }

    vector<int> res = {k};
    for (auto &it : M) {
        auto &V = it.second;
        sort(V.begin(), V.end(), [&](int i, int j) {
            if (x[i] == x[j]) return y[i] < y[j];
            return x[i] < x[j];
        });
        res.insert(res.end(), V.begin(), V.end());
        for (int i = (int)V.size() - 2; i >= 0; --i) res.push_back(V[i]);
        res.push_back(k);
    }
    cout << res.size() << "\n";
    for (int u : res) cout << u + 1 << " ";
    cout << "\n";
}

