#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b; cin >> a >> b;
    vector<int> v = {1};
    int n = 0;
    for (; n <= 1000; ++n) {
        if (v[0] == b && v.back() == a) {
            cout << n << endl;
            exit(0);
        }
        for (int i = 0; i < (int)v.size(); ++i) v[i] *= 2;
        for (int i = 0; i < (int)v.size() - 1; ++i) v[i + 1] += v[i] / 10, v[i] %= 10;
        if (v.back() > 9) v.back() %= 10, v.push_back(1);
    }
    cout << -1 << endl;
}
