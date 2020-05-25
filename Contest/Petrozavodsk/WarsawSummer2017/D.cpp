#include <bits/stdc++.h>
using namespace std;


int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        string ans = "1";
        vector<int> v;
        while (n) {
            v.push_back(n & 1);
            n >>= 1;
        }
        v.pop_back();
        reverse(v.begin(), v.end());
        for (int i : v) {
            if (ans != "1") ans = "(" + ans + ")";
            if (i) {
                ans = ans + "*(1+1)+1";
            } else {
                ans = ans + "*(1+1)";
            }
        }

        cout << ans << endl;
    };
}

