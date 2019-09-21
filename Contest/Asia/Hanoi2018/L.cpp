#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e4 + 5;
const int maxq = 3e5 + 5;
int l[maxq], r[maxq], k[maxq], nxt[maxn][26], last[26], ans[maxq];
vector<int> qr[maxn];
vector<pair<int, int>> kz[maxn];
string t[maxn];

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    string s; cin >> s;
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> t[i];
    sort(t, t + n);
    for (int i = 0; i < q; ++i) {
        cin >> l[i] >> r[i] >> k[i];
        --l[i], --r[i];
        qr[l[i]].push_back(i);
    }

    for (int i = 0; i < 26; ++i) last[i] = (int)s.size();
    for (int i = (int)s.size() - 1; i >= 0; --i) {
        last[s[i] - 'a'] = i;
        for (int j = 0; j < 26; ++j) nxt[i][j] = last[j];
    }
    memset(ans, -1, sizeof(ans));
    for (int i = 0; i < (int)s.size(); ++i) {
        for (int j = i; j < (int)s.size(); ++j) kz[j].clear();
        for (int j = 0; j < (int)qr[i].size(); ++j) {
            // cout << "qr[i][j] = " << qr[i][j] << endl;
            kz[r[qr[i][j]]].emplace_back(k[qr[i][j]], qr[i][j]);
        }
        for (int j = i; j < (int)s.size(); ++j) {
            sort(kz[j].begin(), kz[j].end());
            reverse(kz[j].begin(), kz[j].end());
            for (int k = 0; k + 1 < (int)kz[j].size(); ++k) kz[j][k].first -= kz[j][k + 1].first;
        }
        // printf("iii = %d\n", i);
        for (int j = 0; j < n; ++j) {
            int p = i - 1;
            for (int k = 0; p < (int)s.size() && k < (int)t[j].size(); ++k) {
                ++p;
                if (p >= (int)s.size()) break;
                p = nxt[p][t[j][k] - 'a'];
            }
            for (int k = p; k < (int)s.size(); ++k) {
                if (!kz[k].empty()) {
                    --kz[k].back().first;
                    while (!kz[k].empty() && kz[k].back().first == 0) {
                        // cout << "j = " << j << " back() = " << kz[k].back().second << endl;
                        ans[kz[k].back().second] = j;
                        kz[k].pop_back();
                    }
                }
            }
        }
    }
    // cout << "ans[0] = " << ans[0] << endl;
    for (int i = 0; i < q; ++i) {
        if (ans[i] == -1) {
            cout << "NO SUCH WORD\n";
        } else {
            // cout << "i = " << i << endl;
            int l = min((int)t[ans[i]].size(), 10);
            cout << t[ans[i]].substr(0, l) << '\n';
        }
    }
    return 0;
}


