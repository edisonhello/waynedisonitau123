#include <bits/stdc++.h>
using namespace std;

uint32_t cyc(uint32_t v, int x) {
    return (v << x) | (v >> (32 - x));
}

uint32_t parse(string s) {
    uint32_t v = 0;
    for (char c : s) {
        v *= 16;
        if (c >= '0' && c <= '9') v += c - '0';
        else v += c - 'A' + 10;
    }
    return v;
}


int main() {
    int t; cin >> t;
    for (int T = 1; T <= t; ++T) {
        string s, t; cin >> s >> t;
        uint32_t ss = parse(s), tt = parse(t);
        cout << "Case #" << T << ": ";
        vector<vector<int>> pos(32);
        for (int i = 0; i < 32; ++i) {
            if (cyc(ss, i) == tt) pos[i].push_back(-1);
            if (cyc(ss, 32 - i) == tt) pos[i].push_back(1);
        }

        bool out = 0;
        for (int i = 0; i < 32; ++i) {
            if (pos[i].size()) {
                out = 1;
                if (pos[i].size() == 2u) {
                    cout << i << " Any" << '\n';
                } else if (pos[i][0] == -1) {
                    cout << i << " Left" << '\n';
                } else {
                    cout << i << " Right" << '\n';
                }
                break;
            }
        }

        if (!out) {
            cout << "Not possible" << '\n';
        }
    }
}
