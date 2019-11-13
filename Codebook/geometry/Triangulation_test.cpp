#include <bits/stdc++.h>
using namespace std;
#define isinf ghjfsije
#define double long double

double eps = 1e-12;
double pi = acos(-1);
bool same(double a, double b) { return abs(a - b) < eps; }

struct P {
    double x, y;
    P() : x(0), y(0) {}
    P(double x, double y) : x(x), y(y) {}
    P operator + (P b) const { return P(x + b.x, y + b.y); }
    P operator - (P b) const { return P(x - b.x, y - b.y); }
    P operator * (double b) const { return P(x * b, y * b); }
    P operator / (double b) const { return P(x / b, y / b); }
    double operator * (P b) const { return x * b.x + y * b.y; }
    double operator ^ (P b) const { return x * b.y - y * b.x; }
    double abs() { return hypot(x, y); }
    P unit() { return *this / abs(); }
    P spin(double o) {
        double c = cos(o), s = sin(o);
        return P(c * x - s * y, s * x + c * y);
    }
    double angle() { return atan2(y, x); }
};

struct L {
    // ax + by + c = 0
    double a, b, c, o;
    P pa, pb;
    L() : a(0), b(0), c(0), o(0), pa(), pb() {}
    L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), o(atan2(-a, b)), pa(pa), pb(pb) {}
    P project(P p) { return pa + (pb - pa).unit() * ((pb - pa) * (p - pa) / (pb - pa).abs()); }
    P reflect(P p) { return p + (project(p) - p) * 2; }
    double get_ratio(P p) { return (p - pa) * (pb - pa) / ((pb - pa).abs() * (pb - pa).abs()); }
};

bool operator < (const P &a, const P &b) {
	return same(a.x, b.x) ? same(a.y, b.y) ? 0 : a.y < b.y : a.x < b.x;
}

P Intersect(L x, L y) { return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a); }

#define sq(x) ((x) * (x))

/* Delaunay Triangulation:
Given a sets of points on 2D plane, find a
triangulation such that no points will strictly
inside circumcircle of any triangle.
find : return a triangle contain given point
add_point : add a point into triangulation
A Triangle is in triangulation iff. its has_chd is 0.
Region of triangle u: iterate each u.edge[i].tri,
each points are u.p[(i+1)%3], u.p[(i+2)%3]
calculation involves O(|V|^6) */
const int N = 100000 + 5;
const double inf = 1e9;
// double eps = 1e-6; // 0 when integer
// return p4 is in circumcircle of tri(p1,p2,p3)
bool in_cc(P& p1, P& p2, P& p3, P& p4){
  double u11 = p1.x - p4.x, u12 = p1.y - p4.y;
  double u21 = p2.x - p4.x, u22 = p2.y - p4.y;
  double u31 = p3.x - p4.x, u32 = p3.y - p4.y;
  double u13 = sq(p1.x)-sq(p4.x)+sq(p1.y)-sq(p4.y);
  double u23 = sq(p2.x)-sq(p4.x)+sq(p2.y)-sq(p4.y);
  double u33 = sq(p3.x)-sq(p4.x)+sq(p3.y)-sq(p4.y);
  double det = -u13*u22*u31 + u12*u23*u31 + u13*u21*u32 -u11*u23*u32 - u12*u21*u33 + u11*u22*u33;
  return det > eps;
}
double side(P& a, P& b, P& p) { return (b - a) ^ (p - a); }
struct Tri;
struct Edge {
  Tri *tri; int side;
  Edge():tri(0), side(0){}
  Edge(Tri *_tri, int _side):tri(_tri), side(_side){}
};
struct Tri {
  P p[3];
  Edge edge[3];
  Tri *chd[3];
  Tri() {}
  Tri(P p0, P p1, P p2) {
    p[0] = p0; p[1] = p1; p[2] = p2;
    chd[0] = chd[1] = chd[2] = 0;
  }
  bool has_chd() { return chd[0] != 0; }
  int num_chd() {
    return chd[0] == 0 ? 0
         : chd[1] == 0 ? 1
         : chd[2] == 0 ? 2 : 3;
  }
  bool contains(P& q) {
    for (int i = 0 ; i < 3 ; ++i)
      if (side(p[i], p[(i + 1) % 3], q) < -eps)
        return false;
    return true;
  }
} pool[N * 10], *tris;
void edge( Edge a, Edge b ){
  if(a.tri) a.tri->edge[a.side] = b;
  if(b.tri) b.tri->edge[b.side] = a;
}
struct Trig { // Triangulation
  Trig(){
    the_root = // Tri should at least contain all points
      new(tris++)Tri(P(-inf,-inf),P(+inf+inf,-inf),P(-inf,+inf+inf));
  }
  Tri *find(P p) { return find(the_root,p); }
  void add_point(P& p) { add_point(find(the_root,p),p); }
  Tri *the_root;
  static Tri *find(Tri *root, P& p) {
    while (true) {
      if (!root->has_chd()) return root;
      for(int i = 0; i < 3 && root->chd[i]; ++i)
        if (root->chd[i]->contains(p)) {
          root = root->chd[i];
          break;
        }
    }
    assert( false ); // "point not found"
  }
  void add_point(Tri *root, P& p) {
    Tri *tab,*tbc,*tca;
    /* split it into three triangles */
    tab=new(tris++) Tri(root->p[0],root->p[1],p);
    tbc=new(tris++) Tri(root->p[1],root->p[2],p);
    tca=new(tris++) Tri(root->p[2],root->p[0],p);
    edge(Edge(tab,0), Edge(tbc,1));
    edge(Edge(tbc,0), Edge(tca,1));
    edge(Edge(tca,0), Edge(tab,1));
    edge(Edge(tab,2), root->edge[2]);
    edge(Edge(tbc,2), root->edge[0]);
    edge(Edge(tca,2), root->edge[1]);
    root->chd[0] = tab;
    root->chd[1] = tbc;
    root->chd[2] = tca;
    flip(tab,2);
    flip(tbc,2);
    flip(tca,2);
  }
  void flip(Tri *tri, int pi) {
    Tri *trj = tri->edge[pi].tri;
    int pj = tri->edge[pi].side;
    if (!trj) return;
    if (!in_cc(tri->p[0], tri->p[1], tri->p[2], trj->p[pj])) return;
    /* flip edge between tri,trj */
    Tri *trk = new(tris++) Tri(tri->p[(pi+1)%3], trj->p[pj], tri->p[pi]);
    Tri *trl = new(tris++) Tri(trj->p[(pj+1)%3], tri->p[pi], trj->p[pj]);
    edge(Edge(trk,0), Edge(trl,0));
    edge(Edge(trk,1), tri->edge[(pi+2)%3]);
    edge(Edge(trk,2), trj->edge[(pj+1)%3]);
    edge(Edge(trl,1), trj->edge[(pj+2)%3]);
    edge(Edge(trl,2), tri->edge[(pi+1)%3]);
    tri->chd[0]=trk; tri->chd[1]=trl; tri->chd[2]=0;
    trj->chd[0]=trk; trj->chd[1]=trl; trj->chd[2]=0;
    flip(trk,1); flip(trk,2);
    flip(trl,1); flip(trl,2);
  }
};
vector<Tri *> triang;
set<Tri *> vst;
void go(Tri *now) {
  if (vst.find(now) != vst.end()) return;
  vst.insert(now);
  if (!now->has_chd()) {
    triang.push_back(now);
    return;
  }
  for (int i = 0; i < now->num_chd(); ++i) go(now->chd[i]);
}
void build(int n, P *ps) {
  tris = pool;
  random_shuffle(ps, ps + n);
  Trig tri;
  for(int i = 0; i < n; ++i) tri.add_point(ps[i]);
  go(tri.the_root);
}

bool jizz(L l1,L l2,L l3){
    P p=Intersect(l2,l3);
    return ((l1.pb-l1.pa)^(p-l1.pa))<-eps;
}

bool cmp(const L &a,const L &b){
    return same(a.o,b.o)?(((b.pb-b.pa)^(a.pb-b.pa))>eps):a.o<b.o;
}

// availble area for L l is (l.pb-l.pa)^(p-l.pa)>0
vector<P> HPI(vector<L> &ls){
    sort(ls.begin(),ls.end(),cmp);
    vector<L> pls(1,ls[0]); 
    for(int i=0;i<(int)ls.size();++i)if(!same(ls[i].o,pls.back().o))pls.push_back(ls[i]);
    deque<int> dq; dq.push_back(0); dq.push_back(1);
#define meow(a,b,c) while(dq.size()>1u && jizz(pls[a],pls[b],pls[c]))
    for(int i=2;i<(int)pls.size();++i){
        meow(i,dq.back(),dq[dq.size()-2])dq.pop_back();
        meow(i,dq[0],dq[1])dq.pop_front();
        dq.push_back(i);
    }
    meow(dq.front(),dq.back(),dq[dq.size()-2])dq.pop_back();
    meow(dq.back(),dq[0],dq[1])dq.pop_front();
    if(dq.size()<3u)return vector<P>(); // no solution or solution is not a convex
    vector<P> rt;
    for(int i=0;i<(int)dq.size();++i)rt.push_back(Intersect(pls[dq[i]],pls[dq[(i+1)%dq.size()]]));
    return rt;
}

P ps[N], ops[N];
map<P, int> ptoid;
vector<L> ls[N];
bool isinf[N];
double ans[N];

int gid(P &p) {
	auto it = ptoid.find(p);
	if (it == ptoid.end()) return -1;
	return it->second;
}

L make_line(P p, L l) {
	P d = l.pb - l.pa; d = d.spin(pi / 2);
	P m = (l.pa + l.pb) / 2;
	l = L(m, m + d);
	if (((l.pb - l.pa) ^ (p - l.pa)) < 0) l = L(m + d, m);
	return l;
}

double calc_ans(int i) {
	vector<P> ps = HPI(ls[i]);
	double rt = 0;
	for (int i = 0; i < (int)ps.size(); ++i) {
		rt += (ps[i] ^ ps[(i + 1) % ps.size()]);
	}
	return abs(rt) / 2;
}

int main() {
	int n; cin >> n;
	for (int i = 0; i < n; ++i) cin >> ps[i].x >> ps[i].y;
	for (int i = 0; i < n; ++i) ops[i] = ps[i], ptoid[ops[i]] = i;

	random_shuffle(ps, ps + n);

	build(n, ps);

	for (auto *t : triang) {
		// cout << "Triangle: " 
		// 	<< "(" << t->p[0].x << ", " << t->p[0].y << ") "
		// 	<< "(" << t->p[1].x << ", " << t->p[1].y << ") "
		// 	<< "(" << t->p[2].x << ", " << t->p[2].y << ") " << endl;
		int z[3] = {gid(t->p[0]), gid(t->p[1]), gid(t->p[2])};
		for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) if (i != j && z[i] != -1) {
			L l(ops[z[i]], ops[z[j]]);
			ls[z[i]].push_back(make_line(ops[z[i]], l));
		}
	}

	for (int i = 0; i < n; ++i) {
		if (isinf[i]) cout << -1 << '\n';
		else cout << fixed << setprecision(12) << calc_ans(i) << '\n';
	}
}
