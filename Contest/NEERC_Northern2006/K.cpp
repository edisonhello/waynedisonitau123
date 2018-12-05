#include <bits/stdc++.h>
using namespace std;

const int mod1 = 998244353;
const int pr1 = 131;
const int mod2 = 1e9 + 123;
const int pr2 = 87;

map<pair<int, int>, int> len;
map<pair<int, int>, vector<pair<int, int>>> to;
map<pair<int, int>, string> rev;

pair<int, int> hash_t(const string &s) {
    int h1 = 0, h2 = 0;
    for (int i = 0; i < (int)s.size(); ++i) h1 = (h1 * 1ll * pr1 + s[i]) % mod1;
    for (int i = 0; i < (int)s.size(); ++i) h2 = (h2 * 1ll * pr2 + s[i]) % mod2;
    return make_pair(h1, h2);
}

void blank() {
    string _;
    getline(cin, _);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int w, l, n; cin >> w >> l >> n;
    blank();
    for (int i = 0; i < n; ++i) {
        string s; getline(cin, s);
        vector<string> v;
        stringstream ss(s);
        while (ss >> s) v.push_back(s);
        auto h = hash_t(v[0]);
        rev[h] = v[0];
        len[h] = (int)v[0].size();
        for (int j = 1; j < (int)v.size(); ++j) {
            // cout << "i = " << i << " " << v[j] << endl;
            auto z = hash_t(v[j]);
            len[z] = (int)v[j].size();
            to[h].push_back(z);
            rev[z] = v[j];
        }
    }
    vector<pair<int, int>> v;
    string s;
    int sum = 0;
    len[make_pair(-1, -1)] = 0;
    while (getline(cin, s)) {
        // cout << "s = " << s << endl;
        stringstream ss(s);
        while (ss >> s) {
            auto h = hash_t(s);
            sum += (int)s.size();
            v.push_back(h);
            rev[h] = s;
            len[h] = (int)s.size();
        }
        v.emplace_back(-1, -1);
    }
    len[make_pair(-1, -1)] = 0;
    while (sum < l) {
        vector<pair<int, int>> nxt;
        int nsum = 0;
        for (int i = 0; i < (int)v.size(); ++i) {
            if (to.find(v[i]) == to.end()) {
                nxt.push_back(v[i]);
                assert(len.find(v[i]) != len.end());
                // assert(len[v[i]] != 1);
                nsum += len[v[i]];
                continue;
            }
            for (int j = 0; j < (int)to[v[i]].size(); ++j) {
                nxt.push_back(to[v[i]][j]);
                assert(len.find(to[v[i]][j]) != len.end());
                // assert(len[to[v[i]][j]] != 1);
                nsum += len[to[v[i]][j]];
            }
        }
        if (v == nxt) break;
        sum = nsum;
        v = nxt;
        // for (int i : v) cout << rev[i] << ' '; cout << endl;
    }
    len[make_pair(-1, -1)] = 0;
    if (sum < l) {
        cout << "No result" << endl;
        return 0;
    }
    int cur = 0;
    bool need = false;
    for (int i = 0; i < (int)v.size(); ++i) {
        if (v[i].first == -1) {
            cout << endl;
            cur = 0;
            need = false;
            continue;
        }
        string s = rev[v[i]];
        int tg = cur + (int)s.size();
        if (need) ++tg;
        if (tg > w) {
            cout << endl;
            cout << s;
            cur = s.size();
            need = true;
        } else {
            if (need) cout << ' ';
            cout << s;
            cur += s.size();
            if (need) cur++;
            need = true;
        }
    }
    cout << endl;
}
