#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int cnt[2][4005][26];

// uint64_t hhv[26][4005];
int pp1[26], pp2[26];
const int mod1 = 1000000007, mod2 = 1000000009;

unordered_set<uint64_t> vec[4005];

/* pair<int, int> mhh(const array<int, 26> &v) {
   int x1 = 0, x2 = 0;
   int pp1 = 1, pp2 = 1;
   int mod1 = 1000000007, mod2 = 1000000009;
   for (int i = 0; i < 26; ++i) {
   x1 = (x1 + 1ll * v[i] * pp1) % mod1;
   x2 = (x2 + 1ll * v[i] * pp2) % mod2;
   pp1 = 1ll * pp1 * 131 % mod1;
   pp2 = 1ll * pp2 * 7902131 % mod2;
   }
   return make_pair(x1, x2);
   } */
uint64_t mhh(int x, int y) {
    return (((uint64_t)x) << 32) | (uint64_t)y;
}

int main() {
    // for (int z = 0; z < 26; ++z) for (int i = 0; i < 4005; ++i) hhv[z][i] = (((uint64_t)rand()) << 32) | (uint64_t)rand();
    pp1[0] = pp2[0] = 1;
    for (int i = 1; i < 26; ++i) pp1[i] = 131ll * pp1[i - 1] % mod1, pp2[i] = 7902131ll * pp2[i - 1] % mod2;

    ios_base::sync_with_stdio(0); cin.tie(0);
    string s[2]; cin >> s[0] >> s[1];
    for (int z = 0; z < 2; ++z) {
        for (int i = 0; i < (int)s[z].size(); ++i) {
            if (i) for (int j = 0; j < 26; ++j) cnt[z][i][j] = cnt[z][i - 1][j];
            ++cnt[z][i][s[z][i] - 'a'];
        }
    }
    // array<int, 26> tmp;
    // uint64_t now = 0;
    for (int i = 0; i < (int)s[0].size(); ++i) {
        // for (int z = 0; z < 26; ++z) tmp[z] = 0;
        // now = 0;
        int hh1 = 0, hh2 = 0;
        for (int j = i; j < (int)s[0].size(); ++j) {
            // for (int z = 0; z < 26; ++z) {
            // 	tmp[z] = cnt[0][j][z] - (i ? cnt[0][i - 1][z] : 0);
            // }
            // tmp[s[0][j] - 'a']++;
            // now ^= hhv[s[0][j] - 'a'][tmp[s[0][j] - 'a']];
            hh1 = (hh1 + pp1[s[0][j] - 'a']) % mod1;
            hh2 = (hh2 + pp2[s[0][j] - 'a']) % mod2;
            vec[j - i + 1].insert(mhh(hh1, hh2));
        }
    }

    int mx = 0;
    for (int i = 0; i < (int)s[1].size(); ++i) {
        // for (int z = 0; z < 26; ++z) tmp[z] = 0;
        // now = 0;
        int hh1 = 0, hh2 = 0;
        for (int j = i; j < (int)s[1].size(); ++j) {
            // for (int z = 0; z < 26; ++z) {
            // 	tmp[z] = cnt[1][j][z] - (i ? cnt[1][i - 1][z] : 0);
            // }
            // tmp[s[1][j] - 'a']++;
            // now ^= hhv[s[1][j] - 'a'][tmp[s[1][j] - 'a']];
            hh1 = (hh1 + pp1[s[1][j] - 'a']) % mod1;
            hh2 = (hh2 + pp2[s[1][j] - 'a']) % mod2;
            if (vec[j - i + 1].count(mhh(hh1, hh2))) mx = max(mx, j - i + 1);
        }
    }

    cout << mx << endl;
}
