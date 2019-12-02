#include <bits/stdc++.h>
using namespace std;

int tk[105][105];

int main() {
    int n, k; cin >> n >> k;
    for (int i = 1; i <= k; ++i) for (int j = 1; j <= n; ++j) {
        cin >> tk[i][j];
    }
    vector<int> ans;
    for (int i = 0; i <= 200; ++i) ans.push_back(i);
    for (int i = 1; i <= n - 1; ++i) {
        vector<int> tmp;
        vector<pair<int, int>> diff;
        for (int j = 1; j <= k; ++j) {
            diff.emplace_back(tk[j][n] - tk[j][i], j);
        }
        sort(diff.begin(), diff.end());
        // reverse(diff.begin(), diff.end());
        int sum = 0;
        for (auto &p : diff) sum += p.first;
        while (sum > 0) {
            sum -= diff.back().first;
            tmp.push_back(diff.back().second);
            diff.pop_back();

            // cout << "i = " << i << "  sum = " << sum << endl;
        }
        if (tmp.size() < ans.size()) ans.swap(tmp);
    }
    cout << ans.size() << endl;
    for (int i : ans) cout << i << ' '; 
    cout << endl;
}
