#include <bits/stdc++.h>
using namespace std;

int m[3005][3005], rcnt[3005][27], ccnt[3005][27];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < n; ++j) {
            char c = s[j];
            if (c == '?') continue;
            m[i][j] = c - 'a' + 1;
            ++rcnt[i][m[i][j]];
            if (rcnt[i][m[i][j]] == 1) ++rcnt[i][0];
            ++ccnt[j][m[i][j]];
            if (ccnt[j][m[i][j]] == 1) ++ccnt[j][0];
        }
    }
    stack<tuple<char, int, int>> ans;
    queue<pair<char, int>> ok;
    for (int i = 0; i < n; ++i) if (rcnt[i][0] <= 1) {
        ok.emplace('r', i);
        if (rcnt[i][0] == 1) { for (int z = 1; z <= 26; ++z) if (rcnt[i][z]) ans.emplace('r', i, z); }
        else ans.emplace('r', i, 1);
    }
    for (int i = 0; i < n; ++i) if (ccnt[i][0] <= 1) {
        ok.emplace('c', i);
        if (ccnt[i][0] == 1) { for (int z = 1; z <= 26; ++z) if (ccnt[i][z]) ans.emplace('c', i, z); }
        else ans.emplace('c', i, 1);
    }
    while (ok.size()) {
        char dir; int i; tie(dir, i) = ok.front(); ok.pop();
        if (dir == 'r') {
            for (int j = 0; j < n; ++j) {
                if (m[i][j] == 0) continue;
                int o = m[i][j];
                m[i][j] = 0;
                --ccnt[j][o];
                if (ccnt[j][o] == 0) {
                    --ccnt[j][0];
                    if (ccnt[j][0] == 1) {
                        // cout << "new push ok = col " << j << endl;
                        ok.emplace('c', j);
                        for (int z = 1; z <= 26; ++z) if (ccnt[j][z]) ans.emplace('c', j, z);
                    }
                }
            }
        } else {
            for (int j = 0; j < n; ++j) {
                if (m[j][i] == 0) continue;
                int o = m[j][i];
                m[j][i] = 0;
                --rcnt[j][o];
                if (rcnt[j][o] == 0) {
                    --rcnt[j][0];
                    if (rcnt[j][0] == 1) {
                        // cout << "new push ok = row " << i << endl;
                        ok.emplace('r', j);
                        for (int z = 1; z <= 26; ++z) if (rcnt[j][z]) ans.emplace('r', j, z);
                    }
                }
            }
        }
    }
    while (ans.size()) {
        char dir; int i, z; tie(dir, i, z) = ans.top(); ans.pop();
        printf("%c %d %c\n", dir == 'r' ? 'h' : 'v', i + 1, z - 1 + 'a');
    }
}
