#include <bits/stdc++.h>
using namespace std;

vector<int> SuffixArray(const string& s) {
  int N = s.size();
  vector<int> order(N), rnk(N);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return s[i] < s[j];
  });
  for (int i = 0, r = 0; i < N; ++i) {
    if (i > 0 && s[order[i]] != s[order[i - 1]]) r++;
    rnk[order[i]] = r;
  }
  vector<int> ornk(N);
  for (int k = 1; ; ++k) {
    for (int i = 0; i < N; ++i) {
      ornk[i] = rnk[i];
    }

    auto Get = [&](int x) {
      int a = ornk[x];
      int b = x + (1 << (k - 1)) < N ? ornk[x + (1 << (k - 1))] : -1;
      return make_pair(a, b);
    };

    sort(order.begin(), order.end(), [&](int i, int j) {
      return Get(i) < Get(j);
    });

    int r = 0;
    for (int i = 0; i < N; ++i) {
      if (i > 0 && Get(order[i]) != Get(order[i - 1])) r++;
      rnk[order[i]] = r;
    }

    if (r == N) break;
    if ((1 << k) >= N) break;
  }
  return order;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int k;
    cin >> k;
    string s;
    cin >> s;
    int N = s.size();
    vector<int> sa = SuffixArray(s);

    string ans = "";
    vector<int> rev(N);
    for (int i = 0; i < N; ++i) {
      rev[sa[i]] = i;
    }

    int last = -1;
    int gap = 0;
    for (char c = 'z'; c >= 'a'; c--) {
      while (last + 1 < N && s[last + 1] == c) {
        ans += c;
        last++;
      }
      int cnt = 0, cg = 0;
      int plast = last;
      for (int i = last + 1; i < N; ++i) {
        if (s[i] == c) {
          cnt += (i > last + 1);
          last = i;
          cg++;
        }
      }
      assert(gap <= k);
      if (gap + cnt <= k) {
        for (int i = 0; i < cg; ++i) {
          ans += c;
        }
        gap += cnt;
        if (gap == k) break;
      } else {
        vector<pair<int, int>> group;
        int g = 0;
        last = plast;
        for (int i = last + 1; i < N; ++i) {
          if (s[i] == c) {
            if (i == last + 1) {
              g++;
            } else {
              if (g > 0) {
                group.emplace_back(g, last);
              }
              g = 1;
            }
            last = i;
          }
        }
        if (g > 0) {
          group.emplace_back(g, last);
        }
        assert(!group.empty());
        priority_queue<int, vector<int>, greater<int>> pq;
        int sum = 0;
        vector<tuple<int, int, int>> sfx;
        for (int i = 0; i < group.size(); ++i) {
          while (pq.size() + 1 > k - gap) {
            sum -= pq.top();
            pq.pop();
          }
          int g = group[i].first;
          int p = group[i].second;
          pq.push(g); 
          sum += g;
          sfx.emplace_back(sum, p + 1 < N ? rev[p + 1] : -1, p);
        }
        assert(!sfx.empty());
        int p = max_element(sfx.begin(), sfx.end()) - sfx.begin();
        ans += string(get<0>(sfx[p]), c);
        ans += s.substr(get<2>(sfx[p]) + 1);
        last = N - 1;
        break;
      }
    }
    while (last + 1 < N) {
      ans += s[last + 1];
      last++;
    }
    cout << ans << "\n";
  }
}
