#include <bits/stdc++.h>
#define end jizz
using namespace std;

int par_id[1006];
int start[1006], end[1006];
int head[1006], tail[1006];
long long par_cnt[505][15][15];
long long par_cc[505];
long long cnt[15][15];
long long ccc;

int main() {
    int b, s;
    cin >> b >> s;
    string st;
    vector<string> v;
    v.push_back("R1");
    while (cin >> st) v.push_back(st);
    v.push_back("E");
    int k = 0;
    for (int i = 0; i < v.size(); ++i) {
        if (v[i][0] == 'V') {
            int val = 0;
            for (int j = 1; j < v[i].size(); ++j) val = val * 10 + v[i][j] - '0';
            k = max(k, val);
        }
    }
    int ss = s;

    int cnt_par = 0;
    {
        stack<int> st;
        for (int i = 0; i < (int)v.size(); ++i) {
            if (v[i][0] == 'R') st.push(i);
            else if (v[i][0] == 'E') {
                par_id[st.top()] = cnt_par;
                par_id[i] = cnt_par;
                ++cnt_par;

                end[st.top()] = i;
                start[i] = st.top();

                st.pop();
            }
        }
    }

    auto Solve = [&](int zr) {
        cout << "zr = " << zr << endl;
        memset(cnt, 0, sizeof(cnt));
        memset(par_cnt, 0, sizeof(par_cnt));
        memset(par_cc, 0, sizeof(par_cc));
        auto is_0 = [&] (int x) -> bool { return zr & (1 << (x - 1)); };
        stack<int> st, rep_st, prev_st;
        int cur_par = -1;
        int rep_time = 0;
        int prev = 0;
        cout << "jizz" << endl;
        for (int i = 0; i < (int)v.size(); ++i) {
            cout << "i = " << i << endl;
            if (v[i][0] == 'R') {
                st.push(par_id[i]);
                cur_par = par_id[i];
                rep_time = 0;
                for (int j = 1; j < (int)v[i].size(); ++j) rep_time = rep_time * 10 + v[i][j] - '0';
                rep_st.push(rep_time);
                prev_st.push(prev);
                prev = 0;
            } else if (v[i][0] == 'E') {
                int chpar = cur_par;
                int chrep = rep_time;
                int chprev = prev;
                st.pop();
                rep_st.pop();
                prev_st.pop();
                if (st.empty()) break;
                cur_par = st.top();
                rep_time = rep_st.top();
                prev = prev_st.top();

                if (head[cur_par] == 0) head[cur_par] = head[chpar];
                tail[cur_par] = tail[chpar];

                par_cc[cur_par] += par_cc[chpar] * 1ll * chrep;
                for (int i = 1; i <= 13; ++i) for (int j = 1; j <= 13; ++j) par_cnt[cur_par][i][j] += par_cnt[chpar][i][j] * 1ll * chrep;
                par_cnt[cur_par][tail[chpar]][head[chpar]] += chrep - 1;

                par_cnt[cur_par][prev][head[chpar]]++;
                prev = tail[chpar];
            } else {
                int x = v[i][1] - '0';
                if (v[i].size() > 2u) x = x * 10 + v[i][2] - '0';
                if (!is_0(x)) {
                    if (head[cur_par] == 0) head[cur_par] = x;
                    tail[cur_par] = x;

                    par_cnt[cur_par][prev][x]++;
                    prev = x;
                }
                par_cc[cur_par]++;
            }
        }

        for (int i = 1; i <= 13; ++i) for (int j = 1; j <= 13; ++j) {
            cnt[i][j] = par_cnt[par_id[0]][i][j];
            if (cnt[i][j] == 0) continue;
            cout << i << " " << j << " cnt = " << cnt[i][j] << endl;
        }
        ccc = par_cc[par_id[0]];

        vector<int> id(k + 1, -1);
        vector<int> wh;
        int g = 0;
        for (int i = 0; i < k; ++i) {
            if (zr >> i & 1) continue;
            id[i + 1] = g++;
        }
        vector<vector<int64_t>> cc(g, vector<int64_t>(g));
        for (int i = 1; i <= k; ++i) {
            for (int j = 1; j <= k; ++j) {
                if (id[i] == -1 || id[j] == -1) continue;
                cc[id[i]][id[j]] = cnt[i][j];
            }
        }
        vector<int64_t> cost(1 << g);
        for (int s = 0; s < (1 << g); ++s) {
            for (int i = 0; i < g; ++i) {
                if ((s >> i & 1) == 0) continue;
                for (int j = 0; j < g; ++j) {
                    if ((s >> j & 1) == 0) continue;
                    cost[s] += cc[i][j];
                }
            }
        }
        vector<int64_t> dp(1 << g);
        dp[0] = 0;
        for (int s = 1; s < (1 << g); ++s) {
            if (__builtin_popcount(s) <= ss) {
                dp[s] = cost[s];
                continue;
            }
            dp[s] = -1'000'000'000'000;
            for (int sub = s - 1; sub > 0; sub = (sub - 1) & s) {
                if (__builtin_popcount(sub) <= ss) {
                    dp[s] = max(dp[s], dp[s ^ sub] + cost[sub]);
                }
            }
        }
        int64_t sum = 0;
        for (int  i = 0; i < g; ++i) {
            for (int j = 0; j < g; ++j) sum += cc[i][j];
        }
        cout << "sum = " << sum << endl;
        cout << dp[(1 << g) - 1] << endl;
        cout << "ccc = " << ccc << endl;
        int64_t res = ccc + sum - dp[(1 << g) - 1];
        if (zr != (1 << k) - 1) res++;
        cout << "res = " << res << endl;
        return res;
    };

    int64_t res = 1'000'000'000'000;
    ss = min(ss, k);
    for (int z = 0; z < (1 << k); ++z) {
        if (__builtin_popcount(z) != ss) continue;
        res = min(res, Solve(z));
    }
    cout << res << endl;
}
