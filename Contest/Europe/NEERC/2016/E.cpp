#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("expect.in", "r", stdin);
    freopen("expect.out", "w", stdout);
    int N, Q;
    cin >> N >> Q;
    vector<tuple<int, int, int>> event;
    int delta = 0;
    for (int i = 0; i < N; ++i) {
        string S;
        cin >> S;
        if (S == "+") {
            int t, k;
            cin >> t >> k;
            delta += k;
            event.emplace_back(t, k, 1);
        } else {
            int t, k;
            cin >> t >> k;
            delta -= k;
            event.emplace_back(t, k, -1);
        }
    }

    delta = max(0, -delta);
    vector<pair<int, int>> stk;
    int sum = delta;
    int64_t wait = 0;
    vector<tuple<int, int, int>> nodes;
    // cerr << "delta = " << delta << endl;
    for (int i = 0; i < event.size(); ++i) {
        int t = get<0>(event[i]), k = get<1>(event[i]);
        // cerr << "t = " << t << " k = " << k << endl;
        if (get<2>(event[i]) == 1) {
            while (!stk.empty() && k > 0) {
                int g = stk.back().second;
                int h = min(g, k);
                wait += 1LL * (t - stk.back().first) * h;
                nodes.emplace_back(h, stk.back().first, t);
                stk.back().second -= h;
                k -= h;
                if (stk.back().second == 0) stk.pop_back();
            }
            sum += k;
        } else {
            int h = min(sum, k);
            k -= h;
            sum -= h;
            if (k > 0) {
                stk.emplace_back(t, k);
            }
        }
    }
    sort(nodes.begin(), nodes.end(), [&](auto X, auto Y) {
        if (get<1>(X) == get<1>(Y)) return get<2>(X) > get<2>(Y);
        return get<1>(X) < get<1>(Y);
    });

    int ptr = 0;
    int M = nodes.size();
    vector<int> fa(M, -1);
    vector<vector<int>> T(M);

    auto BuildTree = [&](auto dfs, int ptr) -> int {
        int R = get<2>(nodes[ptr]);
        int X = ptr;
        ptr++;
        while (ptr < nodes.size() && get<2>(nodes[ptr]) <= R) {
            T[X].push_back(ptr);
            fa[ptr] = X;
            ptr = dfs(dfs, ptr);
        }
        return ptr;
    };

    while (ptr < M) {
        ptr = BuildTree(BuildTree, ptr);
    }

    // cerr << "wait = " << wait << "\n";
    assert(stk.empty());
    vector<int64_t> res(Q);
    vector<int> B(Q);
    vector<int> order;
    for (int i = 0; i < Q; ++i) {
        cin >> B[i];
        if (B[i] < delta) {
            res[i] = -1;
        } else {
            order.push_back(i);
        }
    }

    int64_t S = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (int i = 0; i < M; ++i) {
        if (fa[i] == -1) {
            pq.emplace(get<0>(nodes[i]), i);
            S += get<2>(nodes[i]) - get<1>(nodes[i]);
        }
    }

    int tag = 0;
    auto Add = [&](int X) {
        while (X > 0 && !pq.empty()) {
            int h = pq.top().first - tag;
            int g = min(h, X);
            // cerr << "g = " << g << "S = " << S << "\n";
            wait -= g * S;
            tag += g;
            h -= g;
            X -= g;
            if (h == 0) {
                int p = pq.top().second;
                pq.pop();
                S -= get<2>(nodes[p]) - get<1>(nodes[p]);
                for (int u : T[p]) {
                    pq.emplace(get<0>(nodes[u]) + tag, u);
                    S += get<2>(nodes[u]) - get<1>(nodes[u]);
                }
            }
        } 
    };

    sort(order.begin(), order.end(), [&](int i, int j) { return B[i] < B[j]; });
    for (int i = 0, prv = delta; i < order.size(); ++i) {
        int X = B[order[i]] - prv;
        if (X > 0) Add(X);
        res[order[i]] = wait;
        prv = B[order[i]];
    }

    for (int i = 0; i < Q; ++i) {
        if (res[i] == -1) cout << "INFINITY\n";
        else cout << res[i] << "\n";
    }
    return 0;
}

