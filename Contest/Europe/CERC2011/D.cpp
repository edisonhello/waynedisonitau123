#include <bits/stdc++.h>
using namespace std;

string mp[1005],tb[1005],tmp[1005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; while (cin >> n, n) {
        for (int i = 0; i < n; ++i) cin >> mp[i];
        for (int i = 0; i < n; ++i) cin >> tb[i];

        for (int _ = 0; _ < 4; ++_) {
            for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (mp[i][j] == 'O') cout << tb[i][j];
            for (int z = 0; z < 3; ++z) {
                for (int i = 0; i < n; ++i) tmp[i] = "";
                for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) tmp[n - j - 1] += mp[i][j];
                for (int i = 0; i < n; ++i) mp[i] = tmp[i];
            }
        }
        cout << '\n';
    }
}
