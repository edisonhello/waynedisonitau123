#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    string s;
    getline(cin, s);
    while (t--) {
        getline(cin, s);
        stringstream ss; ss << s;
        string k; ss >> k;
        int ans = 1e9;
        int v = 0;
        while (ss >> v) ans = min(ans, v);
        cout << k << ' ' << ans << endl;
    }
}
