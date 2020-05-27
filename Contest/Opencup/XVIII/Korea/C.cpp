#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<pair<double, double>> br;
    vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        vector<int> a(k);
        for (int j = 0; j < k; ++j) {
            cin >> a[j];
        }
        cnt[i] = k;
        sort(a.begin(), a.end());
        double p = 1.0;
        double ex = 0.0;
        for (int j = 0; j < k; ++j) {
            double x = a[j] / 1000.0;
            double broken = p * (1 - x);
            ex += broken * (j + 1);
            p *= x;
        }
        ex += k * p;
        br.emplace_back(ex, p);
    }
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        return br[i].first / br[i].second < br[j].first / br[j].second;
    });

    double res = 0.0;
    double p = 1.0;
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum += br[ord[i]].first;
        double stop = p * br[ord[i]].second;
        res += (sum) * stop;
        p *= (1 - br[ord[i]].second);
    }
    int tot = accumulate(cnt.begin(), cnt.end(), 0);
    res += sum * p;
    cout << fixed << setprecision(20) << res << "\n";
}

