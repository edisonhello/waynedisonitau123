#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    int N;
    cin >> N;
    string s;
    cin >> s;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
      A[i] = (s[i] == '1');
    }
    vector<int> res;
    for (int mask = 0; mask < 4; ++mask) {
      vector<int> B = A;
      vector<int> basis;
      if (mask & 1) {
        B[0] ^= 1;
        B[1] ^= 1;
        B[2] ^= 1;
        basis.push_back(0);
      }
      if (mask & 2) {
        B[1] ^= 1;
        B[2] ^= 1;
        B[3 % N] ^= 1;
        basis.push_back(1);
      }
      for (int i = 2; i < N; ++i) {
        if (B[i] == 0) {
          B[i] ^= 1;
          B[(i + 1) % N] ^= 1;
          B[(i + 2) % N] ^= 1;
          basis.push_back(i);
        }
      }
      if (count(B.begin(), B.end(), 0) == 0) {
        res = basis;
        break;
      }
    }
    if (res.empty()) {
      assert(N % 3 == 0);
      cout << "0\n";
      continue;
    }
    vector<bool> to_flip(N);
    vector<int> need_flip;
    for (int u : res) {
      to_flip[(u + 1) % N] = true;
      need_flip.push_back((u + 1) % N);
      // cerr << (u + 1) % N << " ";
    }
    // cerr << endl;

    sort(need_flip.begin(), need_flip.end());
    vector<int> nxt(N, -1);
    vector<int> prv(N, -1);
    vector<int> gap(N);
    set<pair<int, int>> fg;
    for (int i = 0; i < need_flip.size(); ++i) {
      nxt[need_flip[i]] = need_flip[(i + 1) % need_flip.size()];
      prv[need_flip[i]] = need_flip[(i + need_flip.size() - 1) % need_flip.size()];
      gap[need_flip[i]] = max((nxt[need_flip[i]] - need_flip[i] + N) % N, (need_flip[i] - prv[need_flip[i]] + N) % N);
      fg.emplace(gap[need_flip[i]], need_flip[i]);
    }

    set<int> can_flip;
    for (int i = 0; i < N; ++i) {
      if (to_flip[i] && A[i] == 0) {
        can_flip.insert(i);
      }
    }

    vector<int> ans;

    auto Flip = [&](int p) {
      if (A[p] == 0 && to_flip[p]) {
        can_flip.erase(p);
      }
      A[p] ^= 1;
      if (A[p] == 0 && to_flip[p]) {
        can_flip.insert(p);
      }
    };

    auto DoOp = [&](int p) {
      ans.push_back(p);
      to_flip[p] = false;
      Flip(p);
      Flip((p + 1) % N);
      Flip((p + N - 1) % N);
    };
    auto Recalc = [&](int p) {
      assert(to_flip[p]);
      fg.erase(make_pair(gap[p], p));
      gap[p] = max((nxt[p] - p + N) % N, (p - prv[p] + N) % N);
      fg.emplace(gap[p], p);
    };

    auto Erase = [&](int p) {
      // cerr << "p = " << p << endl;
      assert(to_flip[p]);
      to_flip[p] = false;
      fg.erase(make_pair(gap[p], p));
      can_flip.erase(p);
      if (prv[p] != p) {
        assert(nxt[p] != p);
        nxt[prv[p]] = nxt[p];
        Recalc(prv[p]);
        prv[nxt[p]] = prv[p];
        Recalc(nxt[p]);
      }
    };

    while (!fg.empty()) {
      if (!can_flip.empty()) {
        int p = *can_flip.begin();
        can_flip.erase(p);
        Erase(p);
        DoOp(p);
        // cerr << "case1 p = " << p << endl;
      } else {
        auto [g, p] = *fg.rbegin();
        // cerr << "case2 p = " << p << endl;
        if (g >= 2) {
          assert(prv[p] == (p + N - 1) % N || nxt[p] == (p + 1) % N);
          if (prv[p] == (p + N - 1) % N) {
            assert(nxt[p] == (p + g) % N);
            assert(!to_flip[(p + 1) % N]);
            DoOp((p + 1) % N);
            Erase(p);
            DoOp(p);
            Erase((p + N - 1) % N);
            DoOp((p + N - 1) % N);
            DoOp((p + 1) % N);
          } else {
            assert(prv[p] == (p + N - g) % N);
            assert(!to_flip[(p + N - 1) % N]);
            DoOp((p + N - 1) % N);
            cerr << "hey" << endl;
            Erase(p);
            DoOp(p);
            cerr << "hey" << endl;
            Erase((p + 1) % N);
            DoOp((p + 1) % N);
            DoOp((p + N - 1) % N);
          }
        } else {
          assert(count(A.begin(), A.end(), 0) == 0);
          break;
        }
      }
    }
    cout << ans.size() << "\n";
    assert(count(A.begin(), A.end(), 0) == 0);
    assert(ans.size() <= 2 * N);
    for (int i = 0; i < ans.size(); ++i) {
      cout << ans[i] + 1 << " \n"[i + 1 == ans.size()];
    }
  }
}


// ^[[Aguest-9uhbsd@ta204-BM1AF-BP1AF-BM6AF:~$ ./a.out < L.in
// 13
// 5 1 2 2 3 4 1 2 3 1 5 4 1
// 0
// guest-9uhbsd@ta204-BM1AF-BP1AF-BM6AF:~$ 


