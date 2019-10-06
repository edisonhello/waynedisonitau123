#include <bits/stdc++.h>
using namespace std;

pair<int, double> work[300005];
int endtime[300005], premax[300005];
double pprod[300005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int sec; double prob;
        cin >> sec >> prob;
        work[i] = make_pair(sec, prob);
    }
    ++n;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int itr = 1;
    while ((int)pq.size() < m && itr <= n) {
        pq.emplace(work[itr].first, itr);
        endtime[itr] = work[itr].first;
        ++itr;
    }
    while (itr <= n) {
        auto p = pq.top(); pq.pop();
        int nowt = p.first;
        int workid = p.second;
        pq.emplace(nowt + work[itr].first, itr);
        endtime[itr] = work[itr].first + nowt;
        ++itr;
    }
    for (int i = 1; i <= n; ++i) premax[i] = max(premax[i - 1], endtime[i]);
    pprod[0] = 1;
    for (int i = 1; i <= n; ++i) pprod[i] = pprod[i - 1] * work[i].second;
    double ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += pprod[i - 1] * (1 - work[i].second) * premax[i];
    }
    cout << fixed << setprecision(12) << ans << endl;
}
