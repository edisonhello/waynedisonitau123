#include <bits/stdc++.h>
using namespace std;

const int maxn = 100006;
int mu[maxn], pi[maxn];
vector<int> prime;

void init() {
    mu[1] = pi[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (!pi[i]) {
            pi[i] = i;
            prime.push_back(i);
            mu[i] = -1;
        }
        for (int j = 0; i * prime[j] < maxn; ++j) {
            pi[i * prime[j]] = prime[j];
            mu[i * prime[j]] = -mu[i];
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}

int main() {
    init();

    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        vector<vector<int>> anss;
        for (int i = 1; i <= n; ++i) if (n % i == 0) {
            vector<int> ans = {1};
            vector<int> uu, dd;
            vector<int> facs;
            for (int j = 1; j * j <= i; ++j) {
                if (i % j == 0) {
                    facs.push_back(j);
                    if (i / j != j) facs.push_back(i / j);
                }
            }
            for (int j : facs) {
                // cerr << "fac " << j << " mu " << mu[n / j] << endl;
                if (mu[i / j] == 1) uu.push_back(j);
                else if (mu[i / j] == -1) dd.push_back(j);
            }
            // cerr << "uu: "; for (int j : uu) cerr << j << ' '; cerr << endl;
            // cerr << "dd: "; for (int j : dd) cerr << j << ' '; cerr << endl;
            for (int j : uu) {
                vector<int> vv;
                for (int i = 0; i < (int)ans.size(); ++i) {
                    if (ans[i] != 0) {
                        while ((int)vv.size() < i + j + 1) vv.push_back(0);
                        vv[i] -= ans[i];
                        vv[i + j] += ans[i];
                    }
                }
                ans.swap(vv);
            }
            for (int j : dd) {
                vector<int> vv(ans.size() - j, 0);
                for (int i = (int)ans.size() - 1; i >= 0; --i) {
                    if (ans[i] != 0) {
                        assert(i - j >= 0);
                        vv[i - j] = ans[i];
                        ans[i - j] += ans[i];
                    }
                }
                ans.swap(vv);
            }
            anss.push_back(ans);
        }
        sort(anss.begin(), anss.end(), [] (const vector<int> &a, const vector<int> &b) {
            if (a.size() != b.size()) return a.size() < b.size();
            for (int i = a.size() - 1; i >= 0; --i) if (a[i] != b[i]) return a[i] < b[i];
            return false;
        });
        for (auto &ans : anss) {
            string s = "(";
            bool first = true;
            for (int j = (int)ans.size() - 1; j >= 0; --j) {
                if (ans[j] == 0) continue;
                if (!first) {
                    if (ans[j] > 0) s += "+";
                    else s += "-";
                }
                first = false;
                if (abs(ans[j]) != 1) s += to_string(abs(ans[j]));
                if (j == 0) {
                    if (abs(ans[j]) == 1) s += "1";
                } else if (j == 1) {
                    s += "x";
                } else {
                    s += "x^" + to_string(j);
                }
            }
            s += ")";
            cout << s;
        }
        cout << endl;
    }
}

