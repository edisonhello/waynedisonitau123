#include <bits/stdc++.h>
using namespace std;
 
int main() {
    long long x; cin >> x; --x;
    vector<int> v;
    for (int i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            v.push_back(i);
            v.push_back(x / i);
        }
    }
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    for (int i : v) cout << i << " ";
    cout << endl;
}
