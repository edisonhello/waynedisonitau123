#include <bits/stdc++.h>
using namespace std;

pair<int, int> seg[200005];
int ans[200005];

vector<pair<int, int>> segs[200005];
int cov[200005];

void check_answer(int n, int k, int ans_size) {
    for (int i = 1; i <= k; ++i) segs[i].clear();
    for (int i = 1; i <= n; ++i) if (ans[i] < 1 || ans[i] > k) assert(0);
    for (int i = 1; i <= n; ++i) segs[ans[i]].push_back(seg[i]);
    for (int i = 1; i <= k; ++i) sort(segs[i].begin(), segs[i].end());
    memset(cov, 0, sizeof(cov));
    for (int i = 1; i <= k; ++i) {
        auto tmp = segs[i]; segs[i].clear();
        for (auto &p : tmp) {
            if (segs[i].empty() || p.first > segs[i].back().second) {
                segs[i].push_back(p);
            } else {
                segs[i].back().second = max(segs[i].back().second, p.second);
            }
        }
        for (auto &p : segs[i]) {
            ++cov[p.first]; --cov[p.second];
        }
    }
    for (int i = 1; i <= 200000; ++i) cov[i] += cov[i - 1];
    int my_ans = 0;
    for (int i = 0; i <= 200000; ++i) my_ans += (cov[i] >= k);
    assert(my_ans == ans_size);
    memset(cov, 0, sizeof(cov));
    for (int i = 1; i <= n; ++i) ++cov[seg[i].first], --cov[seg[i].second];
    for (int i = 1; i <= 200000; ++i) cov[i] += cov[i - 1];
    int full_k = 0;
    for (int i = 0; i <= 200000; ++i) full_k += (cov[i] >= k);
    assert(full_k == ans_size);
}

int main() {
    int t; scanf("%d", &t); while(t--) {
        int n, k; scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i) scanf("%d%d", &seg[i].first, &seg[i].second);
        for (int i = 1; i <= n; ++i) ans[i] = 0;
        vector<pair<int, int>> ev;
        for (int i = 1; i <= n; ++i) ev.emplace_back(seg[i].first, i), ev.emplace_back(seg[i].second, -i);
        sort(ev.begin(), ev.end());
        vector<int> need;
        set<int> noc;
        for (int i = 1; i <= k; ++i) need.push_back(i);
        int prev = 0, ans_size = 0;
        for (auto &e : ev) {
            // cerr << "event " << e.first << " " << e.second << " need size: " << need.size() << endl;
            if (e.first != prev) {
                if (need.empty()) ans_size += e.first - prev;
                prev = e.first;
            }
            if (e.second > 0) { // new segment
                if (need.size()) {
                    ans[e.second] = need.back();
                    need.pop_back();
                } else {
                    noc.insert(e.second);
                }
            } else { // end of segment
                e.second *= -1;
                if (ans[e.second]) {
                    need.push_back(ans[e.second]);
                } else {
                    noc.erase(e.second);
                }
                while (need.size() && noc.size()) {
                    int id = *noc.begin();
                    noc.erase(noc.begin());
                    ans[id] = need.back();
                    need.pop_back();
                }
            }
        }
        printf("%d\n", ans_size);
        for (int i = 1; i <= n; ++i) if (!ans[i]) ans[i] = 1;
        for (int i = 1; i <= n; ++i) printf("%d%c", ans[i], " \n"[i == n]);
        // check_answer(n, k, ans_size);
    }
}
