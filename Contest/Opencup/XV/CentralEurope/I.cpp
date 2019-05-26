#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int p[maxn], t[maxn], pos[maxn], b[maxn];
set<pair<int, int>> segs[maxn];
bool used[maxn];

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
        --p[i];
    }

    for (int i = 0; i < n; ++i) scanf("%d", &t[i]);

    vector<vector<int>> cyc;
    for (int i = 0; i < n; ++i) {
        if (used[i]) continue;
        vector<int> v;
        for (int j = i, k = 0; !used[j]; j = p[j], ++k) {
            b[j] = (int)cyc.size();
            pos[j] = k;
            v.push_back(j);
            used[j] = true;
        }
        cyc.push_back(v);
    }

    // puts("done");

    int ans = 0;
    auto length = [&](int l, int r, int m) -> int {
        int res = (r - l + 1);
        if (res <= 0) res += m;
        return res;
    };

    auto debug = [&](string message = "") -> void {
        return;
        cout << message << endl;
        for (int i = 0; i < (int)cyc.size(); ++i) {
            printf("i = %d\n", i);
            for (auto it : segs[i])
                printf("(%d, %d) ", it.first, it.second);
            puts("");
        }
    };

    for (int i = 0; i < (int)cyc.size(); ++i) {
        int k = -1, m = (int)cyc[i].size();
        for (int j = 0; j < m; ++j) {
            if (k == -1 || t[cyc[i][j]] < t[cyc[i][k]]) k = j;
        }

        /* printf("hao123 i = %d: ", i);
        for (int j = 0; j < m; ++j)
            printf("%d ", cyc[i][j]);
        puts(""); */

        for (int j = k, jump = 0; jump < m; ) {
            int l = j, r = j, len = 1;
            while (jump < m && t[cyc[i][(r + 1) % m]] > t[cyc[i][r]]) {
                ++jump;
                ++len;
                r = (r + 1) % m;
            }

            segs[i].insert(make_pair(l, r));
            ans += length(l, r, m) / 2;
            j = (r + 1) % m;
            jump++;
        }
    }

    printf("%d\n", ans);

    debug();
    int q; scanf("%d", &q);
    while (q--) {
        int x, y; scanf("%d%d", &x, &y);
        --x;

        int m = (int)cyc[b[x]].size();
        auto it = segs[b[x]].upper_bound(make_pair(pos[x], 1e9));
        pair<int, int> sg;
        if (it == segs[b[x]].begin()) {
            sg = *prev(segs[b[x]].end());  
        } else {
            sg = *prev(it); 
        }

        debug("go!!!");

        if (pos[x] != sg.second) {
            int nxt = t[cyc[b[x]][(pos[x] + 1) % m]];
            if (y > nxt) {
                // puts("hey");
                // printf("sg = (%d, %d)\n", sg.first, sg.second);
                segs[b[x]].erase(sg);
                ans -= length(sg.first, sg.second, m) / 2;
                segs[b[x]].insert(make_pair((pos[x] + 1) % m, sg.second));
                ans += length((pos[x] + 1) % m, sg.second, m)  / 2;
                segs[b[x]].insert(make_pair(sg.first, pos[x]));
                ans += length(sg.first, pos[x], m) / 2;

                sg = make_pair(sg.first, pos[x]);
            }
        }

        debug();
        // printf("sg = (%d, %d)\n", sg.first, sg.second);

        if (pos[x] != sg.first) {
            int prv = t[cyc[b[x]][(pos[x] + m - 1) % m]];
            if (y < prv) {
                // puts("shoule be here");
                segs[b[x]].erase(sg);
                ans -= length(sg.first, sg.second, m) / 2;
                segs[b[x]].insert(make_pair(sg.first, (pos[x] + m - 1) % m));
                ans += length(sg.first, (pos[x] + m - 1) % m, m) / 2;
                segs[b[x]].insert(make_pair(pos[x], sg.second));
                ans += length(pos[x], sg.second, m) / 2;

                sg = make_pair(pos[x], sg.second);
            }
        }

        debug();
        // printf("sg = (%d, %d)\n", sg.first, sg.second);
        if (pos[x] == sg.second) {
            int nxt = t[cyc[b[x]][(pos[x] + 1) % m]];
            if (y < nxt && (pos[x] + 1) % m != sg.first) {
                segs[b[x]].erase(sg);
                ans -= length(sg.first, sg.second, m) / 2;
                auto itt = segs[b[x]].lower_bound(make_pair((pos[x] + 1) % m, -1));
                assert(itt != segs[b[x]].end());
                pair<int, int> sgg = *itt;
                segs[b[x]].erase(itt);

                ans -= length(sgg.first, sgg.second, m) / 2;

                ans += length(sg.first, sgg.second, m) / 2;
                sg = make_pair(sg.first, sgg.second);
                segs[b[x]].insert(sg);
            }
        }

        debug();
        // printf("sg = (%d, %d)\n", sg.first, sg.second);
        if (pos[x] == sg.first) {
            int prv = t[cyc[b[x]][(pos[x] + m - 1) % m]];
            if (y > prv && (pos[x] + m - 1) % m != sg.second) {
                ans -= length(sg.first, sg.second, m) / 2;
                auto it = segs[b[x]].lower_bound(sg);
                pair<int, int> sgg;
                if (it == segs[b[x]].begin()) {
                    sgg = *prev(segs[b[x]].end());
                } else {
                    sgg = *prev(it);
                }

                segs[b[x]].erase(sg);
                segs[b[x]].erase(sgg);
                ans -= length(sgg.first, sgg.second, m) / 2;
                ans += length(sgg.first, sg.second, m) / 2;
                sg = make_pair(sgg.first, sg.second);
                segs[b[x]].insert(sg);
            }
        }
        debug();
        // printf("sg = (%d, %d)\n", sg.first, sg.second);

        t[x] = y;
        debug();
        printf("%d\n", ans);
    }

    return 0;
}
