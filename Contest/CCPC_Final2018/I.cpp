#include <bits/stdc++.h>
using namespace std;

pair<int, int> pos[100005];

int main() {
    int t; scanf("%d", &t); for (int T = 1; T <= t; ++T) {
        printf("Case %d: ", T);
        int n; scanf("%d", &n);
        vector<pair<int, int>> xs, ys; xs.reserve(n); ys.reserve(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &pos[i].first, &pos[i].second);
            xs.emplace_back(pos[i].first, i);
            ys.emplace_back(pos[i].second, i);
        }
        sort(xs.begin(), xs.end());
        int max_x_count = 0;
        for (int i = 0, j; i < (int)xs.size(); i = j) {
            for (j = i; j < (int)xs.size(); ++j) {
                if (xs[i].first != xs[j].first) break;
            }
            max_x_count = max(max_x_count, j - i);
        }
        set<int> max_x_set;
        for (int i = 0, j; i < (int)xs.size(); i = j) {
            for (j = i; j < (int)xs.size(); ++j) {
                if (xs[i].first != xs[j].first) break;
            }
            if (j - i == max_x_count) {
                max_x_set.insert(xs[i].first);
            }
        }
        sort(ys.begin(), ys.end());
        int max_y_count = 0;
        for (int i = 0, j; i < (int)ys.size(); i = j) {
            for (j = i; j < (int)ys.size(); ++j) {
                if (ys[i].first != ys[j].first) break;
            }
            max_y_count = max(max_y_count, j - i);
        }
        set<int> max_y_set;
        for (int i = 0, j; i < (int)ys.size(); i = j) {
            for (j = i; j < (int)ys.size(); ++j) {
                if (ys[i].first != ys[j].first) break;
            }
            if (j - i == max_y_count) {
                max_y_set.insert(ys[i].first);
            }
        }
        if (max_x_count == 1 && max_y_count == 1) {
            if (n == 1) {
                printf("%d %d\n", 1, 1);
            } else {
                printf("%d %lld\n", 2, 1ll * n * (n - 1) / 2);
            }
            continue;
        }
        if (max_x_count == n || max_y_count == n) {
            printf("%d %d\n", n, 1);
            continue;
        }
        map<int, vector<int>> mp;
        for (int i = 0; i < n; ++i) {
            if (max_x_set.count(pos[i].first) == 0) continue;
            mp[pos[i].first].push_back(i);
        }
        int good = 0;
        // cerr << "max_y_set : "; for (int i : max_y_set) cerr << i << " "; cerr << endl;
        for (auto &p : mp) {
            set<int> bad_y_set;
            for (int i : p.second) {
                // cerr << "i = " << i << endl;
                if (max_y_set.count(pos[i].second)) bad_y_set.insert(pos[i].second);
            }
            // cerr << "max_y_set.size() = " << max_y_set.size() << " , bad_y_set.size() = " << bad_y_set.size() << endl;
            good += max_y_set.size() - bad_y_set.size();
            // cerr << "At x = " << p.first << " , ans += " << max_y_set.size() - bad_y_set.size() << endl;
        }
        if (good) printf("%d %d\n", max_x_count + max_y_count, good);
        else {
            long long ans = 1ll * (int)max_x_set.size() * (int)max_y_set.size();
            int cnt_less_x = 0;
            for (int i = 0, j; i < (int)xs.size(); i = j) {
                bool ok = true;
                for (j = i; j < (int)xs.size(); ++j) {
                    if (xs[i].first != xs[j].first) break;
                    if (max_y_set.count(ys[xs[j].second].first)) ok = false;
                }
                if (j - i == max_x_count - 1 && ok) {
                    cnt_less_x++;
                }
            }
            int cnt_less_y = 0;
            for (int i = 0, j; i < (int)ys.size(); i = j) {
                bool ok = true;
                for (j = i; j < (int)ys.size(); ++j) {
                    if (ys[i].first != ys[j].first) break;
                    if (max_x_set.count(xs[ys[j].second].first)) ok = false;
                }
                if (j - i == max_y_count - 1 && ok) {
                    ++cnt_less_y;
                }
            }
            ans += 1ll * (int)max_x_set.size() * cnt_less_y;
            ans += 1ll * cnt_less_x * (int)max_y_set.size();
            printf("%d %lld\n", max_x_count + max_y_count - 1, ans);
        }
    }
}
