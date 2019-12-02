#include <bits/stdc++.h>
using namespace std;
#define int int64_t

struct seg {
    long long l, r, t;
} a[200005];

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].l >> a[i].r >> a[i].t;
    
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> event;
    for (int i = 1; i <= n; ++i) {
        event.emplace(a[i].l + a[i].t, 0, -i);
        event.emplace(a[i].r, 0, i);
    }
    // sort(event.begin(), event.end());

    int now = -1;
    int ptime = 0;
    set<pair<int, int>> active;
    int ans = 0;
    while (event.size()) {
        auto p = event.top(); event.pop();
        // cerr << "sweep time = " << get<0>(p) << endl;
        // cerr << "now = " << now << ", ptime = " << ptime << endl;
        if (now > 0) {
            int timing = get<0>(p);
            ptime = max(ptime, a[now].l);
            int tseg = timing - ptime;
            int zz = tseg / a[now].t;
            ans += zz;
            ptime += zz * a[now].t;
            // cout << "timing tseg zz " << timing << " " << tseg << " " << zz << endl;
            // cerr << "zz = " << zz << endl;
        }
        if (get<2>(p) < 0) { // open
            int id = -get<2>(p);
            // cerr << id << " open " << endl;
            if (now == -1) {
                now = id;
                ptime = max(a[id].l, ptime);
            }
            else {
                int nowend = ptime + a[now].t;
                int idend = get<0>(p);
                // cout << "id = " << id << ", nowend = " << nowend << ", idend = " << idend << endl;
                if (idend <= nowend && a[id].t < a[now].t) {
                    ptime = max(ptime, a[id].l);
                    now = id;
                } else if (a[id].t < a[now].t) {
                    // if (nowend + a[id].t <= a[id].r) {
                    //     event.emplace(nowend, a[id].t, id);
                    //     a[id].l = nowend;
                    // }
                }
            }
            active.insert(make_pair(a[id].t, id));
        } else { // close
            int id = get<2>(p);
            // cerr << id << " close" << endl;
            active.erase(make_pair(a[id].t, id));
            if (id == now) {
                if (active.empty()) now = -1;
                else now = active.begin()->second;
            }
        }
    }
    cout << ans << endl;
}
