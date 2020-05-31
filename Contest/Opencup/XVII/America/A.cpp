#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<tuple<int, int, int>> v;
    int p = 0;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int sum = 0, bal = 0;
        for (int j = 0; j < s.size(); ++j) {
            sum += (s[j] == '(' ? 1 : -1);
            bal = min(bal, sum);
        }
        p += s.size();
        v.emplace_back(sum, bal, s.size());
    }
    sort(v.begin(), v.end(), [&](auto x, auto y) {
        // return get<0>(x) - get<1>(x) > get<0>(y) - get<1>(y);
        return min(get<1>(x), get<0>(x) + get<1>(y)) >
               min(get<1>(y), get<0>(y) + get<1>(x));
    });

    vector<int> dp(p + 1, -p);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        vector<int> nxt(p + 1, -p);
        for (int j = 0; j <= p; ++j) {
            if (dp[j] < 0) continue;
            nxt[j] = max(nxt[j], dp[j]);
            if (j + get<1>(v[i]) >= 0 && j + get<0>(v[i]) <= p && j + get<0>(v[i]) >= 0) {
                nxt[j + get<0>(v[i])] = max(nxt[j + get<0>(v[i])], dp[j] + get<2>(v[i]));
            }
        }
        dp = nxt;
    }
    cout << dp[0] << "\n";
}

