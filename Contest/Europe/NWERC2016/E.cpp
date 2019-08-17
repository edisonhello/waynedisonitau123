#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    int sum = accumulate(s.begin(), s.end(), 0);
    int z = max_element(s.begin(), s.end()) - s.begin();
    if (s[z] * 2 > sum) {
        cout << "impossible" << endl;
        return 0;
    }
    for (int i = z; i < n; ++i) cout << i + 1 << ' ';
    for (int i = 0; i < z; ++i) cout << i + 1 << ' ';
    cout << endl;
}
