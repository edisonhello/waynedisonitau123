#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (i == j || j == k || i == k) continue;
                if (abs(a[i] - a[j]) % a[k] != 0) {
                    cout << "no" << endl;
                    return 0;
                }
            }
        }
    }
    cout << "yes" << endl;
}
