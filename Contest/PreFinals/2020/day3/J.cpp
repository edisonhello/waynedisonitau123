#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int64_t> cnt(n + 1);
    int64_t sum = 0;
    for (int i = 0; i <= n; ++i) {
        cin >> cnt[i];
        sum += (1LL << i) * (1LL << i) * cnt[i];
    }

    auto Check = [&](int64_t x, int64_t y) {
        vector<int64_t> ncnt(cnt.begin(), cnt.end());
        for (int i = 0; i <= n; ++i) {
            if (x % 2 == 1 && y % 2 == 1) {
                if (ncnt[i] < x + y - 1) return false;
                ncnt[i] -= x + y - 1;
            } else if (x % 2 == 1) {
                if (ncnt[i] < y) return false;
                ncnt[i] -= y;
            } else if (y % 2 == 1) {
                if (ncnt[i] < x) return false;
                ncnt[i] -= x;
            }
            if (i == n) {
                break;
            } else {
                if (ncnt[i] % 4 != 0) return false;
                ncnt[i + 1] += ncnt[i] / 4;
                x >>= 1;
                y >>= 1;
            }
        }
        return true;
    };

    for (int64_t p = 1; p * p <= sum; ++p) {
        if (sum % p == 0) {
            if (Check(p, sum / p)) {
                cout << p << " " << sum / p << "\n";
                return 0;
            }
        }
    }
    cout << "impossible\n";
    return 0;
}

