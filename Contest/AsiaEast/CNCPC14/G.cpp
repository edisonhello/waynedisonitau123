#include <bits/stdc++.h>
using namespace std;



int main() {
    int t; cin >> t; while (t--) {
        int n, k; cin >> n >> k;
        int cnt[4] = {0, 0, 0, 0};
        int ans = 0;
        deque<pair<int, int>> dq;
        while (n--) {
            char c; int x; cin >> c >> x;
            int z = -1;
            if (c == 'A') z = 0;
            if (c == 'B') z = 1;
            if (c == 'G') z = 2;
            if (c == 'P') z = 3;
            dq.emplace_back(z, x);
            cnt[z] += x;
            if (dq.size() > k) {
                auto [z, x] = dq.front();
                dq.pop_front();
                cnt[z] -= x;
            }

            for (int i = 0; i < 4; ++i) ans += cnt[i] == 5;
        }

        cout << ans << '\n';
    }
}

