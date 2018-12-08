#include <bits/stdc++.h>
using namespace std;

char s[10][10000];

char tab[10][7][6] = {
    {
        "xxxxx",
        "x...x",
        "x...x",
        "x...x",
        "x...x",
        "x...x",
        "xxxxx"
    },
    {
        "....x",
        "....x",
        "....x",
        "....x",
        "....x",
        "....x",
        "....x"
    },
    {
        "xxxxx",
        "....x",
        "....x",
        "xxxxx",
        "x....",
        "x....",
        "xxxxx"
    },
    {
        "xxxxx",
        "....x",
        "....x",
        "xxxxx",
        "....x",
        "....x",
        "xxxxx"
    },
    {
        "x...x",
        "x...x",
        "x...x",
        "xxxxx",
        "....x",
        "....x",
        "....x"
    },
    {
        "xxxxx",
        "x....",
        "x....",
        "xxxxx",
        "....x",
        "....x",
        "xxxxx"
    },
    {
        "xxxxx",
        "x....",
        "x....",
        "xxxxx",
        "x...x",
        "x...x",
        "xxxxx",
    },
    {
        "xxxxx",
        "....x",
        "....x",
        "....x",
        "....x",
        "....x",
        "....x"
    },
    {
        "xxxxx",
        "x...x",
        "x...x",
        "xxxxx",
        "x...x",
        "x...x",
        "xxxxx"
    },
    {
        "xxxxx",
        "x...x",
        "x...x",
        "xxxxx",
        "....x",
        "....x",
        "xxxxx"
    }
};

int main() {
    for (int i = 0; i < 7; ++i) {
        scanf("%s", s[i]);
    }
    // for (int i = 0; i < 7; ++i) printf("%s\n", s[i]);
    /* for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 7; ++j) {
            for (int k = 0; k < 5; ++k) printf("%c", tab[i][j][k]);
            puts("");
        }
    } */
    int n = strlen(s[0]);
    int c[2] = { 0, 0 };
    int p = 0;
    for (int i = 0; i < n; i += 6) {
        bool plus = true;
        for (int j = 0; j < 10; ++j) {
            bool ok = true;
            for (int k = 0; k < 7; ++k) {
                for (int l = 0; l < 5; ++l) ok &= s[k][l + i] == tab[j][k][l];
            }
            if (ok) {
                plus = false;
                c[p] = c[p] * 10 + j;
            }
        }
        if (plus) {
            p++;
        }
    }
    int x = c[0] + c[1];
    vector<int> d;
    while (x) d.push_back(x % 10), x /= 10;
    reverse(d.begin(), d.end());
    for (int j = 0; j < 7; ++j) {
        for (int i = 0; i < (int)d.size(); ++i) {
            for (int k = 0; k < 5; ++k) printf("%c", tab[d[i]][j][k]);
            if (i + 1 < (int)d.size()) printf(".");
        }
        puts("");
    }
}
