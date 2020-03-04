#include <bits/stdc++.h>
using namespace std;


int main() {
    int t; cin >> t; for (int i = 1; i <= t; ++i) {
        int n, m; cin >> n >> m;
        string s, t, r; cin >> s >> t >> r;
        for (char &c : s) c -= 'A';
        for (char &c : t) c -= 'A';
        for (char &c : r) c -= 'A';
        int diff = s[0] - t[0];
        for (char &c : r) c += diff;
        for (char &c : r) c = (c + 26) % 26 + 'A';
        cout << "Case #" << i << ": " << r << endl;
    }
}
