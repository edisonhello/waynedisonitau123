#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    vector<int> pv(26, -1);
    int n = s.size();
    vector<vector<int>> nxt(n);
    for (int i = n - 1; i >= 0; --i) {
        pv[s[i] - 'a'] = i;
        nxt[i] = pv;
    }
    int res = 0;
    vector<int> vis(26, -1);
    for (int ptr = 0; ptr < n; res++) {
        if (vis[s[ptr] - 'a'] == -1) {
            vis[s[ptr] - 'a'] = ptr;
            ptr++;
        } else {
            int p = -1, optr = ptr;
            while (ptr < n) {
                int g = p == -1 ? vis[s[ptr] - 'a'] : nxt[p][s[ptr] - 'a'];
                if (g == -1) break;
                if (g >= optr) break;
                ptr++;
                p = g + 1;
                if (p >= n) break;
            }
        }
    }
    cout << res << "\n";
    return 0;
}

