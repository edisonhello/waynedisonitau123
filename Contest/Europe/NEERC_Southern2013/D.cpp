#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        vector<int> gd, bd;
        vector<int> ans(n + 4, 0);
        for (int i = 1; i <= n; ++i) {
            cout << "1\n" << i << endl;
            int x; cin >> x;
            if (x) gd.push_back(i), ans[i] = 1;
            else bd.push_back(i), ans[i] = 2;
        }
        for (int i = 1; i <= n; ++i) {
            if (ans[i] == 1) {
                cout << bd.size() + 1 << "\n";
                for (int i : bd) cout << i << " ";
                cout << i << endl;
                int x; cin >> x;
                if (x == 0) ans[i] = 3;
            } else {
                cout << gd.size() + 1 << "\n";
                for (int i : gd) cout << i << " ";
                cout << i << endl;
                int x; cin >> x;
                if (x == gd.size() + 1) ans[i] = 3;
            }
        }
        cout << "-1\n";
        for (int i = 1; i <= n; ++i) cout << ans[i] << " "; cout << endl;
    }
}
