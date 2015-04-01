#include <bits/stdc++.h>

using namespace std;

const double PI = 3.14159265358;

class NoRightTurnDiv2 {
public:
  vector <int> findPath(vector <int>, vector <int>);
};

double cross(double x1,double y1,double x2,double y2)
{
  return x1*y2-y1*x2;
}

struct point{
  double x,y;
  int index;
};

point T;

bool cmp(const point& a, const point& b)
{
  return cross(a.x-T.x,a.y-T.y,b.x-T.x,b.y-T.y)>0;
}

vector <int> NoRightTurnDiv2::findPath(vector <int> x, vector <int> y) {
  int n = x.size();
  vector <int> c;
  for (int i =0; i<n; i++) c.push_back(i);
  vector <int> res;
  for (int i = 1; i<n; i++) {
    if (y[i]<y[0] || y[i]==y[0]&&x[i]>x[0]) {
      swap(x[i],x[0]);
      swap(y[i],y[0]);
      swap(c[i],c[0]);
    }
  }
  vector <point> p;
  for (int i = 0; i<n; i++) {
    point tmp;
    tmp.x = x[i]; tmp.y = y[i]; tmp.index = c[i];
    p.push_back(tmp);
  }
  res.push_back(p[0].index);
  for (int i = 1; i<n; i++) {
    T = p[i-1];
    sort(p.begin()+i, p.end(), cmp);
    res.push_back(p[i].index);
  }
  return res;
}


//Powered by [KawigiEdit] 2.0!