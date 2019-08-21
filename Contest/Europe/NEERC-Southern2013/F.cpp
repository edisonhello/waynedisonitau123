#include <bits/stdc++.h>
using namespace std;

pair<int, double> work[300005];
int endtime[300005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int sec; double prob;
        cin >> sec >> prob;
        work[i] = make_pair(sec, prob);
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    double cur_ch = 1;
    double ans = 0;
    int itr = 1;
    while ((int)pq.size() < m && itr <= n) {
        pq.emplace(work[itr].first, itr);
        endtime[itr] = max(endtime[itr - 1], work[itr].first);
        ++itr;
    }
    while (itr <= n) {
        auto p = pq.top(); pq.pop();
        int nowt = p.first;
        int workid = p.second;
        ans += (1 - work[workid].second) * endtime[workid];
        cur_ch *= work[workid].second;
        pq.emplace(nowt + work[itr].first, itr);
        endtime[itr] = max(endtime[itr - 1], work[itr].first + nowt);
        ++itr;
    }
    while (pq.size()) {
        auto p = pq.top(); pq.pop();
        int nowt = p.first;
        int workid = p.second;
        // cerr << nowt << " " << workid << " " << endtime[workid] << endl;
        if (pq.size()) {
            // cerr << cur_ch << " " << work[workid].second << " " << endtime[workid] << endl;
            ans += cur_ch * (1 - work[workid].second) * endtime[workid];
            cur_ch *= work[workid].second;
        } else {
            ans += cur_ch * nowt;
        }
    }
    cout << fixed << setprecision(11) << ans << endl;
}
