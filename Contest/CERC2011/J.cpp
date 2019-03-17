#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    string s, t; 
    while (cin >> s) {
        if (s == "0") break;
        cin >> t;
        for (int i = 0; i < (int)t.size(); ++i) {
            int shift = s[i % (int)s.size()] - 'A' + 1;
            while (shift--) {
                if ((++t[i]) > 'Z')
                    t[i] = 'A';
            }
        }
        cout << t << "\n";
    }
}
