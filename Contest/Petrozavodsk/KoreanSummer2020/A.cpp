#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

ostream& operator<<(ostream& os, __int128 v) {
  if (v == 0) {
    return os << "0";
  }
  int buf[32], ptr = 0;
  while (v > 0) {
    buf[ptr++] = v % 10;
    v /= 10;
  }
  while (ptr > 0) os << buf[--ptr];
  return os;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  string M, S;
  cin >> M >> S;
  int cnt = count(S.begin(), S.end(), '$');
  assert(cnt >= 1);
  if (cnt == 1) {
    int pos = S.find('$');
    assert(pos != string::npos);
    string prefix = S.substr(0, pos);
    string suffix = S.substr(pos + 1);
    int K, Q;
    cin >> K >> Q;
    while (Q--) {
      int64_t a, b;
      cin >> a >> b;
      a--;
      b--;
      if (a < K * prefix.size()) {
        if (b < K * prefix.size()) {
          for (int64_t i = a; i <= b; ++i) cout << prefix[i % prefix.size()];
          cout << "\n";
        } else {
          for (int64_t i = a; i < K * prefix.size(); ++i) cout << prefix[i % prefix.size()];
          int64_t left = b - a + 1 - (K * prefix.size() - a);
          for (int64_t i = 0; left > 0 && i < M.size(); ++i) {
            cout << M[i];
            left--;
          }
          for (int64_t i = 0; left > 0; ++i) {
            cout << suffix[i % suffix.size()];
            left--;
          }
          cout << "\n";
        }
      } else if (a < K * prefix.size() + M.size()) {
        int64_t left = b - a + 1;
        for (int64_t i = a - K * prefix.size(); left > 0 && i < M.size(); ++i) {
          cout << M[i];
          left--;
        }
        for (int64_t i = 0; left > 0; ++i) {
          cout << suffix[i % suffix.size()];
          left--;
        }
        cout << "\n";
      } else {
        int64_t left = b - a + 1;
        for (int64_t i = a - K * prefix.size() - M.size(); left > 0; ++i) {
          cout << suffix[i % suffix.size()];
          left--;
        }
        cout << "\n";
      }
    }
  } else {
    int K, Q;
    cin >> K >> Q;
    vector<__int128> Ls = {M.size()};
    constexpr int64_t kInf = 1'000'000'000'000'000'000;
    while (Ls.back() <= kInf && Ls.size() <= K) {
      __int128 t = Ls.back() * cnt + S.size() - cnt;
      Ls.push_back(t);
    }

    // cerr << "Ls: ";
    // for (auto L : Ls) cerr << L << " ";
    // cerr << endl;

    vector<int> sep;
    for (int i = 0; i < S.size(); ++i) {
      if (S[i] == '$') sep.push_back(i);
    }

    auto GetLength = [&](int K, int p) -> __int128 {
      return (p + 1) * Ls[K - 1] + (sep[p] + 1) - (p + 1);
    };

    function<void(int, int64_t, int64_t)> Print = [&](int K, int64_t L, int64_t R) {
      if (K == 0) {
        assert(L < M.size() && R < M.size());
        cout << M.substr(L, R - L + 1);
        return;
      }
      int pos = -1;
      for (int d = 20; d >= 0; --d) {
        if (pos + (1 << d) < sep.size()) {
          if (L >= GetLength(K, pos + (1 << d))) pos += (1 << d);
        }
      }
      pos++;
      if (pos == sep.size()) {
        int64_t pl = GetLength(K, pos - 1);
        int64_t len = R - L + 1;
        L -= pl;
        cout << S.substr(sep.back() + 1 + L, len);
        return;
      }
      int64_t p = L, pl = (pos > 0 ? GetLength(K, pos - 1) : 0);
      int gap = pos > 0 ? sep[pos] - sep[pos - 1] - 1 : sep[pos];
      int sp = pos > 0 ? sep[pos - 1] + 1 : 0;
      p -= pl; 
      int64_t left = R - L + 1;
      if (p < gap) {
        for (int i = sp + p; left > 0 && i < sep[pos]; ++i) {
          cout << S[i];
          left--;
        }
        if (left > 0) {
          __int128 t = min(__int128(left), Ls[K - 1]);
          Print(K - 1, 0, t - 1);
          left -= t;
        }
      } else {
        p -= gap;
        __int128 t = min(__int128(p + left), Ls[K - 1]);
        Print(K - 1, p, t - 1);
        left -= t - p;
      }
      while (left > 0) {
        int nxt = pos + 1 < sep.size() ? sep[pos + 1] : S.size();
        for (int i = sep[pos] + 1; left > 0 && i < nxt; ++i) {
          cout << S[i];
          left--;
        }
        if (left > 0) {
          __int128 t = min(__int128(left), Ls[K - 1]);
          Print(K - 1, 0, t - 1);
          left -= t;
        }
        pos++;
      }
    };

    string prefix = S.substr(0, sep[0]);

    while (Q--) {
      int64_t a, b;
      cin >> a >> b;
      a--;
      b--;
      if (K >= Ls.size()) {
        int diff = K - (Ls.size() - 1);
        int64_t left = b - a + 1;
        if (a < 1LL * sep[0] * diff) {
          for (int64_t i = a; left > 0; ++i) {
            cout << prefix[i % prefix.size()]; 
            left--;
          }
          a = 0;
        } else {
          a -= 1LL * sep[0] * diff;
        }
        if (left > 0) {
          Print(Ls.size() - 1, a, a + left - 1);
        }
        cout << "\n";
      } else {
        Print(min(int(Ls.size()) - 1, K), a, b);
        cout << "\n";
      }
    }
  }
}
