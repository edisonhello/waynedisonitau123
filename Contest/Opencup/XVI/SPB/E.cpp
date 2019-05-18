#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> __v;
vector<int> __cur;

void dfs(int now, int upp, int left) {
    if (left == 0) {
        if (now == 0) __v.push_back(__cur);
        return;
    }
    if (now <= 0) return;
    for (; upp > 0; --upp) {
        __cur.push_back(upp);
        dfs(now - upp, upp, left - 1);
        __cur.pop_back();
    }
}
vector<pair<long long, long long>> find_answer(vector<pair<long long, long long>> &v) {
    long long n = 0, k = 0;
    for (auto p : v) {
        n += p.first * p.second;
        k += p.first;
    }
    dfs(n, n, k);
    vector<vector<pair<long long, long long>>> tran;
    for (vector<int> &v : __v) {
        vector<pair<long long, long long>> now;
        for (int i = 0, j; i < (int)v.size(); i = j) {
            for (j = i; j < (int)v.size(); ++j) {
                if (v[i] != v[j]) break;
            }
            now.emplace_back(j - i, v[i]);
        }
        tran.push_back(now);
    }
    for (int i = 0; i < (int)tran.size(); ++i) {
        if (tran[i] == v) {
            if (i == (int)tran.size() - 1) return tran[0];
            return tran[i + 1];
        }
    }
    return tran[0];
}

int main() {
    int l; cin >> l;
    vector<pair<long long, long long>> v; // [cnt, n_i]
    long long N = 0, K = 0;
    for (int i = 0; i < l; ++i) {
        long long cnt, ni; cin >> cnt >> ni;
        v.emplace_back(cnt, ni);
        N += cnt * ni;
        K += cnt;
    }
    // vector<pair<long long, long long>> ans = find_answer(v);
    /* cerr << "ans = " << endl;
    for (auto p : ans) {
        cerr << p.first << " " << p.second << endl;
    } */
    if (l == 1) {
        cout << -1 << endl;
        exit(0);
    }
    if (l == 2 && v[0].second == v[1].second + 1) {
        cout << -1 << endl;
        exit(0);
    }
    long long x;
    if (v[l - 2].second == v[l - 1].second + 1) {
        v.pop_back(); v.pop_back();
        x = v.back().second;
        --v.back().first;
        if (v.back().first == 0) v.pop_back();
    }
    else {
        v.pop_back();
        x = v.back().second;
        --v.back().first;
        if (v.back().first == 0) v.pop_back();
    }
    long long n = 0, k = 0;
    for (auto p : v) {
        n += p.first * p.second;
        k += p.first;
    }
    long long cnt_x_1 = ((N - n) - (K - k)) / (x - 2);
    v.emplace_back(cnt_x_1, x - 1);
    n += cnt_x_1 * (x - 1);
    k += cnt_x_1;
    if (K > k) {
        if (N - n == K - k) {
            v.emplace_back(K - k, 1);
        } else {
            v.emplace_back(1, (N - n) - (K - k) + 1);
            if (K - k - 1) v.emplace_back(K - k - 1, 1);
        }
    }
    cout << v.size() << endl;
    for (auto p : v) {
        cout << p.first << " " << p.second << '\n';
    }
    // assert(v == ans);
}
