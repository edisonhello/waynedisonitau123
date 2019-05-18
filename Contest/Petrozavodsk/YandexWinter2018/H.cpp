#include <bits/stdc++.h>
using namespace std;

int t[300005];
map<int, int> cnt;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int k, n, m; cin >> k >> n >> m;
    for (int i = 1; i <= k; ++i) {
        cin >> t[i];
        if (t[i] == -1) {
            if (i == 1) t[i] = 1;
            else t[i] = t[i - 1];
        }
        if (t[i] < t[i - 1]) {
            cout << -1 << endl;
            exit(0);
        }
        ++cnt[t[i]];
    }
    deque<int> dq;
    for (int i = 1; i <= k; ++i) dq.push_back(t[i]);
    if (int(dq.size()) > n) {
        cout << -1 << endl;
        exit(0);
    }
    int can_use = k, now_use = 0, now_num = m + 1;
    deque<int> dq2;
    while (int(dq.size() + dq2.size()) < n) {
        if (can_use <= 0) break;
        if (now_num <= 0) break;
        if (now_use <= 0) {
            --now_num;
            auto it = cnt.find(now_num);
            if (it != cnt.end()) can_use -= it->second;
            now_use = can_use;
            continue;
        }
        --now_use;
        dq2.push_back(now_num);
    }
    if (int(dq.size() + dq2.size()) < n) {
        cout << -1 << endl;
        exit(0);
    }
    for (int i : dq2) cout << i << ' '; 
    for (int i : dq) cout << i << ' '; 
    cout << endl;

}
