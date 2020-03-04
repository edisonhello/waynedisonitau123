#include <bits/stdc++.h>
using namespace std;
 
vector<pair<int, int>> g[100005];
vector<vector<int>> pathes;
int curflow[100005];
int curcost[100005];
priority_queue<int, vector<int>, greater<int>> ppq[100005];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int length;
 
int n;
 
void dfs(int now, int pa, vector<int> &cur) {
    if (now == n) return;
    for (auto i : g[now]) if (i.first != pa) {
        cur.push_back(i.second);
        ++length;
        dfs(i.first, now, cur);
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int m; cin >> n >> m;
    long long totw = 0;
    while (m--) {
        int u, v, w; cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        totw += w;
    }
    long long cur = 0;
    for (auto &p : g[1]) {
        vector<int> v;
        v.push_back(p.second);
        length = 1;
        dfs(p.first, 1, v);
        sort(v.begin(), v.end());
        cur += (curflow[pathes.size()] = v[0]);
        for (int i : v) ppq[pathes.size()].push(i);
        pathes.push_back(v);
    }
    long long maxf = totw / length;
    long long fleft = maxf - cur;
    int np = pathes.size();
    for (int i = 0; i < np; ++i) {
        while (ppq[i].size() && ppq[i].top() == curflow[i]) {
            ppq[i].pop();
            ++curcost[i];
        }
        pq.emplace(curcost[i], i);
    }
 
    long long cost = 0;
    while (maxf > cur) {
        int i = pq.top().second;
        pq.pop();
 
        long long maxadd = (ppq[i].size() ? ppq[i].top() - curflow[i] : 1'000'000'000'000'000'000);
        long long add = (maxadd > fleft ? fleft : maxadd);
        fleft -= add;
        cur += add;
        cost += add * curcost[i];
        curflow[i] += add;
        while (ppq[i].size() && ppq[i].top() == curflow[i]) {
            ppq[i].pop();
            ++curcost[i];
        }
        pq.emplace(curcost[i], i);
    }
 
    cout << cost << endl;
}


