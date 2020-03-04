#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int a = 0;
    while (n--) {
        string s; cin >> s;
        if (s[0] == 'L') a ^= 1;
    }
    if (a) cout << "LIE" << endl;
    else cout << "TRUTH" << endl;
}
