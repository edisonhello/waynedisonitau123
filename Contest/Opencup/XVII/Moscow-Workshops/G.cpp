#include <bits/stdc++.h>
using namespace std;


int main() {
    string s;
    cin >> s;
    int n = s.size();
    int l = 0, r = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'L') ++l;
        else break;
    }
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == 'R') ++r;
        else break;
    }
    if (l + r == n) cout << n << endl;
    else cout << l + r + 1 << endl;
}
