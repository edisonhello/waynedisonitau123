#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;
int d[maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &d[i]);
    vector<pair<int, int>> ans;
    for (int i = 0; i < n; ) {
        int l = i, j = i;
        int x = 1e9, y = 1e9;
        while (j < n) {
            int px = min(x, d[j] - j);
            int py = min(y, d[j] + j);
            if (px + l <= 0 && py - j <= 0) break;
            x = px;
            y = py;
            ++j;
        }
        if (x + l > 0) ans.emplace_back(i, j - 1);
        else ans.emplace_back(j - 1, i);
        i = j;
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i)
        printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
    return 0;
}
