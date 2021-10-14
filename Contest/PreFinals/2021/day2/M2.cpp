
#include <bits/stdc++.h>
using namespace std;

struct P {
  double x, y;
  P() = default;
  P(double x, double y) : x(x), y(y) {}

  bool operator< (const P b) const { return same(x, b.x) ? same(y, b.y) ? 0 : y < b.y : x < b.x; }
};

struct L {
  double a, b, c;
  P pa, pb;
  L() = default;
  L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
};

bool SegmentIntersectStrict(P p1, P p2, P p3, P p4) { // point touch = true
  if (max(p1.x, p2.x) < min(p3.x, p4.x) || max(p3.x, p4.x) < min(p1.x, p2.x)) return false;
  if (max(p1.y, p2.y) < min(p3.y, p4.y) || max(p3.y, p4.y) < min(p1.y, p2.y)) return false;
  return sign((p3 - p1) ^ (p4 - p1)) * sign((p3 - p2) ^ (p4 - p2)) <= 0 && sign((p1 - p3) ^ (p2 - p3)) * sign((p1 - p4) ^ (p2 - p4)) <= 0;
}

bool SegmentIntersect(P p1, P p2, P p3, P p4) { // point touch = false
  if (max(p1.x, p2.x) <= min(p3.x, p4.x) || max(p3.x, p4.x) <= min(p1.x, p2.x)) return false;
  if (max(p1.y, p2.y) <= min(p3.y, p4.y) || max(p3.y, p4.y) <= min(p1.y, p2.y)) return false;
  return sign((p3 - p1) ^ (p4 - p1)) * sign((p3 - p2) ^ (p4 - p2)) < 0 && sign((p1 - p3) ^ (p2 - p3)) * sign((p1 - p4) ^ (p2 - p4)) < 0;
}

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<P>> poly(N);
  vector<P> but(N);
  for (int i = 0; i < N; ++i) {
    int P;
    cin >> P;
    poly[i].resize(P);
    for (int j = 0; j < P; ++j) {
      cin >> poly[i][j].x >> poly[i][j].y;
    }
    cin >> but[i].x >> but[i].y;
  }
  vector<vector<double>> dist(N, vector<double>(N, 1E18));

  auto get_dist = [&] (int i, P &ip) {
    map<P, int> pid;
    auto get_id = [&] (const P p) {
      auto it = pid.find(p);
      if (it != pid.end()) return it->second;
      int z = pid.size();
      return pid[p] = z;
    };

    for (auto &p : poly[i]) get_id(p);
    get_id(but[i]);
    get_id(ip);

    int n = pid.size();

    vector<vector<pair<double, int>>> g(n);
    for (auto to : poly[i]) {
      L tol(to, but[i]);
      bool no = 0;
      for (int ii = 0; ii < poly[i].size(); ++ii) {
        int iii = ii == poly[i].size() - 1 ? 0 : ii + 1;
        L l(poly[i][ii], poly[i][iii]);
        if (SegmentIntersectStrict(tol.pa, tol.pb, l.pa, l.pb)) {
          no = 1;
        }
      }
      if (!no) {
        addedge(get_id(to), get_id(but[i]), (to - but[i]).abs());
      }
    }
  };

  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      bool c = false;
      for (int ii = 0; ii < poly[i].size(); ++ii) {
        int iii = ii == poly[i].size() - 1 ? 0 : ii + 1;
        for (int jj = 0; jj < poly[j].size(); ++jj) {
          int jjj = jj == poly[j].size() - 1 ? 0 : jj + 1;
          if (SegmentIntersectStrict(poly[i][ii], poly[i][iii], poly[j][jj], poly[j][jjj])) {
            P ip = Intersect(L(poly[i][ii], poly[i][iii]), L(poly[j][jj], poly[j][jjj]));
            dist[i][j] = min(dist[i][j], get_dist(i, ip) + get_dist(j, ip));
          }
        }
      }
    }
  }

  auto Dist = [&](auto p, auto q) {
    return hypot(p.first - q.first, p.second - q.second);
  };

  vector<int> deg(N);
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      for (int k = 0; k < poly[i].size(); ++k) {
        for (int l = 0; l < poly[j].size(); ++l) {
          if (poly[i][k] == poly[j][l]) {
            dist[i][j] = dist[j][i] = Dist(poly[i][k], but[i]) + Dist(poly[j][l], but[j]);
            deg[i]++;
            deg[j]++;
          }
        }
      }
    }
  }
  double ans = 0.0;
  for (int i = 0; i < N; ++i) dist[i][i] = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      if (dist[i][j] < 1E10) ans += 2 * dist[i][j];
    }
  }
  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    }
  }
  vector<int> odd;
  for (int i = 0; i < N; ++i) {
    if (deg[i] & 1) odd.push_back(i);
  }
  int K = odd.size();
  vector<double> dp(1 << K, 1E18);
  dp[0] = 0;
  for (int s = 1; s < (1 << K); ++s) {
    for (int i = 0; i < K; ++i) {
      if (s >> i & 1) {
        for (int j = i + 1; j < K; ++j) {
          if (s >> j & 1) {
            dp[s] = min(dp[s], dp[s ^ (1 << i) ^ (1 << j)] + dist[odd[i]][odd[j]]);
          }
        }
      }
    }
  }
  cout << fixed << setprecision(20) << ans + dp[(1 << K) - 1] << "\n";
}
