#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    vector<int> s(N);
    for (int i = 0; i < N; ++i) {
      cin >> s[i];
      s[i]--;
    }
    int M;
    cin >> M;
    vector<int> t(M);
    for (int i = 0; i < M; ++i) {
      cin >> t[i];
      t[i]--;
    }
    int K;
    cin >> K;
    if (N != M) {
      cout << "NIE\n";
      continue;
    }
    bool bad = false;
    int parity = -1;

    auto Parity = [&](vector<int> vec) {
      int N = vec.size();
      vector<int> fw(N + 1);

      auto Update = [&](int p, int v) {
        for (int i = p + 1; i <= N; i += i & -i) {
          fw[i] += v;
        }
      };

      auto Query = [&](int p) {
        int res = 0;
        for (int i = p + 1; i > 0; i -= i & -i) {
          res += fw[i];
        }
        return res;
      };

      int64_t inv = 0;
      reverse(vec.begin(), vec.end());
      for (int u : vec) {
        inv += Query(u);
        Update(u, 1);
      }
      return inv % 2;
    };

    for (int r = 0; r < K; ++r) {
      map<int, int> ms, mt;
      for (int i = r; i < N; i += K) {
        ms[s[i]]++;
        mt[t[i]]++;
      }
      if (ms != mt) {
        bad = true;
        break;
      }
      bool good = false;
      for (auto iter : ms) {
        if (iter.second > 1) {
          good = true;
          break;
        }
      }
      if (good) {
        continue;
      }
      map<int, int> where;
      for (int i = r; i < N; i += K) {
        where[s[i]] = i;
      }
      vector<int> perm;
      for (int i = r; i < N; i += K) {
        assert(where.find(t[i]) != where.end());
        int p = where[t[i]];
        perm.push_back(p / K);
      }
      int g = Parity(perm);
      if (parity == -1) {
        parity = g;
      } else if (parity != g) {
        bad = true;
        break;
      }
    }
    if (bad) {
      cout << "NIE\n";
    } else {
      cout << "TAK\n";
    }
  }
}

