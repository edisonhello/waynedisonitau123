#include <bits/stdc++.h>
using namespace std;

int pos[200005][2];
vector<pair<int, int>> G[200005];
long long d[200005];
bitset<200005> vis;

pair<int, int> meow(int from, int to) {
    return make_pair(to, min(abs(pos[from][0] - pos[to][0]), abs(pos[from][1] - pos[to][1])));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> pos[i][0] >> pos[i][1];
    vector<int> posx, posy;
    for (int i = 1; i <= n; ++i) {
        posx.push_back(i);
        posy.push_back(i);
    }
    sort(posx.begin(), posx.end(), [&] (const int &a, const int &b) -> bool { return make_pair(pos[a][0], pos[a][1]) < make_pair(pos[b][0], pos[b][1]); });
    sort(posy.begin(), posy.end(), [&] (const int &a, const int &b) -> bool { return make_pair(pos[a][1], pos[a][0]) < make_pair(pos[b][1], pos[b][0]); });
    for (int i = 0; i < n - 1; ++i) {
        G[posx[i]].push_back(meow(posx[i], posx[i + 1]));
        G[posx[i + 1]].push_back(meow(posx[i + 1], posx[i]));
        G[posy[i]].push_back(meow(posy[i], posy[i + 1]));
        G[posy[i + 1]].push_back(meow(posy[i + 1], posy[i]));
    }
    memset(d, 0x3f, sizeof(d));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    d[1] = 0; pq.emplace(0, 1);
    while (pq.size()) {
        int now = pq.top().second; pq.pop();
        if (vis[now]) continue;
        vis[now] = 1;
        for (auto &p : G[now]) {
            if (d[p.first] > d[now] + p.second) {
                d[p.first] = d[now] + p.second;
                pq.emplace(d[p.first], p.first);
            }
        }
    }
    cout << d[n] << endl;
}
