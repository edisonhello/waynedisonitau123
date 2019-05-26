#include <bits/stdc++.h>
using namespace std;

const int maxn = 20;
vector<tuple<int, int, int>> segs[maxn];

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        int l, r, d; scanf("%d%d%d", &l, &r, &d);
        segs[d - 1].emplace_back(l, r, i);
    }

    for (int i = 0; i < m; ++i) {
        if ((int)segs[i].size() < 2) {
            puts("NIE");
            continue;
        }

        sort(segs[i].begin(), segs[i].end(), [&](tuple<int, int, int> i, tuple<int, int, int> j) {
            return get<0>(i) > get<0>(j);
        });

        tuple<int, int, int> x = segs[i][0];

        sort(segs[i].begin(), segs[i].end(), [&](tuple<int, int, int> i, tuple<int, int, int> j) {
            return get<1>(i) < get<1>(j);
        });

        tuple<int, int, int> y = segs[i][0];

        if (get<1>(y) < get<0>(x)) {
            printf("TAK %d %d\n", get<2>(y) + 1, get<2>(x) + 1);
        } else {
            puts("NIE");
        }
    }
}
