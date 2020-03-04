#include <bits/stdc++.h>
using namespace std;
#define stof jifsoeifjeofij

long long stof[200005];
set<pair<long long, int>> st[200005]; // [out time, id]
long long want[200005];
vector<tuple<int, long long, long long>> look[200005]; // [look id, in time, exp out time]

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int pid = 0, last = 0;
    int n, m; cin >> n >> m; while (m--) {
        int c; cin >> c; 
        if (c == 1) {
            ++pid;
            int y, k; cin >> y >> k;
            y ^= last;
            want[pid] = y;
            vector<long long> exth(k);
            for (int i = 0; i < k; ++i) {
                exth[i] = y / (k - i);
                y -= exth[i];
            }

            vector<tuple<int, long long, long long>> lk(k); 
            for (int i = 0; i < k; ++i) 
                cin >> get<0>(lk[i]), 
                get<0>(lk[i]) ^= last,
                get<1>(lk[i]) = stof[get<0>(lk[i])], 
                get<2>(lk[i]) = get<1>(lk[i]) + exth[i], 
                st[get<0>(lk[i])].insert(make_pair(get<2>(lk[i]), pid));
            look[pid] = lk;
        } else {
            int x, y; cin >> x >> y;
            x ^= last;
            y ^= last;
            stof[x] += y;
            vector<pair<long long, int>> pl;
            while (st[x].size() && st[x].begin()->first <= stof[x]) {
                pl.push_back(*st[x].begin());
                st[x].erase(st[x].begin());
            }

            vector<int> done;
            for (auto &p : pl) {
                int pid = p.second, idx = 0;
                for (; get<0>(look[pid][idx]) != x; ++idx);
                long long got = 0;
                for (int z = 0; z < (int)look[pid].size(); ++z) {
                    got += stof[get<0>(look[pid][z])] - get<1>(look[pid][z]);
                    if (z != idx) 
                        st[get<0>(look[pid][z])].erase(make_pair(get<2>(look[pid][z]), pid));
                }
                want[pid] -= got;
                if (want[pid] <= 0) {
                    done.push_back(pid);
                } else {
                    int y = want[pid], k = look[pid].size();
                    vector<long long> exth(k);
                    for (int i = 0; i < k; ++i) {
                        exth[i] = y / (k - i);
                        y -= exth[i];
                    }

                    vector<tuple<int, long long, long long>> lk(k); 
                    for (int i = 0; i < k; ++i) 
                        get<0>(lk[i]) = get<0>(look[pid][i]),
                        get<1>(lk[i]) = stof[get<0>(lk[i])], 
                        get<2>(lk[i]) = get<1>(lk[i]) + exth[i], 
                        st[get<0>(lk[i])].insert(make_pair(get<2>(lk[i]), pid));
                    look[pid] = lk;
                }
            }

            sort(done.begin(), done.end());
            cout << done.size();
            for (int i : done) cout << ' ' << i;
            cout << '\n';

            last = done.size();
        }
    }
}
