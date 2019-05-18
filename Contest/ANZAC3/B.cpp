#include <bits/stdc++.h>
using namespace std;

long long fac[20];

int main() {
    int n; long long k; cin >> n >> k; --k;
    vector<int> ans;
    vector<int> can;
    fac[0] = 1;
    for (int i = 1; i <= 19; ++i) fac[i] = fac[i - 1] * i;
    for (int i = 1; i < n; ++i) can.push_back(i);
    int idx = 0;
    for (int i = 1; i < n; ++i) {
        int j = n - 1 - i;
        int ii;
        if (j > 19) ii = 0;
        else ii = k / fac[j];
        assert(ii < 20);
        idx += ii;
        idx %= can.size();
        ans.push_back(can[idx]);
        can.erase(can.begin() + idx);
        k -= fac[j] * ii;

        /* if (j > 19) {
            ans.push_back(can[0]);
            can.erase(can.begin());
        } else {
            int ii = k / fac[j];
            cerr << "ii = " << ii << endl;
            ans.push_back(can[ii]);
            can.erase(can.begin() + ii);
            k -= fac[j] * ii;
        } */
    }
    for (int i = (int)ans.size() - 1; i > 0; --i) {
        ans[i] -= ans[i - 1];
    }
    for (int &i : ans) {
        i = (i % n + n) % n;
    }
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << " \n"[i == ans.size() - 1];
    }
}
