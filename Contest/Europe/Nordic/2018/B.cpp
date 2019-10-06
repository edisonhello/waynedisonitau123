#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        if (s[0] == 'm') continue;
        stringstream ss(s);
        int x; ss >> x;
        if (x != i) {
            cout << "something is fishy" << endl;
            return 0;
        }
    }
    cout << "makes sense" << endl;
}
