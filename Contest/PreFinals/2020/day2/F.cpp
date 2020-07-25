#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n; cin >> n;
    vector<int> a(n), b(n);
    set<int> ast;
    map<int, int> inva;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    for (int i = 0; i < n; ++i) ast.insert(a[i]);
    for (int i = 0; i < n; ++i) inva[a[i]] = i;

    auto GetMatch = [&] (int pos) {
        assert(ast.size());

        auto it1 = ast.lower_bound(pos);
        if (it1 != ast.end() && *it1 == pos) return inva[pos];
        if (it1 == ast.end()) {
            --it1;
            return inva[*it1];
        }
        if (it1 == ast.begin()) {
            return inva[*it1];
        }

        auto it2 = it1;
        --it1;
        if (pos - *it1 <= *it2 - pos) return inva[*it1];
        else return inva[*it2];
        
    };

    stack<int> stk;
    long long cost = 0;
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        int id = GetMatch(b[i]);
        if (id == i) {
            cost += abs(a[id] - b[i]);
            ans.push_back(i);
            ast.erase(a[id]);

            while (stk.size()) {
                int j = stk.top();
                int jd = GetMatch(b[j]);
                if (jd == j) {
                    stk.pop();
                    cost += abs(a[jd] - b[j]);
                    ans.push_back(j);
                    ast.erase(a[jd]);
                } else break;
            }
        } else stk.push(i);
    }

    assert(stk.empty());
    cout << cost << endl;
    for (int i : ans) cout << i + 1 << ' ';
    cout << endl;
}

