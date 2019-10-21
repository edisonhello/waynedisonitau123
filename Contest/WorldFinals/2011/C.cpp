#include <bits/stdc++.h>
using namespace std;
 
int ToHex(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    return c - 'a' + 10;
}
 
const int kN = 200 + 5;
int gr[kN][kN], uf[kN * kN], bd[kN * kN];
set<int> st[kN * kN];
 
int Find(int x) {
    if (x == uf[x]) return x;
    return uf[x] = Find(uf[x]);
}
 
void Merge(int x, int y) {
    uf[Find(x)] = Find(y);
}
 
int main() {
    int h, w, tc = 0; 
    string tpl = "WAKJSD";
    while (cin >> h >> w) {
        if (!h && !w) break;
        for (int i = 0; i < h; ++i) {
            string s;
            cin >> s;
            for (int j = 0; j < w; ++j) {
                int f = ToHex(s[j]);
                // gr[i][j] = f > 0;
                for (int k = 0; k < 4; ++k) {
                    gr[i][j << 2 | k] = (f >> (3 - k) & 1);
                }
            }
        }
        w <<= 2;
        // for (int i = 0; i < h; ++i) {
        //     for (int j = 0; j < w; ++j)
        //         cout << gr[i][j];
        //     cout << endl;
        // }
        for (int i = 0; i < h * w; ++i) {
            uf[i] = i;
            bd[i] = 0;
            st[i].clear();
        }
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (i > 0 && gr[i - 1][j] == gr[i][j]) Merge(i * w + j, (i - 1) * w + j);
                if (j > 0 && gr[i][j - 1] == gr[i][j]) Merge(i * w + j, i * w + (j - 1));
            }
        }
        string ans = "";
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (i == 0 || j == 0 || i == h - 1 || j == w - 1) {
                    // assert(gr[i][j] == 0);
                    bd[Find(i * w + j)] = 1;
                }
            }
        }
        int cp = 0;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (gr[i][j]) continue;
                int z = Find(i * w + j);
                if (bd[z]) continue;
                if (i > 0 && gr[i - 1][j]) 
                    st[Find((i - 1) * w + j)].insert(z);
                if (j > 0 && gr[i][j - 1])
                    st[Find(i * w + (j - 1))].insert(z);
            }
        }
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (gr[i][j] && Find(i * w + j) == i * w + j) {
                    assert(st[i * w + j].size() < 6);
                    if (st[i * w + j].size() >= 6) {
                        cout << "warning: " << st[i * w + j].size() << endl;
                    }
                    ans += tpl[st[i * w + j].size()];
                }
            }
        }
        sort(ans.begin(), ans.end());
        cout << "Case " << (++tc) << ": " << ans << endl;
    }
}
