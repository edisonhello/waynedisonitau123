#include <bits/stdc++.h>
using namespace std;

const int kN = 10000;
int p[kN], nxt[kN], prv[kN], rv[kN], pos[kN], r[kN];
int ans[kN], mk[kN];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &p[i]);
            --p[i];
            rv[p[i]] = i;
            r[p[i]] = i;
        }
        for (int i = 0; i < n; ++i) {
            p[i] = r[i];
            rv[p[i]] = i;
        }
        vector<int> s(p, p + n);

        auto Erase = [&](int x) {
            // printf("x = %d prv = %d nxt = %d\n", x, prv[x], nxt[x]);
            if (~prv[x]) nxt[prv[x]] = nxt[x];
            if (~nxt[x]) prv[nxt[x]] = prv[x];
        };

        for (int z = 1; z <= 24; ++z) {
            // printf("z = %d\n", z);
            if (s.empty()) break;
            for (int i = 0; i < s.size(); ++i) {
                prv[s[i]] = (i == 0) ? -1 : s[i - 1];
                nxt[s[i]] = (i + 1 == s.size()) ? -1 : s[i + 1];
                mk[s[i]] = false;
                pos[s[i]] = i;
            }
            sort(s.begin(), s.end(), greater<int>());
            vector<int> w;
            for (int i = 0; i < s.size(); ++i) {
                // printf("z = %d s[i] = %d mk = %d\n", z, s[i] + 1, mk[s[i]]);
                if (!mk[s[i]]) {
                    if (~prv[s[i]]) mk[prv[s[i]]] = true;
                    if (~nxt[s[i]]) mk[nxt[s[i]]] = true;
                    ans[rv[s[i]]] = z;
                } else {
                    w.push_back(s[i]);
                }
                Erase(s[i]);
            }
            sort(w.begin(), w.end(), [&](int i, int j) { return pos[i] < pos[j]; });
            s.swap(w);
        }
        for (int i = 0; i < n; ++i) printf("%d ", ans[i]);
        puts("");
    }
}
