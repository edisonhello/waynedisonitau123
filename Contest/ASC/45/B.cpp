#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
const double eps = 1e-9;

pair<double, double> p[maxn];

vector<pair<double, double>> getsegs(int n, double a, double b) {
    vector<pair<double, double>> segs;
    for (int i = 0; i < n - 1; ++i) {
        int j = i + 1;
        if (max(p[i].second, p[j].second) < a || min(p[i].second, p[j].second) > b) continue;
        // printf("%lf %lf %lf %lf\n", a, b, p[i].second, p[j].second);
        double slope = (p[j].second - p[i].second) / (p[j].first - p[i].first);
        // printf("slope: %lf\n", slope);
        if (abs(slope) < 1e-9) {
            segs.emplace_back(p[i].first, p[j].first);
        } else if (slope > 0) {
            double yldist = a - p[i].second, yrdist = b - p[i].second;
//            printf("yldist = %lf, yrdist = %lf\n", yldist, yrdist);
            double xldist = yldist / slope, xrdist = yrdist / slope;
            double xl = p[i].first + xldist, xr = p[i].first + xrdist;
//            printf("xl = %lf, xr = %lf\n", xl, xr);
            xl = max(xl, p[i].first), xr = min(xr, p[j].first);
            segs.emplace_back(xl, xr);
        } else {
            double yldist = b - p[i].second, yrdist = a - p[i].second;
 //           printf("yldist = %lf, yrdist = %lf\n", yldist, yrdist);
            double xldist = yldist / slope, xrdist = yrdist / slope;
            double xl = p[i].first + xldist, xr = p[i].first + xrdist;
  //          printf("xl = %lf, xr = %lf\n", xl, xr); 
            xl = max(xl, p[i].first), xr = min(xr, p[j].first);
            segs.emplace_back(xl, xr);
        }
    }
    vector<pair<double, double>> ans;
    for (auto &p : segs) {
        if (ans.empty()) ans.push_back(p);
        else if (p.first - ans.back().second < 1e-10) ans.back().second = p.second;
        else ans.push_back(p);
    }
    return ans;
}

void solve(vector<pair<double, double>> &v, double z) {
    int n = (int)v.size();
    double sum = 0.0;
    double ans = 1e9;
    double zl, zr, l, r;
    double all = 0.0;
    for (int i = 0; i < n; ++i) all += v[i].second - v[i].first;
    deque<int> dq;
    for (int i = 0; i < n; ++i) {
        sum += v[i].second - v[i].first;
        dq.push_back(i);
        while (dq.size() > 1) {
            double ksum = sum - (v[dq[0]].second - v[dq[0]].first);
            if (ksum >= all * z - eps) {
                dq.pop_front();
                sum = ksum;
            } else {
                break;
            }
        }
        if (sum < all * z - eps) continue;
        l = v[dq[0]].first + (sum - all * z), r = v[i].second; 
        if (r - l < ans) {
            ans = r - l;
            zl = l;
            zr = r;
        }
        l = v[dq[0]].first, r = v[i].second - (sum - all * z);
        if (r - l < ans) {
            ans = r - l;
            zl = l;
            zr = r;
        }
    }
    /* sum = 0.0;
    while (dq.size()) dq.pop_front();
    for (int i = n - 1; i >= 0; --i) {
        sum += v[i].second - v[i].first;
        dq.push_back(i);
        while (dq.size() > 1) {
            double ksum = sum - (v[dq[0]].second - v[dq[0]].first);
            if (ksum >= all * z - eps) {
                dq.pop_front();
                sum = ksum;
            } else {
                break;
            }
        }
        if (sum < all * z - eps) continue;
        l = v[dq[0]].first + (sum - all * z), r = v[i].second; 
        if (r - l < ans) {
            ans = r - l;
            zl = l;
            zr = r;
        }
        l = v[dq[0]].first, r = v[i].second - (sum - all * z);
        if (r - l < ans) {
            ans = r - l;
            zl = r;
            zr = r;
        }
    } */
    /* zl = max(0.0, zl);
    double maxr = 0;
    for (int i = 0; i < maxn; ++i) maxr = max(maxr, p[i].first);
    zr = min(maxr, zr); */
    printf("%.20lf %.20lf\n", zl, zr);
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("bayes.in", "r", stdin);
    freopen("bayes.out", "w", stdout);
#endif
    int n; while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        ++n;
        double a, b; scanf("%lf%lf", &a, &b);
        double alpha; scanf("%lf", &alpha);
        for (int i = 0; i < n; ++i) scanf("%lf%lf", &p[i].first, &p[i].second);
        auto segs = getsegs(n, a, b);
        // for (auto &p : segs) printf("%lf, %lf\n", p.first, p.second);
        solve(segs, alpha);
    }
}
