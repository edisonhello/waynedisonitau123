#include <bits/stdc++.h>
using namespace std;

int a[100005], b[100005], c[100005];

int main() {
    int n; cin >> n;
    string s; cin >> s; s = " " + s;
    for (int i = 1; i <= n; ++i) {
        a[i] += a[i - 1];
        b[i] += b[i - 1];
        c[i] += c[i - 1];
        if (s[i] == 'A') ++a[i];
        if (s[i] == 'B') ++b[i];
        if (s[i] == 'C') ++c[i];
    }

    int mn = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        string per = "ABC";
        do {
            int now = i;
            int val = 0;
            auto add = [&] (int l, int r, char sh) {
                if (sh == 'A') val += r - l + 1 - (a[r] - a[l - 1]);
                if (sh == 'B') val += r - l + 1 - (b[r] - b[l - 1]);
                if (sh == 'C') val += r - l + 1 - (c[r] - c[l - 1]);
            };
            for (int i = 0; i < 3; ++i) {
                int nnow = now;
                if (per[i] == 'A') nnow += a[n] - 1;
                if (per[i] == 'B') nnow += b[n] - 1;
                if (per[i] == 'C') nnow += c[n] - 1;
                
                if (nnow > n) {
                    add(now, n, per[i]);
                    nnow -= n;
                    add(1, nnow, per[i]);
                    now = nnow + 1;
                } else {
                    add(now, nnow, per[i]);
                    now = nnow == n ? 1 : nnow + 1;
                }
            }
            mn = min(mn, val);
        } while (next_permutation(per.begin(), per.end()));
    }

    cout << mn << endl;


}

