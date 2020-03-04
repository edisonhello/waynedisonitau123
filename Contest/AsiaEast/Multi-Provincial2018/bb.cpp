#include <bits/stdc++.h>
using namespace std;


int main() {
    int n = 5;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) v[i] = i + 1;
    int cnt = 0;
    vector<int> ans = {1, 3, 2, 4, 5};
    do {
        vector<int> a = v;
        for (int k = 0; k < 2; ++k) {
            for (int i = 1; i < n; ++i) {
                if (a[i - 1] > a[i]) swap(a[i - 1], a[i]);
            }
        }
        if (a == ans) ++cnt;
    } while (next_permutation(v.begin(), v.end()));
    cout << cnt << endl;
}
