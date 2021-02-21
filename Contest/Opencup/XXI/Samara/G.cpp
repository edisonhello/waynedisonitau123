#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int k;
    cin >> k;
    int n = s.size();
    vector<vector<int>> nxt(n, vector<int>(26, n));
    vector<int> pos(26, n);
    for (int i = n - 1; i >= 0; --i) {
        pos[s[i] - 'a'] = i;
        copy(pos.begin(), pos.end(), nxt[i].begin());
    }
    string ans = "";
    for (int i = 0; i < n && ans.size() < k; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (n - nxt[i][j] + ans.size() >= k) {
                ans += static_cast<char>(j + 'a');
                i = nxt[i][j];
                break;
            }
        }
    }
    cout << ans << "\n";
}

