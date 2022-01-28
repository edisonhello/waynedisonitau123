#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int K, N, Q;
  cin >> K >> N >> Q;
  vector<vector<int>> A(K, vector<int>(N));
  for (int i = 0; i < K; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> A[i][j];
    }
  }

  const int KK = K;

  constexpr int64_t kInf = 1'000'000'000'000'000'000;

  struct Tag {
    enum Type {
      kNone,
      kAdd,
      kSet
    };

    Type type;
    int64_t value;

    Tag() : type(kNone) {}
  };

  struct Node {
    vector<int64_t> sum;
    vector<Tag> tag;
    int left;
    int right;

    Node(int KK) : sum(1 << KK), tag(KK), left(-1), right(-1) {}
  };

  vector<Node> nodes;

  auto NewNode = [&](int z = -1) {
    if (z == -1) {
      nodes.emplace_back(KK);
    } else {
      nodes.push_back(nodes[z]);
    }
    return nodes.size() - 1;
  };

  auto Pull = [&](Node& nd) {
    for (int s = 0; s < (1 << KK); ++s) {
      nd.sum[s] = min(nodes[nd.left].sum[s], nodes[nd.right].sum[s]);
    }
  };

  auto Build = [&]() {
    auto dfs = [&](auto dfs, int l, int r) -> int {
      int o = NewNode();
      if (r - l == 1) {
        for (int s = 0; s < (1 << KK); ++s) {
          for (int i = 0; i < KK; ++i) {
            if (s >> i & 1) {
              nodes[o].sum[s] += A[i][l];
            }
          }
        }
        return o;
      }
      int m = (l + r) >> 1;
      nodes[o].left = dfs(dfs, l, m);
      nodes[o].right = dfs(dfs, m, r);
      Pull(nodes[o]);
      return o;
    };

    return dfs(dfs, 0, N);
  };

  auto ApplyAddTag = [&](Node& nd, int p, int64_t x) {
    if (nd.tag[p].type == Tag::Type::kNone) {
      nd.tag[p].type = Tag::Type::kAdd;
      nd.tag[p].value = x;
    } else if (nd.tag[p].type == Tag::Type::kAdd) {
      nd.tag[p].value += x;
    } else {
      nd.tag[p].value += x;
    }
    for (int s = 0; s < (1 << KK); ++s) {
      if (s >> p & 1) {
        nd.sum[s] += x;
      }
    }
  };

  auto ApplySetTag = [&](Node& nd, int p, int64_t x) {
    nd.tag[p].type = Tag::Type::kSet;
    nd.tag[p].value = x;
    for (int s = 0; s < (1 << KK); ++s) {
      if (s >> p & 1) {
        nd.sum[s] = nd.sum[s ^ (1 << p)] + x;
      }
    }
  };

  auto Push = [&](int g) {
    int x = NewNode(nodes[g].left);
    int y = NewNode(nodes[g].right);
    nodes[g].left = x;
    nodes[g].right = y;
    for (int p = 0; p < KK; ++p) {
      if (nodes[g].tag[p].type == Tag::Type::kAdd) {
        ApplyAddTag(nodes[x], p, nodes[g].tag[p].value);
        ApplyAddTag(nodes[y], p, nodes[g].tag[p].value);
      } else if (nodes[g].tag[p].type == Tag::Type::kSet) {
        ApplySetTag(nodes[x], p, nodes[g].tag[p].value);
        ApplySetTag(nodes[y], p, nodes[g].tag[p].value);
      }
      nodes[g].tag[p].type = Tag::Type::kNone;
    }
  };

  auto Query = [&](int z, int ql, int qr) {
    auto dfs = [&](auto dfs, int l, int r, int o) -> pair<int64_t, int> {
      int z = NewNode(o);
      if (l >= qr || ql >= r) {
        return {kInf, z};
      }
      if (l >= ql && r <= qr) {
        return {nodes[z].sum[(1 << KK) - 1], z};
      }
      int m = (l + r) >> 1;
      Push(z);
      auto [lq, lz] = dfs(dfs, l, m, nodes[z].left);
      auto [rq, rz] = dfs(dfs, m, r, nodes[z].right);
      nodes[z].left = lz;
      nodes[z].right = rz;
      return {min(lq, rq), z};
    };

    return dfs(dfs, 0, N, z);
  };

  auto Add = [&](int z, int ql, int qr, int p, int x) {
    auto dfs = [&](auto dfs, int l, int r, int o) -> int {
      int z = NewNode(o);
      if (l >= ql && r <= qr) {
        ApplyAddTag(nodes[z], p, x);
        return z;
      }
      int m = (l + r) >> 1;
      Push(z);
      if (qr <= m) {
        nodes[z].left = dfs(dfs, l, m, nodes[z].left);
      } else if (ql >= m) {
        nodes[z].right = dfs(dfs, m, r, nodes[z].right);
      } else {
        nodes[z].left = dfs(dfs, l, m, nodes[z].left);
        nodes[z].right = dfs(dfs, m, r, nodes[z].right);
      }
      Pull(nodes[z]);
      return z;
    };

    return dfs(dfs, 0, N, z);
  };

  auto Set = [&](int z, int ql, int qr, int p, int x) {
    // cerr << "Set z = " << z << " ql = " << ql << " qr = " << qr << " p = " << p << " x = " << x << endl;
    auto dfs = [&](auto dfs, int l, int r, int o) -> int {
      int z = NewNode(o);
      if (l >= ql && r <= qr) {
        ApplySetTag(nodes[z], p, x);
        return z;
      }
      int m = (l + r) >> 1;
      Push(z);
      if (qr <= m) {
        nodes[z].left = dfs(dfs, l, m, nodes[z].left);
      } else if (ql >= m) {
        nodes[z].right = dfs(dfs, m, r, nodes[z].right);
      } else {
        nodes[z].left = dfs(dfs, l, m, nodes[z].left);
        nodes[z].right = dfs(dfs, m, r, nodes[z].right);
      }
      Pull(nodes[z]);
      return z;
    };

    return dfs(dfs, 0, N, z);
  };

  vector<int> roots(Q + 1);
  roots[0] = Build();

  // cerr << "Build" << endl;

  for (int i = 1; i <= Q; ++i) {
    int type, t;
    cin >> type >> t;
    if (type == 1) {
      int p, l, r, x;
      cin >> p >> l >> r >> x;
      p--;
      l--;
      roots[i] = Add(roots[t], l, r, p, x);
    } else if (type == 2) {
      int p, l, r, x;
      cin >> p >> l >> r >> x;
      p--;
      l--;
      roots[i] = Set(roots[t], l, r, p, x);
    } else if (type == 3) {
      int l, r;
      cin >> l >> r;
      l--;
      auto [q, z] = Query(roots[t], l, r);
      roots[i] = z;
      cout << q << "\n";
    }
  }
  return 0;
}

