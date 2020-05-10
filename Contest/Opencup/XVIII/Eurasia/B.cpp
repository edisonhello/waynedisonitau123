#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<string> s(n);
        for (int i = 0; i < n; ++i) {
            cin >> s[i];
        }
        int z = -1;
        for (int i = 0; i < n; ++i) {
            if (z == -1 || s[i].size() > s[z].size()) z = i;
        }
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < s[i].size(); ++j) ok &= s[i][j] == s[z][j];
        }
        if (!ok) cout << "Impossible\n";
        else cout << s[z].size() << "\n";
    }
}

