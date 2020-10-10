#include <bits/stdc++.h>
using namespace std;

int main() {
    int x, y; cin >> x >> y;
    vector<pair<int, int>> v;
    while (x > 0) {
        v.emplace_back(x, y);
        x--;
    }
    while (y > 0) {
        v.emplace_back(x, y);
        y--;
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if ((i & 1) == 0) {
                v.emplace_back(i, j);
            } else {
                v.emplace_back(i, 9 - j);
            }
        }
    }
    for (auto p : v) cout << p.first << " " << p.second << "\n";
}
