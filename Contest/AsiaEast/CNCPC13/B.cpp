#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;

        vector<int> l(m + 2, 0);
        for (int i = 1; i <= m; ++i) cin >> l[i];

        vector<vector<int>> as(m + 2);
        for (int i = 0; i < n; ++i) {
            int a, b; cin >> a >> b;
            as[b].push_back(a);
        }

        for (int i = 1; i <= m; ++i) {
            sort(as[i].begin(), as[i].end());
            reverse(as[i].begin(), as[i].end());
        }

        set<int> taking;
        vector<vector<int>> revl(n + 2);

        for (int i = 1; i <= m; ++i) revl[l[i]].push_back(i);

        long long u = 0, d = 1;

        long long sum = 0;
        for (int cl = 1; cl <= n; ++cl) {
            // cerr << "cl = " << cl << endl;
            for (int i : revl[cl]) {
                // cerr << "new i = " << i << endl;
                // cerr << "as[i].size() = " << as[i].size() << endl;
                if ((int)as[i].size() < cl) continue;
                // cerr << "new i = " << i << endl;
                taking.insert(i);

                for (int j = 0; j < cl - 1; ++j) {
                    sum += as[i][j];
                }
            }

            // cerr << "taking: ";
            // for (int i : taking) cerr << i << ' ' ;
            // cerr << endl;

            vector<int> removes;
            for (int i : taking) {
                if ((int)as[i].size() < cl) {
                    removes.push_back(i);
                } else {
                    sum += as[i][cl - 1];
                }
            }

            for (int i : removes) {
                taking.erase(i);
            }

            if ((__int128)sum * d > (__int128)cl * u) {
                u = sum;
                d = cl;
            }

            // cerr << "cl = " << cl << " sum = " << sum << endl;
        }

        long long g = __gcd(u, d);
        cout << u / g << "/" << d / g << '\n';


    }
}

