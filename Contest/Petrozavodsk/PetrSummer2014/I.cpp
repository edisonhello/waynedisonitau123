#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

void check(vector<double> nums, double avg, double std, double mid) {
    int n = nums.size();
    double sum = 0;
    for (double d : nums) sum += d;
    double _avg = sum / n;
    double ssum = 0;
    for (double d : nums) ssum += (d - _avg) * (d - _avg);
    double _std = sqrt(ssum / n);

    // cerr << fixed << setprecision(12);
    // cerr << avg << ' ' << std << ' ' << mid << endl;
    // cerr << _avg << ' ' << _std << ' ' << nums[n / 2] << endl;
    // for (int i = 0; i < n; ++i) cerr << nums[i] << ' ';
    // cerr << endl;

    assert(abs(mid - nums[n / 2]) < eps);
    assert(abs(avg - _avg) < eps);
    assert(abs(std - _std) < eps);

}

void solve() {
    double avg, std, mid; 
    cin >> avg >> std >> mid;
    double sqavg = std * std + avg * avg;

    for (int n = 1; n <= 19; n += 2) {
        double tot = avg * n;
        double sqtot = sqavg * n;
        vector<double> nums(n, mid);
        tot -= mid * n;
        if (tot > 0) {
            double add = tot / (n / 2);
            if (add > eps && n == 1) continue;
            for (int i = n / 2 + 1; i < n; ++i) nums[i] += add;
        } else {
            double sub = -tot / (n / 2);
            if (sub > eps && n == 1) continue;
            for (int i = 0; i < n / 2; ++i) nums[i] -= sub;
        }

        bool fail = false;
        for (int i = 0; i < n; ++i) {
            if (nums[i] < -eps || nums[i] > 100 + eps) fail = true;
        }
        if (fail) continue;

        for (int i = 0; i < n; ++i) sqtot -= nums[i] * nums[i];

        if (sqtot < -eps) continue;
        // sqtot now > 0

        auto pullout = [&] (int i, int j, double movemax) {
            if (movemax < eps) return;
            if (abs(sqtot) < eps) return;

            double osqtot = sqtot + nums[i] * nums[i] + nums[j] * nums[j];
            
            double L = 0, R = movemax;
            int it = 100;

            if (osqtot - (nums[i] - movemax) * (nums[i] - movemax) - (nums[j] + movemax) * (nums[j] + movemax) > 0) {
                L = movemax;
                it = 0;
            }


            while (it--) {
                double M = (L + R) / 2;

                double nsqtot = osqtot - (nums[i] - M) * (nums[i] - M) - (nums[j] + M) * (nums[j] + M);
                if (nsqtot > 0) L = M;
                else R = M;
            }

            nums[i] -= L;
            nums[j] += L;
            sqtot = osqtot - nums[i] * nums[i] - nums[j] * nums[j];
        };

        for (int i = 0; i < n / 2; ++i) {
            for (int j = n / 2 + 1; j < n; ++j) {
                double movemax = min(nums[i], 100 - nums[j]);
                pullout(i, j, movemax);
            }
        }
        for (int i = 0; i < n / 2; ++i) {
            for (int j = i + 1; j < n / 2; ++j) {
                if (nums[i] > nums[j]) swap(nums[i], nums[j]);
                double movemax = min(nums[i], mid - nums[j]);
                pullout(i, j, movemax);
            }
        }
        for (int i = n / 2 + 1; i < n; ++i) {
            // for (int j = n / 2 + 1; j < n; ++j) {
            for (int j = i + 1; j < n; ++j) {
                if (nums[i] > nums[j]) swap(nums[i], nums[j]);
                double movemax = min(nums[i] - mid, 100 - nums[j]);
                pullout(i, j, movemax);
            }
        }

        if (sqtot > eps) continue;

        cout << n;
        cout << fixed << setprecision(12);
        for (double d : nums) cout << ' ' << d;
        cout << '\n';

        // check(nums, avg, std, mid);

        return;
    }
    cout << -1 << '\n';
}

int main() {
    freopen("stats.in", "r", stdin);
    freopen("stats.out", "w", stdout);
    int t; cin >> t; while (t--) {
        solve();
    }
}

