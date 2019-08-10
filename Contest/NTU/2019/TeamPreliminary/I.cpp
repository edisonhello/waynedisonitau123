#include <bits/stdc++.h>
using namespace std;

int djs[100005];

int F(int x) { return djs[x] == x ? x : djs[x] = F(djs[x]); }
void U(int u, int v) { djs[F(u)] = F(v); }

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int N, M; cin >> N >> M;
    bool meetsN = false, meetsM = false, notSimple = false;
    vector<int> answers;

    int T; cin >> T; while (T--) {
        int n, m; cin >> n >> m;
        if (n == N) meetsN = true;
        if (m == M) meetsM = true;
        set<pair<int, int>> edges;
        for (int i = 1; i <= n; ++i) djs[i] = i;
        for (int i = 1; i <= m; ++i) {
            int u, v; cin >> u >> v;
            if (edges.count(minmax(u, v))) notSimple = true;
            if (u == v) notSimple = true;
            U(u, v);
            edges.insert(minmax(u, v));
        }
        bool same = true;
        for (int i = 1; i <= n; ++i) if (F(i) != F(1)) same = false;
        answers.push_back(int(same));
    }
    sort(answers.begin(), answers.end());
    if (answers[0] == answers.back()) cout << "India" << endl;
    else {
        if (notSimple) cout << "India" << endl;
        else if (!meetsN || !meetsM) cout << "India" << endl;
        else cout << "Normal" << endl;
    }
}
