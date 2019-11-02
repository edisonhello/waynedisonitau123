#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int kN = 3e5 + 5;
const int kMod[2] = {1'000'000'000 + 123, 1'000'000'000 + 87};
const int kMult[2] = {87, 131};
const int kMagic = 800;
int h[2][kN], pw[2][kN], z[kN], cnt[kN];
char s[kN];

int main() {
    int q; scanf("%d", &q);
    int last = 0, n = 0;

    for (int j = 0; j < 2; ++j) {
        pw[j][0] = 1;
        for (int i = 1; i < kN; ++i)
            pw[j][i] = 1LL * pw[j][i - 1] * kMult[j] % kMod[j];
    }

    int zp = 0;

    auto Rebuild = [&]() {
        fill(z, z + n, 0);
        z[0] = n;
        int l = 0, r = 0;
        for (int i = 1; i < n; ++i) {
            z[i] = max(0, min(z[i - l], r - i + 1));
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                l = i; r = i + z[i];
                ++z[i];
            }
        }
        fill(cnt, cnt + n + 1, 0);
        for (int i = 0; i < n; ++i) cnt[z[i]]++;
        for (int i = n; i >= 0; --i) cnt[i] += cnt[i + 1];
        zp = n;
    };

    auto Append = [&](char c) {
        int prv[2] =  {0, 0};
        if (n > 0) {
            prv[0] = h[0][n - 1];
            prv[1] = h[1][n - 1];
        }
        h[0][n] = (1LL * prv[0] * kMult[0] + c) % kMod[0];
        h[1][n] = (1LL * prv[1] * kMult[1] + c) % kMod[1];
        s[n++] = c;
        if (n - zp > kMagic) Rebuild();
    };

    auto QueryHash = [&](int l, int r, int k) {
        for (int i = 0; i < 2; ++i) {
            int hv = 0;
            if (l == 0) hv = h[i][r];
            else hv = (h[i][r] + kMod[i] - 1LL * h[i][l - 1] * pw[i][r - l + 1] % kMod[i]) % kMod[i];
            if (hv != h[i][k - 1]) return false;
        }
        return true;
    };

    auto Query = [&](int k) {
        int res = cnt[k];
        for (int i = zp; i < n; ++i) {
            if (i - k + 1 >= 0 && QueryHash(i - k + 1, i, k)) ++res;
        }
        return res;
    };

    while (q--) {
        static char cmd[5], c[2];
        scanf("%s", cmd);
        if (cmd[0] == 'a') {
            scanf("%s", c);
            char z = (c[0] - 'a' + last) % 26 + 'a';
            // z = c[0];
            Append(z);
        } else {
            int k; scanf("%d", &k);
            k = k - 1 + last;
            while (k >= n) k -= n;
            k += 1;
            printf("%d\n", last = Query(k));
        }
    }
    return 0;
}
