#include <bits/stdc++.h>
using namespace std;

int cnt[25];
long long fac[25];

int main() {
    // vector<int> rm = {0, 0, 0, 0, 2, 3, 3, 4};
    // set<int> all;
    // do {
    //     bool no = false;
    //     for (int i = 2; i < 10; ++i) if (rm[i - 2] >= i) no = true;
    //     if (rm.back() == 0) no = true;
    //     if (!no) {
    //         int num = 0;
    //         for (int i = 2; i < 10; ++i) {
    //             num = num * i + rm[i - 2];
    //         }
    //         all.insert(num);
    //         cout << num << endl;
    //     }
    // } while (next_permutation(rm.begin(), rm.end()));

    // cout << all.size() << endl;

    fac[0] = 1;
    for (int i = 1; i <= 20; ++i) fac[i] = fac[i - 1] * i;

    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        long long k; cin >> k;
        vector<int> rm;
        for (int i = 2; k; ++i) {
            rm.push_back(k % i);
            k /= i;
        }
        sort(rm.begin(), rm.end());
        set<int> lasts(rm.begin(), rm.end());
        lasts.erase(0);
        long long ans = 0;
        for (int last : lasts) {
            int ladiv = rm.size();
            long long tmp = 1;
            int pos = 0;
            bool bylas = false;
            memset(cnt, 0, sizeof(cnt));
            for (int i = (int)rm.size() - 1; i >= 0; --i) {
                if (!bylas && last == rm[i]) {
                    bylas = true;
                    continue;
                }
                while (ladiv >= 2 && ladiv > rm[i]) ++pos, --ladiv;
                ++cnt[rm[i]];
                tmp *= pos;
                --pos;
            }
            for (int i = 0; i <= 20; ++i) tmp /= fac[cnt[i]];
            ans += tmp;
        }
        cout << ans - 1 << '\n';
    }
}
