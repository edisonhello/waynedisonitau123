#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a, b;
    for (int i = 0; i < 6; ++i) {
        int t; cin >> t;
        a.push_back(t);
    }
    for (int i = 0; i < 6; ++i) {
        int t; cin >> t;
        b.push_back(t);
    }
    int win = 0;
    for (int i = 0; i < 6; ++i) for (int j = 0; j < 6; ++j) {
        if (a[i] > b[j]) ++win;
    }

    int g = __gcd(win, 36);
    cout << win / g << "/" << 36 / g << endl;
}

