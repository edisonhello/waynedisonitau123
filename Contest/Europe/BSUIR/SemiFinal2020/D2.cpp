#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

template <size_t P>
struct Decimal {
  template <class T>
  static constexpr T TEN(size_t k) {
    if (k == 0) return 1;
    return TEN<T>(k - 1) * 10;
  }

  static constexpr int64_t kM = TEN<int64_t>(P);

  vector<int64_t> dig;

  constexpr Decimal() : dig(1, 0) {}
  Decimal(const vector<int64_t> &d) : dig(d) {}

  template <class T, typename = typename enable_if<is_integral<T>::value>::type>
  Decimal(T x) {
    while (x > 0) {
      dig.push_back(x % kM);
      x /= kM;
    }
    if (dig.empty()) dig.push_back(0);
  }

  Decimal(string s) {
    reverse(s.begin(), s.end());
    for (size_t i = 0; i < s.size(); i += P) {
      dig.push_back(0);
      for (size_t j = min(s.size(), i + P); j != i; j--) {
        dig.back() = dig.back() * 10 + s[j - 1] - '0';
      }
    }
  }

  size_t size() const { return dig.size(); }

  Decimal operator+(const Decimal &rhs) const {
    Decimal res;
    res.dig.resize(max(size(), rhs.size()));
    int64_t carry = 0;
    for (size_t i = 0; i < res.size(); ++i) {
      int64_t x = i < size() ? dig[i] : 0;
      int64_t y = i < rhs.size() ? rhs.dig[i] : 0;
      res.dig[i] = (x + y + carry) % kM;
      carry = (x + y + carry) / kM;
    }
    if (carry > 0) res.dig.push_back(carry);
    return res;
  }

  Decimal operator-(const Decimal &rhs) const {
    Decimal res(dig);
    for (size_t i = 0; i < size(); ++i) {
      int64_t y = i < rhs.size() ? rhs.dig[i] : 0;
      if (res.dig[i] < y) {
        for (size_t j = i + 1; j < size(); ++j) {
          if (res.dig[j] > 0) {
            res.dig[i] += kM;
            res.dig[j]--;
            break;
          }
        }
      }
      res.dig[i] -= y;
    }
    while (res.size() > 1 && res.dig.back() == 0) res.dig.pop_back();
    return res;
  }

  Decimal operator-=(const Decimal &rhs) {
    for (size_t i = 0; i < size(); ++i) {
      int64_t y = i < rhs.size() ? rhs.dig[i] : 0;
      if (dig[i] < y) {
        for (size_t j = i + 1; j < size(); ++j) {
          if (dig[j] > 0) {
            dig[i] += kM;
            dig[j]--;
            break;
          }
        }
      }
      dig[i] -= y;
    }
    while (size() > 1 && dig.back() == 0) dig.pop_back();
    return *this;
  }

  bool operator==(const Decimal &rhs) const { return dig == rhs.dig; }
  bool operator<(const Decimal &rhs) const {
    if (size() == rhs.size()) {
      for (size_t i = size(); i != 0; i--) {
        if (dig[i - 1] != rhs.dig[i - 1]) return dig[i - 1] < rhs.dig[i - 1];
      }
      return false;
    }
    return size() < rhs.size();
  }
  bool operator>(const Decimal &rhs) const {
    if (size() == rhs.size()) {
      for (size_t i = size(); i != 0; i--) {
        if (dig[i - 1] != rhs.dig[i - 1]) return dig[i - 1] > rhs.dig[i - 1];
      }
      return false;
    }
    return size() > rhs.size();
  }
  bool operator<=(const Decimal &rhs) const {
    return operator<(rhs) || operator==(rhs);
  }
  bool operator>=(const Decimal &rhs) const {
    return operator>(rhs) || operator==(rhs);
  }

  friend istream &operator>>(istream &is, Decimal<P> &d) {
    string s;
    is >> s;
    d = Decimal(s);
    return is;
  }
};

using Vector = bitset<1000>;
using Int = Decimal<18>;

int main() {
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
  vector<Int> pw(n, 1);
  for (int i = 1; i < n; ++i) pw[i] = pw[i - 1] + pw[i - 1];
	vector<Vector> v(n);
	Vector v0;

  auto Parse = [&](Int d) {
    Vector vec;
    for (int i = n - 1; i >= 0; --i) {
      if (d >= pw[i]) {
        d -= pw[i];
        vec[i] = true;
      }
    }
    return vec;
  };

	for (int i = 0; i <= n; ++i) {
    Int d;
    cin >> d;
    if (i == 0) v0 = Parse(d);
    else v[i - 1] = Parse(d);
	}
	vector<Vector> adj(n);
	vector<Vector> w = v;
	for (int i = 0; i < n; ++i) {
		adj[i].set(i);
	}
	for (int i = 0; i < n; ++i) {
		int p = -1;
		for (int j = i; j < n; ++j) {
			if (v[j][i]) {
				p = j;
				break;
			}
		}
    if (p == -1) continue;
		swap(v[i], v[p]);
		swap(adj[i], adj[p]);
		for (int j = 0; j < n; ++j) {
			if (i == j) continue;
			if (v[j][i]) {
				v[j] ^= v[i];
				adj[j] ^= adj[i];
			}
		}
	}

  vector<Vector> inv(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      inv[i][j] = adj[j][i];
    }
  }

	auto Solve = [&](const vector<Vector> &inv, const Vector &v) {
		vector<int> res = {0};
		for (int i = 0; i < n; ++i) {
			if ((inv[i] & v).count() & 1) res.push_back(i + 1);
		}
		cout << res.size() << "\n";
		int enc = res.size();
		for (int u : res) {
			cout << u << " ";
			enc ^= u;
		}
		cout << "\n";
		return enc;
	};

	int enc = Solve(inv, v0);
	while (m--) {
    Int x;
		int t;
		cin >> t >> x;
    t ^= enc;
    if (t == 0) {
      v0 = Parse(x);
    } else {
      t--;
      assert(t < n);
      Vector nv = Parse(x);
      Vector u = nv ^ w[t];
      w[t] = nv;
      Vector y;
      for (int i = 0; i < n; ++i) {
        y[i] = (inv[i] & u).count() & 1;
      }
      u = y;
      Vector v;
      for (int i = 0; i < n; ++i) {
        v[i] = inv[t][i];
      }
      for (int i = 0; i < n; ++i) {
        if (u[i]) {
          inv[i] ^= v;
        }
      }
    }
    enc = Solve(inv, v0);
	}
	return 0;
}

