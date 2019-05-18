#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int a[maxn], dv[maxn];
vector<int> pos[maxn];
vector<int> pr;

int main() {
    for (int i = 2; i < maxn; ++i) {
        if (!dv[i]) pr.push_back(i), dv[i] = i;
        for (int j = 0; i * pr[j] < maxn; ++j) {
            dv[i * pr[j]] = pr[j];
            if (i % pr[j] == 0)
                break;
        }
    }

    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        while (x > 1) {
            int d = dv[x];
            while (x % d == 0) x /= d;

            pos[d].push_back(i);
        }
    }

    pair<int, int> ans = make_pair(-1, -1);
    for (int i = 0; i < n; ++i) {
        if (a[i] > 1) {
            if (ans.first == -1)
                ans = make_pair(i, i);
            if (i - 1 >= 0)
                ans = make_pair(i - 1, i);
            if (i + 1 < n)
                ans = make_pair(i, i + 1);
        }
    }
    for (int i = 0; i < (int)pr.size(); ++i) {
        int p = pr[i];
        vector<int> v;
        for (int j = 0; j < (int)pos[p].size(); ++j) {
            int l = 0, r = (int)v.size();
            while (r - l > 1) {
                int m = (l + r) >> 1;
                int k = v[m];
                if ((j - k + 1) * 2 < (pos[p][j] - pos[p][k] + 1))
                    l = m;
                else
                    r = m;
            }

            if (l < (int)v.size() && (j - v[l] + 1) * 2 >= (pos[p][j] - pos[p][v[l]] + 1)) {
                int ll = v[l], rr = j;
                int prv = ll == 0 ? 0 : pos[p][ll - 1] + 1;
                int nxt = rr == pos[p].size() - 1 ? n - 1 : pos[p][rr + 1] - 1;
                int leng = (rr - ll + 1) * 2;
                int tleng = pos[p][rr] - pos[p][ll] + 1;
                int tl = pos[p][ll], tr = pos[p][rr];
                int f = min(tl - prv, leng - tleng);
                tl -= f;
                tleng += f;
                int b = min(nxt - tr, leng - tleng);
                tr += b;
                tleng += b;

                if (tleng > ans.second - ans.first + 1) {
                    ans = make_pair(tl, tr);
                }
            } 
            l++;

            if (l < (int)v.size() && (j - v[l] + 1) * 2 >= (pos[p][j] - pos[p][v[l]] + 1)) {
                int ll = v[l], rr = j;
                int prv = ll == 0 ? 0 : pos[p][ll - 1] + 1;
                int nxt = rr == pos[p].size() - 1 ? n - 1 : pos[p][rr + 1] - 1;
                int leng = (rr - ll + 1) * 2;
                int tleng = pos[p][rr] - pos[p][ll] + 1;
                int tl = pos[p][ll], tr = pos[p][rr];
                int f = min(tl - prv, leng - tleng);
                tl -= f;
                tleng += f;
                int b = min(nxt - tr, leng - tleng);
                tr += b;
                tleng += b;

                if (tleng > ans.second - ans.first + 1) {
                    ans = make_pair(tl, tr);
                }
            } 
            if (v.empty() || (j - 1) * 2 - (pos[p][j] - 1) < (v.back() - 1) * 2 - (pos[p][v.back()] - 1))
                v.push_back(j);

        }
    }

    printf("%d %d\n", ans.first + 1, ans.second + 1);
    return 0;
}
