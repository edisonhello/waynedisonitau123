#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<pair<int, int>> v(n);
    vector<int> dif;
    int unk = 0;
    for (auto &[i, j] : v) {
        cin >> i >> j;
        if (!j) ++unk;
        else dif.push_back(i - j + 1);
    }

    sort(dif.begin(), dif.end(), greater<int>());
    long long d = 0;
    if (unk >= 2) {
        for (auto [i, j] : v) {
            if (j) d += i;
        }
        cout << dif[0] << ' ' << d << endl;
    } else if (unk == 1) {
        for (auto [i, j] : v) {
            d += i;
        }
        cout << dif[0] + 1 << ' ' << d << endl;
    } else {
        for (auto [i, j] : v) {
            d += i;
        }
        long long t = dif[0];
        if (dif.size() > 1u) t = min(t, (long long)dif[1] + 1);
        cout << t << ' ' << d << endl;
    }
}

