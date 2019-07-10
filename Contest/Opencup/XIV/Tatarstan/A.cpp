#include <bits/stdc++.h>
using namespace std;


int main() {
    int n; cin >> n; n = n * 2 + 1;
    vector<int> fac;
    for (int i = 2; i <= n; ++i) {
        while (n % i == 0) fac.push_back(i), n /= i;
    }
    reverse(fac.begin(), fac.end());
    vector<vector<int>> ans;
    do {
        int now = 0;
        vector<int> aans;
        for (int i : fac) {
            int cnt = i / 2;
            for (int j = 0; j < cnt; ++j) aans.push_back(now * 2 + 1);
            now += (now * 2 + 1) * cnt;
        }
        ans.push_back(aans);
    } while (prev_permutation(fac.begin(), fac.end()));
    cout << ans.size() << " " << ans[0].size() << endl;
    for (auto &v : ans) {
        for (int i : v) cout << i << " ";
        cout << endl;
    }
}
