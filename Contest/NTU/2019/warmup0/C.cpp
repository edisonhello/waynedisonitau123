#include <bits/stdc++.h>
using namespace std;

int a, b, m, x1, cnt[100009], appear[100009];

int f(int i) {
    if (i == 1) return x1;
    else return (1ll * a * f(i - 1) + b) % m + 2;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        long long n;
        cin >> n >> m >> a >> b >> x1;
        if (n <= m) {
            long long x = x1;
            for (int i = 1; i <= n; ++i) {
                ++cnt[x];
                x = (1ll * a * x + b) % m + 2;
            }

            int v = 0;
            for (int i = 0; i <= m + 3; ++i) if (cnt[i] % 2) v ^= (i - 2);
            // for (int i = 0; i <= m + 3; ++i) cerr << cnt[i] << ' '; cerr << endl;
            if (v) cout << "First" << '\n';
            else cout << "Second" << '\n';

            for (int i = 0; i <= m + 3; ++i) cnt[i] = 0;
        } else {
            long long x = x1;
            vector<int> loop;
            long long starti = -1;
            long long endi = -1;
            for (int i = 1; ; ++i) {
                if (appear[x]) {
                    starti = appear[x];
                    endi = i - 1;
                    break;
                }
                appear[x] = i;
                x = (1ll * a * x + b) % m + 2;
            }
            for (int i = starti; i <= endi; ++i) loop.push_back(x), x = (1ll * a * x + b) % m + 2;

            long long trashsize = starti - 1;
            x = x1;
            for (int i = 1; i <= trashsize; ++i) ++cnt[x], x = (1ll * a * x + b) % m + 2;

            long long cntloop = (n - trashsize) / loop.size();
            for (int i = 1, j = 0; i <= (int)loop.size(); ++i, ++j) cnt[loop[j]] += cntloop & 1;

            long long left = (n - cntloop * loop.size() - trashsize);
            for (int i = 1, j = 0; i <= left; ++i, ++j) ++cnt[loop[j]];

            int v = 0;
            for (int i = 0; i <= m + 3; ++i) if (cnt[i] % 2) v ^= (i - 2);
            // for (int i = 0; i <= m + 3; ++i) cerr << cnt[i] << ' '; cerr << endl;
            if (v) cout << "First" << '\n';
            else cout << "Second" << '\n';

            for (int i = 0; i <= m + 3; ++i) cnt[i] = 0, appear[i] = 0;
        }
    }
}
