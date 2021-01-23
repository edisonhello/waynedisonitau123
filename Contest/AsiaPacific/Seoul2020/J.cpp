#include <bits/stdc++.h>
using namespace std;

using row = bitset<505>;

int main() {
    int n; cin >> n;
    vector<row> v(n), inv(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int t; cin >> t;
            if (t) v[i][j] = 1;
        }
        inv[i][i] = 1;
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (v[j][i] == 1) {
                swap(v[i], v[j]);
                swap(inv[i], inv[j]);
                break;
            }
        }

        if (v[i][i] == 0) {
            exit((cout << -1 << endl, 0));
        }

        for (int j = 0; j < n; ++j) if (j != i) {
            if (v[j][i]) {
                v[j] ^= v[i];
                inv[j] ^= inv[i];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        vector<int> z;
        for (int j = 0; j < n; ++j) if (inv[i][j]) {
            z.push_back(j + 1);
        }
        for (int j = 0; j < (int)z.size(); ++j) {
            cout << z[j] << " \n"[j == z.size() - 1];
        }
    }
}

