#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> s(3);
    for (int i = 0; i < 3; ++i) cin >> s[i];
    vector<int> ord(3);
    iota(ord.begin(), ord.end(), 0);
    vector<map<vector<vector<int>>, int>> rot(3);
    int n = s[0].size();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            vector<vector<int>> p(3);
            for (int k = 0; k < n; ++k) {
                p[s[i][k] - 'A'].push_back((k + j) % n);
            }
            for (int k = 0; k < 3; ++k) {
                sort(p[k].begin(), p[k].end());
            }
            int g = min(j, n - j);
            if (rot[i].find(p) == rot[i].end()) {
                rot[i][p] = g;
            } else {
                rot[i][p] = min(rot[i][p], g);
            }
        }
    }
    int res = -1;
    do {
        for (int i = 0; i < n; ++i) {
            bool ok = true;
            vector<vector<int>> w(3);
            for (int j = 0; j < n; ++j) {
                if (s[ord[0]][j] == s[ord[1]][(j + i) % n]) {
                    ok = false;
                    break;
                }
                // cout << "a = " << s[ord[0]][j] << " b = " << s[ord[1]][(j + i) % n] << endl;
                char c = s[ord[0]][j] ^ s[ord[1]][(j + i) % n] ^ 'A' ^ 'B' ^ 'C';
                // cout << "c = " << c << endl;
                w[c - 'A'].push_back(j);
            }
            if (!ok) continue;
            auto it = rot[ord[2]].find(w);
            if (it != rot[ord[2]].end()) {
                int dist = min(i, n - i) + it->second;
                if (res == -1 || dist < res) res = dist;
            }
        }
    } while (next_permutation(ord.begin(), ord.end()));
    cout << res << "\n";
}


