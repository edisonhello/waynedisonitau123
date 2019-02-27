#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
char s[maxn];

int weight(int x, int l) {
    int res = 0;
    for (int i = 1; i < l; ++i) {
        res += s[x + i - 1] != s[x + i];
    }
    return res;
}

int main() {
    scanf("%s", s);
    int n = strlen(s);
    vector<int> ans;
    for (int i = 0; i + 3 < n; i += 3) {
        int w = weight(i, 4);
        if (w < 2) {
            s[i + 1] = '1' - s[i + 1] + '0';
            s[i + 2] = '1' - s[i + 2] + '0';
            if (weight(i, 4) < 2) {
                s[i + 1] = '1' - s[i + 1] + '0';
                s[i + 2] = '1' - s[i + 2] + '0';
                s[i + 2] = '1' - s[i + 2] + '0';
                s[i + 3] = '1' - s[i + 3] + '0';
                assert(weight(i, 4) >= 2);
                ans.push_back(i + 2);
            } else {
                ans.push_back(i + 1);
            }
        }
    }
    int w = weight(n - 3, 3);
    if (w < 1) {
        s[n - 2] = '1' - s[n - 2];
        s[n - 1] = '1' - s[n - 1];
        ans.push_back(n - 2);
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i) printf("%d ", ans[i] + 1);
    puts("");
}
