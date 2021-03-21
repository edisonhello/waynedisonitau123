#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector<tuple<int, int, int>> E(N - 1);
    for (int i = 0; i < N - 1; ++i) {
        cin >> get<1>(E[i]) >> get<2>(E[i]) >> get<0>(E[i]);
        get<1>(E[i])--;
        get<2>(E[i])--;
    }
    vector<int> uf(N);
    vector<int> value(N);
    iota(uf.begin(), uf.end(), 0);
    iota(value.begin(), value.end(), 0);

    function<int(int)> Find = [&](int x) {
        if (x == uf[x]) return x;
        return uf[x] = Find(uf[x]);
    };

    sort(E.begin(), E.end());

    vector<vector<int>> event(N);
    for (int i = 0; i < N - 1; ++i) {
        auto [w, u, v] = E[i];
        u = Find(u);
        v = Find(v);
        event[max(value[u], value[v])].push_back(w);
        value[u] = min(value[u], value[v]);
        uf[v] = u;
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    int64_t sum = 0;
    for (int i = 0; i < N; ++i) {
        for (int w : event[i]) {
            pq.push(w); 
            sum += w;
        }
        while (pq.size() > K) {
            sum -= pq.top();
            pq.pop();
        }
        cout << sum << "\n";
    }
}

