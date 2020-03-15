#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int djs[300005];
long long djswei[300005];
set<pair<long long, int>> djsqs[300005];
tuple<int, long long, int, long long, long long> query[300005];
    // u, when into u, v, when into v, w
int wei[300005];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> wei[i];
    for (int i = 1; i <= n; ++i) djs[i] = i;
    for (int i = 1; i <= n; ++i) djswei[i] = wei[i];

    priority_queue<int, vector<int>, greater<int>> okay;

    function<int(int)> Find = [&] (const int x) {
        return djs[x] == x ? x : djs[x] = Find(djs[x]);
    };

    function<pair<int, long long>(int, int)> GetOther = [&] (const int qi, int u) {
        if (Find(get<0>(query[qi])) == Find(u)) return make_pair(get<2>(query[qi]), get<3>(query[qi]) + (get<4>(query[qi]) + 1) / 2);
        else return make_pair(get<0>(query[qi]), get<1>(query[qi]) + (get<4>(query[qi]) + 1) / 2);
    };

    function<void(int, int)> Merge = [&] (int u, int v) {
        // cerr << "Merge: " << u << ' ' << v << endl;
        u = Find(u);
        v = Find(v);
        assert(u != v);
        if (djsqs[v].size() > djsqs[u].size()) swap(u, v);
        for (auto &p : djsqs[v]) {
            pair<int, long long> mucou_info = GetOther(p.second, v);
            if (mucou_info.first == u) {
                djsqs[u].erase(make_pair(mucou_info.second, p.second));
            } else {
                djsqs[u].insert(p);
            }
        }

        djswei[u] += djswei[v];
        djs[v] = u;

        while (djsqs[u].size()) {
            auto [val, qid] = *djsqs[u].begin();
            // cerr << "bruh " << val << ' ' << qid << endl;
            if (val <= djswei[u]) {
                djsqs[u].erase(djsqs[u].begin());

                if (Find(get<0>(query[qid])) == u) {
                    // cerr << "case 1" << endl;
                    int v = Find(get<2>(query[qid]));
                    long long wadd = djswei[u] - get<1>(query[qid]) + djswei[v] - get<3>(query[qid]);
                    djsqs[v].erase(make_pair(get<3>(query[qid]) + (get<4>(query[qid]) + 1) / 2, qid));
                    if (wadd >= get<4>(query[qid])) {
                        okay.push(qid);
                    } else {
                        get<4>(query[qid]) -= wadd;
                        get<1>(query[qid]) = djswei[u];
                        get<3>(query[qid]) = djswei[v];
                        djsqs[u].insert(make_pair(djswei[u] + (get<4>(query[qid]) + 1) / 2, qid));
                        djsqs[v].insert(make_pair(djswei[v] + (get<4>(query[qid]) + 1) / 2, qid));
                    }
                } else {
                    assert(Find(get<2>(query[qid])) == u);
                    // cerr << "case 2" << endl;

                    int v = Find(get<0>(query[qid]));
                    long long wadd = djswei[u] - get<3>(query[qid]) + djswei[v] - get<1>(query[qid]);
                    djsqs[v].erase(make_pair(get<1>(query[qid]) + (get<4>(query[qid]) + 1) / 2, qid));
                    if (wadd >= get<4>(query[qid])) {
                        okay.push(qid);
                    } else {
                        get<4>(query[qid]) -= wadd;
                        get<3>(query[qid]) = djswei[u];
                        get<1>(query[qid]) = djswei[v];
                        djsqs[u].insert(make_pair(djswei[u] + (get<4>(query[qid]) + 1) / 2, qid));
                        djsqs[v].insert(make_pair(djswei[v] + (get<4>(query[qid]) + 1) / 2, qid));
                    }
                }
            } else break;
        }
    };

    for (int i = 1; i <= m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        if (wei[u] + wei[v] >= w) {
            query[i] = make_tuple(u, 0, v, 0, w);
            okay.push(i);
            continue;
        }
        query[i] = make_tuple(u, djswei[u], v, djswei[v], w - djswei[u] - djswei[v]);
        djsqs[u].insert(make_pair(djswei[u] + (w - djswei[u] - djswei[v] + 1) / 2, i));
        djsqs[v].insert(make_pair(djswei[v] + (w - djswei[u] - djswei[v] + 1) / 2, i));
    }

    vector<int> ans;
    while (okay.size()) {
        int qnow = okay.top(); okay.pop();
        if (Find(get<0>(query[qnow])) == Find(get<2>(query[qnow]))) continue;
        ans.push_back(qnow);
        Merge(get<0>(query[qnow]), get<2>(query[qnow]));
    }

    cout << ans.size() << endl;
    for (int i : ans) cout << i << ' ';
    cout << endl;
}

