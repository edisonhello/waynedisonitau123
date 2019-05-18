#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int q; cin >> q; 
        vector<pair<int, int>> m(q);
        for (auto &i : m) cin >> i.first >> i.second;
        int mp[3][3]; memset(mp, -1, sizeof(mp));
        auto win = [&] () -> int {
            if (mp[0][0] == mp[0][1] && mp[0][0] == mp[0][2] && mp[0][0] > -1) return mp[0][0];
            if (mp[1][0] == mp[1][1] && mp[1][0] == mp[1][2] && mp[1][0] > -1) return mp[1][0];
            if (mp[2][0] == mp[2][1] && mp[2][0] == mp[2][2] && mp[2][0] > -1) return mp[2][0];
            if (mp[0][0] == mp[1][0] && mp[0][0] == mp[2][0] && mp[0][0] > -1) return mp[0][0];
            if (mp[0][1] == mp[1][1] && mp[0][1] == mp[2][1] && mp[0][1] > -1) return mp[0][1];
            if (mp[0][2] == mp[1][2] && mp[0][2] == mp[2][2] && mp[0][2] > -1) return mp[0][2];
            if (mp[0][0] == mp[1][1] && mp[0][0] == mp[2][2] && mp[0][0] > -1) return mp[1][1];
            if (mp[0][2] == mp[1][1] && mp[0][2] == mp[2][0] && mp[0][2] > -1) return mp[1][1];
            return -1;
        };
        auto print = [&] () -> void {
            for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) {
                cout << mp[i][j] << " \n"[j == 2];
            }
            cout << "win = " << win() << endl;
        };
        int who = 1;
        for (auto &i : m) {
            int x, y; tie(x, y) = i;
            if (mp[x][y] > -1) continue;
            mp[x][y] = who;
            who = 1 - who;
            // print();
            if (win() > -1) break;
        }
        cout << win() << '\n';
    }
}
