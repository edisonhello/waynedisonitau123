#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n; cin >> n;
    vector<int> v;
    while (n) {
        v.push_back(n & 1);
        n >>= 1;
    }
    v.push_back(0); v.push_back(0);
    for (int i = 1; i < (int)v.size(); ++i) {
        if (v[i] >= 2) {
            v[i + 1] += v[i] / 2;
            v[i] %= 2;
        }
        if (v[i - 1] == 1 && v[i] == 1) {
            ++v[i + 1];
            --v[i];
            v[i - 1] = -1;
        }
    }
    while (v.back() == 0) v.pop_back();
    reverse(v.begin(), v.end());
    for (int i : v) cout << i << " "; cout << endl;
}
