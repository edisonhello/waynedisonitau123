#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int sp = 0;
    int out = 0;
    string s; while (cin >> s) {
        if (s == "bubble" || s == "tapioka") continue;
        if (sp) cout << ' ';
        sp = 1;
        cout << s;
        ++out;
    }
    if (out == 0) cout << "nothing";
    cout << endl;
}
