namespace delaunay {
// Not equal to any other points.
const Point kA(inf, inf);
bool InCircle(Point p, Point a, Point b, Point c) {
  a = a - p;
  b = b - p;
  c = c - p;
  __int128 x = __int128(a.Norm()) * (b ^ c) + __int128(b.Norm()) * (c ^ a) +
    __int128(c.Norm()) * (a ^ b);
  return x * Sign((b - a) ^ (c - a)) > 0;
}
struct Quad {
  bool mark;
  Quad *o, *rot;
  Point p;
  Quad(Point p) : mark(false), o(nullptr), rot(nullptr), p(p) {}
  Point F() { return r()->p; }
  Quad* r() { return rot->rot; }
  Quad* prev() { return rot->o->rot; }
  Quad* next() { return r()->prev(); }
};
Quad* MakeEdge(Point orig, Point dest) {
  Quad* q[4] = {new Quad(orig), new Quad(kA), new Quad(dest), new Quad(kA)};
  for (int i = 0; i < 4; ++i) {
    q[i]->o = q[-i & 3];
    q[i]->rot = q[(i + 1) & 3];
  }
  return q[0];
}
void Splice(Quad* a, Quad* b) {
  swap(a->o->rot->o, b->o->rot->o);
  swap(a->o, b->o);
}
Quad* Connect(Quad* a, Quad* b) {
  Quad* q = MakeEdge(a->F(), b->p);
  Splice(q, a->next());
  Splice(q->r(), b);
  return q;
}
pair<Quad*, Quad*> Dfs(const vector<Point>& s, int l, int r) {
  if (r - l <= 3) {
    Quad *a = MakeEdge(s[l], s[l + 1]), *b = MakeEdge(s[l + 1], s[r - 1]);
    if (r - l == 2) return {a, a->r()};
    Splice(a->r(), b);
    auto side = (s[l + 1] - s[l]) ^ (s[l + 2] - s[l]);
    Quad* c = side ? Connect(b, a) : nullptr;
    return make_pair(side < 0 ? c->r() : a, side < 0 ? c : b->r());
  }
  int m = (l + r) >> 1;
  auto [ra, a] = Dfs(s, l, m);
  auto [b, rb] = Dfs(s, m, r);
  while (((a->F() - b->p) ^ (a->p - b->p)) < 0 && (a = a->next()) ||
      ((b->F() - a->p) ^ (b->p - a->p)) > 0 && (b = b->r()->o));
  Quad* base = Connect(b->r(), a);
  auto Valid = [&](Quad* e) {
    return ((base->F() - e->F()) ^ (base->p - e->F())) > 0;
  };
  if (a->p == ra->p) ra = base->r();
  if (b->p == rb->p) rb = base;
  while (true) {
    Quad* lc = base->r()->o;
    if (Valid(lc)) {
      while (InCircle(lc->o->F(), base->F(), base->p, lc->F())) {
        Quad* t = lc->o;
        Splice(lc, lc->prev());
        Splice(lc->r(), lc->r()->prev());
        lc = t;
      }
    }
    Quad* rc = base->prev();
    if (Valid(rc)) {
      while (InCircle(rc->prev()->F(), base->F(), base->p, rc->F())) {
        Quad* t = rc->prev();
        Splice(rc, rc->prev());
        Splice(rc->r(), rc->r()->prev());
        rc = t;
      }
    }
    if (!Valid(lc) && !Valid(rc)) break;
    if (!Valid(lc) || (Valid(rc) && InCircle(rc->F(), rc->p, lc->F(), lc->p))) {
      base = Connect(rc, base->r());
    } else {
      base = Connect(base->r(), lc->r());
    }
  }
  return make_pair(ra, rb);
}
vector<array<Point, 3>> Triangulate(vector<Point> pts) {
  sort(pts.begin(), pts.end());
  if (pts.size() < 2) return {};
  Quad* e = Dfs(pts, 0, pts.size()).first;
  vector<Quad*> q = {e};
  while (((e->F() - e->o->F()) ^ (e->p - e->o->F())) < 0) e = e->o;
  auto Add = [&]() {
    Quad* c = e;
    do {
      c->mark = true;
      pts.push_back(c->p);
      q.push_back(c->r());
      c = c->next();
    } while (c != e);
  };
  Add();
  pts.clear();
  int ptr = 0;
  while (ptr < q.size()) {
    if (!(e = q[ptr++])->mark) Add();
  }
  vector<array<Point, 3>> res(pts.size() / 3);
  for (int i = 0; i < pts.size(); ++i) res[i / 3][i % 3] = pts[i];
  return res;
}
}  // namespace delaunay
