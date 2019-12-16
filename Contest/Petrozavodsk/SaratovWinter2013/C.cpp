  #include <bits/stdc++.h>
  using namespace std;
   
  const double pi = acos(-1);
   
  struct P {
      double x, y; 
      P operator + (const P b) { return P{x + b.x, y + b.y}; }
      P operator - (const P b) { return P{x - b.x, y - b.y}; }
      P operator * (const double b) { return P{x * b, y * b}; }
      P operator / (const double b) { return P{x / b, y / b}; }
      P spin(const double o) {
          double c = cos(o), s = sin(o);
          return P{c * x - s * y, s * x + c * y};
      }
  };
   
  int main() {
      ios_base::sync_with_stdio(0); cin.tie(0);
      int n; cin >> n;
      for (int i = 1; i <= n; ++i) {
          double w, h; cin >> w >> h;
          P c, a; cin >> c.x >> c.y >> a.x >> a.y;
          double alpha, s; cin >> alpha >> s;
          double oalpha = alpha;
          alpha = (alpha) / 180 * pi;
   
          //cerr << "alpha = " << alpha << endl;
   
          P r[6]; r[1] = a - c;
          r[2] = r[1]; r[2].x += w;
          r[3] = r[1]; r[3].y += h;
          r[4] = r[3]; r[4].x += w;
   
          // cerr << "org" << endl;
          // cerr << r[1].x << ' ' << r[1].y << endl;
          // cerr << r[2].x << ' ' << r[2].y << endl;
          // cerr << r[3].x << ' ' << r[3].y << endl;
          // cerr << r[4].x << ' ' << r[4].y << endl;
   
          for (int i = 1; i <= 4; ++i) r[i] = (r[i] - a).spin(alpha) + a;
          // cerr << "rot" << endl;
          // cerr << r[1].x << ' ' << r[1].y << endl;
          // cerr << r[2].x << ' ' << r[2].y << endl;
          // cerr << r[3].x << ' ' << r[3].y << endl;
          // cerr << r[4].x << ' ' << r[4].y << endl;
          for (int i = 1; i <= 4; ++i) r[i] = (r[i] - a) * s + a;
          // cerr << "scl" << endl;
          // cerr << r[1].x << ' ' << r[1].y << endl;
          // cerr << r[2].x << ' ' << r[2].y << endl;
          // cerr << r[3].x << ' ' << r[3].y << endl;
          // cerr << r[4].x << ' ' << r[4].y << endl;
   
          P d = (r[1] + r[2] + r[3] + r[4]) / 4;
          
          for (int i = 1; i <= 4; ++i) r[i] = (r[i] - d).spin(-alpha) + d;
          // cerr << "rot -1" << endl;
          // cerr << r[1].x << ' ' << r[1].y << endl;
          // cerr << r[2].x << ' ' << r[2].y << endl;
          // cerr << r[3].x << ' ' << r[3].y << endl;
          // cerr << r[4].x << ' ' << r[4].y << endl;
   
          double width = (r[2] - r[1]).x;
          double height = (r[3] - r[1]).y;
          double left = r[1].x;
          double top = r[1].y;
          double transform = oalpha;
   
          printf(".item%d { width: %.1lfpx; height: %.1lfpx; left: %.1lfpx; top: %.1lfpx; transform: rotate(%.1lfdeg); }\n",
                  i, width, height, left, top, transform);
      }
  }
