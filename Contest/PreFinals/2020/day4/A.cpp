#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> ord(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        ord[i] = i;
    }
    sort(ord.begin(), ord.end(), [&](int i, int j) { return a[i] < a[j]; });
    sort(a.begin(), a.end());
    n = unique(a.begin(), a.end()) - a.begin();
    constexpr int kA = 36000;
    pair<int, vector<pair<int, int>>> res(0, vector<pair<int, int>>());

    auto Solve = [&](vector<int> b) {
        vector<int> dp(n, 0);
        vector<int> fr(n, -1);
        vector<int> wh(n, -1);
        vector<int> ev(n);
        assert(is_sorted(b.begin(), b.end()));
        deque<int> dq;
        for (int i = 0, j = 0; i < n; ++i) {
            while (!dq.empty() && b[i] - b[dq[0]] > kA / 2) dq.pop_front();
            if (!dq.empty()) {
                fr[i] = dq[0];
                dp[i] = ev[dq[0]] + b[i];
            }
            ev[i] = (i > 0 ? dp[i - 1] : 0) - b[i];
            while (!dq.empty() && ev[i] >= ev[dq.back()]) dq.pop_back();
            dq.push_back(i);
            wh[i] = i;
            if (i > 0 && dp[i - 1] > dp[i]) {
                dp[i] = dp[i - 1];
                wh[i] = wh[i - 1];
            }
        }
        if (dp[n - 1] <= 0) return make_pair(0, vector<pair<int, int>>());
        vector<pair<int, int>> ch;
        // cout << "dp = " << dp[n - 1] << "\n";
        for (int g = wh[n - 1]; fr[g] >= 0; ) {
            // cout << "g = " << g << endl;
            ch.emplace_back(fr[g], g);
            if (fr[g] == 0) break;
            g = wh[fr[g] - 1];
        }
        return make_pair(dp[n - 1], ch);
    };

    for (int i = 0; i < n; ++i) {
        vector<int> b(n);
        for (int j = 0; j < n; ++j) {
            b[j] = (a[(i + j) % n] - a[i] + kA) % kA;
        }
        auto ret = Solve(b);
        for (auto &p : ret.second) {
            (p.first += i) %= n;
            (p.second += i) %= n;
        }
        // set<int> s;
        // int sum = 0;
        // for (auto &p : ret.second) {
        //     assert(!s.count(p.first));
        //     s.insert(p.first);
        //     assert(!s.count(p.second));
        //     s.insert(p.second);
        //     int dist = abs(a[p.first] - a[p.second]);
        //     dist = min(dist, kA - dist);
        //     sum += dist;
        // }
        // assert(sum == ret.first);
        res = max(res, ret);
    }
    cout << res.first << " " << res.second.size() << "\n";
    for (auto p : res.second) cout << ord[p.first] + 1 << " " << ord[p.second] + 1 << " ";
    cout << "\n";
}

