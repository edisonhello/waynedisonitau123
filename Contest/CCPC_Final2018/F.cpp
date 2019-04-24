#pragma GCC optimize("Ofast")
#pragma GCC target("avx,sse,sse2,sse3,sse4,sse4.2,tune=native")

#include <bits/stdc++.h>
using namespace std;

double pos[1005][2];
map<pair<int, int>, vector<int>> mp;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; for (int T = 1; T <= t; ++T) {
        cout << "Case " << T << ": ";
        mp.clear();
        int n; cin >> n;
        double block_size;
        if (n >= 100) block_size = 0.5;
        else if (n >= 10) block_size = 0.25;
        else block_size = 0.1;
        for (int i = 0; i < n; ++i) {
            cin >> pos[i][0] >> pos[i][1];
            pos[i][0] += 20;
            pos[i][1] += 20;
            for (double x = pos[i][0] - 1; x <= pos[i][0] + 1; x += block_size) {
                for (double y = pos[i][1] - 1; y <= pos[i][1] + 1; y += block_size) {
                    mp[make_pair(x / block_size, y / block_size)].push_back(i);
                }
            }
        }
        const int cut = 16;
        double vol = 0;
        double d_area = block_size * block_size / (cut * cut);
        for (auto &p : mp) {
            int xid = p.first.first;
            int yid = p.first.second;
            for (int i = 0; i < cut; ++i) {
                double x = xid * block_size + (i + 0.5) * block_size / cut;
                for (int j = 0; j < cut; ++j) {
                    double y = yid * block_size + (j + 0.5) * block_size / cut;
                    double z = 0;
                    for (int id : p.second) z = max(z, 1 - hypot(x - pos[id][0], y - pos[id][1]));
                    // cerr << "z = " << z << " at " << x << " " << y << endl;
                    // if (p.second.size()) cerr << hypot(x - pos[p.second[0]][0], y - pos[p.second[0]][1]) << " " << x << " " << y << " " << pos[p.second[0]][0] << " " << pos[p.second[0]][1] << endl;
                    vol += d_area * z;
                }
            }
        }
        cout << fixed << setprecision(10) << vol << '\n';
    }
}
