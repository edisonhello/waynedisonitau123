#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, c, y;
    cin >> n >> c >> y;
    vector<int> x(n);
    c--;
    int64_t sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        sum += x[i];
    }
    vector<int> z;
    for (int i = 0; i < n; ++i) {
        if (i != c) {
            z.push_back(x[i]);
        }
    }
    sort(z.begin(), z.end());
    for (int i = 1; i < z.size(); ++i) {
        if ((z[i] - z[i - 1]) % (y + 1) != 0) {
            cout << "impossible\n";
            return 0;
        }
    }
    cout << z.back() << " " << sum + 1LL * z.back() * (y - n + 1) << "\n";
}

