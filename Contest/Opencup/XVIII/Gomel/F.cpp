#include <bits/stdc++.h>
using namespace std;


int main() {
    int p; cin >> p;
    int n = 100;
    vector<vector<int>> pp;
    for (int i = 1; i <= 99; ++i) {
        pp.push_back(vector<int>{i, i + 1});
        for (int j = i + 2; j <= 100; ++j) {
            pp.push_back(vector<int>{i, j});
            pp.push_back(vector<int>{i, j});
        }
    }
    for (int i = 2, c = 3; i <= 100; ++i, c += 2) {
        if (i == 100) --c;
        for (int _ = 0; _ < c; ++_) {
            pp.push_back(vector<int>{i});
        }
    }

    cout << pp.size() << ' ' << 100 << endl;
    for (auto &v : pp) {
        cout << v.size();
        for (int i : v) cout << ' ' << i;
        cout << '\n';
    }
}

