#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int cnt[3005];
int _C[3005][3005];

int C(int x, int y) { return _C[x][y]; }

int main() {

    _C[0][0] = 1;
    for (int i = 1; i <= 3000; ++i) {
        for (int j = 0; j <= i; ++j) {
            _C[i][j] = _C[i - 1][j];
            if (j) (_C[i][j] += _C[i - 1][j - 1]) >= mod ? _C[i][j] -= mod : 0;
        }
    }

    string s;
    int c;
    cin >> s >> c;

    int n = s.size();
    int prec = 0;
    for (int i = 0; i < n; ++i) {
        int r = n - i - 1;

        if (s[i] == '0') {
            continue;
        } else {
            for (int j = 0; j <= r; ++j) {
                cnt[j + prec] += C(r, j);
                if (cnt[j + prec] >= mod) cnt[j + prec] -= mod;
            }
            ++prec;
        }
    }

    ++cnt[prec];

    int sum = 0;
    int cc = 1;
    for (int i = 0; i <= 3000; ++i) {
        sum += cc * 1ll * cnt[i] % mod;
        if (sum >= mod) sum -= mod;
        cc = 1ll * cc * c % mod;
    }

    cout << sum << endl;

    
}

