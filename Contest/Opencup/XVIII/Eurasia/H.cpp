#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> pp;

int Query(int x, int y) {
    cout << "? " << x << " " << y << endl;
    fflush(stdout);
    int z; cin >> z;
    for (auto &p : pp) {
        if (p.first <= x && p.second <= y) --z;
    }
    assert(z >= 0);
    return z;
}

const int L = 1000000;

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x = L, y = L;
        for (int i = 23; i >= 0; --i) {
            if (y - (1 << i) < -L) continue;
            if (Query(x, y - (1 << i))) y -= 1 << i;
        }
        for (int i = 23; i >= 0; --i) {
            if (x - (1 << i) < -L) continue;
            if (Query(x - (1 << i), y)) x -= 1 << i;
        }
        pp.emplace_back(x, y);
    }

    cout << "!";
    for (auto &p : pp) cout << ' ' << p.first << ' ' << p.second;
    cout << endl;
}

