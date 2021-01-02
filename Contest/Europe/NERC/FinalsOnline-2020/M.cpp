#include <bits/stdc++.h>
using namespace std;


int main() {
    map<int, int> mp;
    int ans = 0;
    int t; cin >> t; while (t--) {
        int z; cin >> z;
        int mx = 0;
        vector<int> yy;
        while (z--) {
            int y; cin >> y;
            yy.push_back(y);
            auto it = mp.find(y);
            if (it != mp.end()) mx = max(mx, it->second);
        }
        for (int y : yy) {
            mp[y] = mx + 1;
        }
        ans = max(ans, mx + 1);
    }
    cout << ans << endl;

}

