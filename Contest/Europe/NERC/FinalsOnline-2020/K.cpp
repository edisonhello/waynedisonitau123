#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int ch = INT_MAX, by = 0;
    for (int i = 1; i <= n; ++i) {
        int pri; cin >> pri;
        string s; cin >> s;
        int cn[3] = {0};
        for (char c : s) {
            if (c >= '0' && c <= '2') {
                cn[c - '0']++;
            }
        }

        if (cn[2] >= 2 && cn[0] >= 1 && cn[1] >= 1) {
            if (pri < ch) {
                ch = pri;
                by = i;
            }
        }
    }
    cout << by << endl;
}

