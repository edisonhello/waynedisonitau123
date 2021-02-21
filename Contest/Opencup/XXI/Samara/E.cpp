#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    vector<int> q(N), w(N), e(N);
    for (int i = 0; i < N; ++i) cin >> q[i] >> w[i] >> e[i];

    auto Positive = [](int x) { return x > 0; };
    if (all_of(q.begin(), q.end(), Positive) ||
        all_of(w.begin(), w.end(), Positive) ||
        all_of(e.begin(), e.end(), Positive)) {
        cout << "Infinity\n";
        return 0;
    }

    vector<int> Order(N);
    iota(Order.begin(), Order.end(), 0);
    sort(Order.begin(), Order.end(), [&](int i, int j) { return q[i] < q[j]; });
    vector<int> Qt;
    for (int x : q) if (x > 0) Qt.push_back(x - 1);
    sort(Qt.begin(), Qt.end());
    Qt.resize(unique(Qt.begin(), Qt.end()) - Qt.begin());

    set<pair<int, int>> rect;
    multiset<int> candidate;
    constexpr int kInf = 2'000'000'000;

    auto AddRect = [&](int i) {
        // cerr << "add i = " << i << endl;
        auto iter = rect.upper_bound(make_pair(w[i], kInf));

        auto Remove = [&](auto iter) {
            if (iter != rect.begin()) {
                int v = iter->first + prev(iter)->second;
                candidate.erase(candidate.find(v));
            }
            if (next(iter) != rect.end()) {
                int v = iter->second + next(iter)->first;
                candidate.erase(candidate.find(v));
            }
            if (iter != rect.begin() && next(iter) != rect.end()) {
                int v = prev(iter)->second + next(iter)->first;
                candidate.insert(v);
            }
        };


        if (iter != rect.begin()) {
            auto piter = prev(iter);
            assert(piter->first <= w[i]);
            if (piter->second <= e[i]) return; // covered by other rectagles.

            if (piter->first == w[i] && piter->second >= e[i]) {
                Remove(piter);
                rect.erase(piter);
                iter = rect.upper_bound(make_pair(w[i], kInf));
            }
        }

        while (iter != rect.end() && iter->second >= e[i]) {
            Remove(iter);
            iter = rect.erase(iter);
        }
        iter = rect.upper_bound(make_pair(w[i], kInf));
        if (iter != rect.begin()) {
            int v = prev(iter)->second + w[i];
            candidate.insert(v);
        }
        if (iter != rect.end()) {
            int v = e[i] + iter->first;
            candidate.insert(v);
        }
        if (iter != rect.begin() && iter != rect.end()) {
            int v = prev(iter)->second + iter->first;
            candidate.erase(candidate.find(v));
        }
        rect.insert(make_pair(w[i], e[i]));
    };

    auto Debug = [&]() {
        cerr << "rect: ";
        for (auto it : rect) cerr << "(" << it.first << ", " << it.second << ") ";
        cerr << endl;
        cerr << "candidate: ";
        for (auto it : candidate) cerr << it << " ";
        cerr << endl;
    };

    int64_t ans = 0;
    for (int i = 0, j = 0; i < Qt.size(); ++i) {
        while (j < N && q[Order[j]] <= Qt[i]) AddRect(Order[j++]);
        // cerr << "Qt = " << Qt[i] << endl;
        // Debug();
        if (rect.empty()) {
            cout << "Infinity\n";
            return 0;
        }
        if (rect.begin()->first > 0 || rect.rbegin()->second > 0) {
            cout << "Infinity\n";
            return 0;
        }
        if (!candidate.empty()) ans = max(ans, static_cast<int64_t>(*candidate.rbegin()) - 2 + Qt[i]);
    }
    cout << ans << "\n";
    return 0;
}

