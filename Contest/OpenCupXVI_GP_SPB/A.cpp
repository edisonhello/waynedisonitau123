#include <bits/stdc++.h>
using namespace std;

int pos[1094][2];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> pos[i][0] >> pos[i][1];
    if (n == 1) {
        cout << 1 << endl;
        exit(0);
    }
    vector<double> xs;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (pos[i][0] == pos[j][0]) continue;
            double x = (double)(pos[i][0] * pos[i][0] + pos[i][1] * pos[i][1] - pos[j][0] * pos[j][0] - pos[j][1] * pos[j][1]) / (2 * pos[i][0] - 2 * pos[j][0]);
            xs.push_back(x);
        }
    }
    sort(xs.begin(), xs.end());
    if (xs.empty()) {
        cout << 1 << endl;
        exit(0);
    }
    vector<double> uxs; uxs.push_back(xs[0]);
    for (int i = 1; i < (int)xs.size(); ++i) {
        if (abs(xs[i] - uxs.back()) < 1e-9) continue;
        uxs.push_back(xs[i]);
    }
    // cerr << "uxs: "; for (double x : uxs) cerr << x << " "; cerr << endl;
    cout << uxs.size() + 1 << endl;
}
