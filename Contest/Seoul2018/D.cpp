#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        char c = s.back(); s.pop_back();
        if (c == 'a') s += "as";
        else if (c == 'i' || c == 'y') s += "ios";
        else if (c == 'l') s += "les";
        else if (c == 'n' || c == 'e' && s.back() == 'n') {
            if (c == 'e') s.pop_back();
            s += "anes";
        }
        else if (c == 'o') s += "os";
        else if (c == 'r') s += "res";
        else if (c == 't') s += "tas";
        else if (c == 'u') s += "us";
        else if (c == 'v') s += "ves";
        else if (c == 'w') s += "was";
        else s.push_back(c), s += "us";
        cout << s << endl;
    }
}
