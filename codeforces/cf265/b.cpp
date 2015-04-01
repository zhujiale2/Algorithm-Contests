#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-8;

struct Point3D {
    double x, y, z;
};

struct Line3D {
    Point3D a, b;
};

struct Plane {
    Point3D a, b, c;
};

struct PlaneF {
    // ax + by + cz + d = 0
    double a, b, c, d;
};

inline bool zero(double x) {
    return (x > 0 ? x : -x) < EPS;
}

//平方
inline double sqr(double d) {
    return d * d;
}

//计算cross product U x V
inline Point3D xmult(const Point3D & u, const Point3D & v) {
    Point3D ret;
    ret.x = u.y * v.z - v.y * u.z;
    ret.y = u.z * v.x - u.x * v.z;
    ret.z = u.x * v.y - u.y * v.x;
    return ret;
}

//计算dot product U . V
inline double dmult(const Point3D & u, const Point3D & v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

//矢量差 U - V
inline Point3D subt(const Point3D & u, const Point3D & v) {
    Point3D ret;
    ret.x = u.x - v.x;
    ret.y = u.y - v.y;
    ret.z = u.z - v.z;
    return ret;
}

//取平面法向量
inline Point3D pvec(const Plane & s) {
    return xmult(subt(s.a, s.b), subt(s.b, s.c));
}
inline Point3D pvec(const Point3D & s1, const Point3D & s2, const Point3D & s3) {
    return xmult(subt(s1, s2), subt(s2, s3));
}
inline Point3D pvec(const PlaneF & p) {
    Point3D ret;
    ret.x = p.a;
    ret.y = p.b;
    ret.z = p.c;
    return ret;
}

//两点距离
inline double dis(const Point3D & p1, const Point3D & p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) + (p1.z - p2.z)*(p1.z - p2.z));
}

//向量大小
inline double vlen(const Point3D & p) {
    return sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
}

//向量大小的平方
inline double sqrlen(const Point3D & p) {
    return (p.x*p.x + p.y*p.y + p.z*p.z);
}

//判三点共线
bool dotsInline(const Point3D & p1, const Point3D & p2, const Point3D & p3) {
    return sqrlen(xmult(subt(p1, p2), subt(p2, p3))) < EPS;
}

//判四点共面
bool dotsOnplane(const Point3D & a, const Point3D & b, const Point3D & c, const Point3D & d) {
    return zero(dmult(pvec(a, b, c), subt(d, a)));
}

//判点是否在线段上, 包括端点和共线
bool dotOnlineIn(const Point3D & p, const Line3D & l) {
    return zero(sqrlen(xmult(subt(p, l.a), subt(p, l.b)))) && (l.a.x - p.x) * (l.b.x - p.x) < EPS && (l.a.y - p.y) * (l.b.y - p.y) < EPS && (l.a.z - p.z) * (l.b.z - p.z) < EPS;
}
bool dotOnlineIn(const Point3D & p, const Point3D & l1, const Point3D & l2) {
    return zero(sqrlen(xmult(subt(p, l1), subt(p, l2)))) && (l1.x - p.x) * (l2.x - p.x) < EPS && (l1.y - p.y) * (l2.y - p.y) < EPS && (l1.z - p.z) * (l2.z - p.z) < EPS;
}

//判点是否在线段上, 不包括端点
bool dotOnlineEx(const Point3D & p, const Line3D & l) {
    return dotOnlineIn(p, l) && (!zero(p.x - l.a.x) || !zero(p.y - l.a.y) || !zero(p.z - l.a.z)) && (!zero(p.x - l.b.x) || !zero(p.y - l.b.y) || !zero(p.z - l.b.z));
}
bool dotOnlineEx(const Point3D & p, const Point3D & l1, const Point3D & l2) {
    return dotOnlineIn(p, l1, l2) && (!zero(p.x - l1.x) || !zero(p.y - l1.y) || !zero(p.z - l1.z)) && (!zero(p.x - l2.x) || !zero(p.y - l2.y) || !zero(p.z - l2.z));
}

//判点是否在空间三角形上, 包括边界, 三点共线无意义
bool dotInplaneIn(const Point3D & p, const Plane & s) {
    return zero(vlen(xmult(subt(s.a, s.b), subt(s.a, s.c))) - vlen(xmult(subt(p, s.a), subt(p, s.b))) - vlen(xmult(subt(p, s.b), subt(p, s.c))) - vlen(xmult(subt(p, s.c), subt(p, s.a))));
}
bool dotInplaneIn(const Point3D & p, const Point3D & s1, const Point3D & s2, const Point3D & s3) {
    return zero(vlen(xmult(subt(s1, s2), subt(s1, s3))) - vlen(xmult(subt(p, s1), subt(p, s2))) - vlen(xmult(subt(p, s2), subt(p, s3))) - vlen(xmult(subt(p, s3), subt(p, s1))));
}

//判点是否在空间三角形上, 不包括边界, 三点共线无意义
bool dotInplaneEx(const Point3D & p, const Plane & s) {
    return dotInplaneIn(p, s) && sqrlen(xmult(subt(p, s.a), subt(p, s.b))) > EPS && sqrlen(xmult(subt(p, s.b), subt(p, s.c))) > EPS && sqrlen(xmult(subt(p, s.c), subt(p, s.a))) > EPS;
}
bool dotInplaneEx(const Point3D & p, const Point3D & s1, const Point3D & s2, const Point3D & s3) {
    return dotInplaneIn(p, s1, s2, s3) && sqrlen(xmult(subt(p, s1), subt(p, s2))) > EPS && sqrlen(xmult(subt(p, s2), subt(p, s3))) > EPS && sqrlen(xmult(subt(p, s3), subt(p, s1))) > EPS;
}

//判两点在线段同侧, 点在线段上返回0, 不共面无意义
bool sameSide(const Point3D & p1, const Point3D & p2, const Line3D & l) {
    return dmult(xmult(subt(l.a, l.b), subt(p1, l.b)), xmult(subt(l.a, l.b), subt(p2, l.b))) > EPS;
}
bool sameSide(const Point3D & p1, const Point3D & p2, const Point3D & l1, const Point3D & l2) {
    return dmult(xmult(subt(l1, l2), subt(p1, l2)), xmult(subt(l1, l2), subt(p2, l2))) > EPS;
}

//判两点在线段异侧, 点在线段上返回0, 不共面无意义
bool oppositeSide(const Point3D & p1, const Point3D & p2, const Line3D & l) {
    return dmult(xmult(subt(l.a, l.b), subt(p1, l.b)), xmult(subt(l.a, l.b), subt(p2, l.b))) < -EPS;
}
bool oppositeSide(const Point3D & p1, const Point3D & p2, const Point3D & l1, const Point3D & l2) {
    return dmult(xmult(subt(l1, l2), subt(p1, l2)), xmult(subt(l1, l2), subt(p2, l2))) < -EPS;
}

//判两点在平面同侧, 点在平面上返回0
bool sameSide(const Point3D & p1, const Point3D & p2, const Plane & s) {
    return dmult(pvec(s), subt(p1, s.a)) * dmult(pvec(s), subt(p2, s.a)) > EPS;
}
bool sameSide(const Point3D & p1, const Point3D & p2, const Point3D & s1, const Point3D & s2, const Point3D & s3) {
    return dmult(pvec(s1, s2, s3), subt(p1, s1)) * dmult(pvec(s1, s2, s3), subt(p2, s1)) > EPS;
}
bool sameSide(const Point3D & p1, const Point3D & p2, const PlaneF & s) {
    return (s.a * p1.x + s.b * p1.y + s.c * p1.z + s.d) * (s.a * p2.x + s.b * p2.y + s.c * p2.z + s.d) > EPS;
}

//判两点在平面异侧, 点在平面上返回0
bool oppositeSide(const Point3D & p1, const Point3D & p2, const Plane & s) {
    return dmult(pvec(s), subt(p1, s.a)) * dmult(pvec(s), subt(p2, s.a)) < -EPS;
}
bool oppositeSide(const Point3D & p1, const Point3D & p2, const Point3D & s1, const Point3D & s2, const Point3D & s3) {
    return dmult(pvec(s1, s2, s3), subt(p1, s1)) * dmult(pvec(s1, s2, s3), subt(p2, s1)) < -EPS;
}
bool oppositeSide(const Point3D & p1, const Point3D & p2, const PlaneF & s) {
    return (s.a*p1.x+s.b*p1.y+s.c*p1.z+s.d) * (s.a*p2.x+s.b*p2.y+s.c*p2.z+s.d) < -EPS;
}

//判两直线平行
bool parallel(const Line3D & u, const Line3D & v) {
    return sqrlen(xmult(subt(u.a, u.b), subt(v.a, v.b))) < EPS;
}
bool parallel(const Point3D & u1, const Point3D & u2, const Point3D & v1, const Point3D & v2) {
    return sqrlen(xmult(subt(u1, u2), subt(v1, v2))) < EPS;
}

//判两平面平行
bool parallel(const Plane & u, const Plane & v) {
    return sqrlen(xmult(pvec(u), pvec(v))) < EPS;
}
bool parallel(const Point3D & u1, const Point3D & u2, const Point3D & u3, const Point3D & v1, const Point3D & v2, const Point3D & v3) {
    return sqrlen(xmult(pvec(u1, u2, u3), pvec(v1, v2, v3))) < EPS;
}
bool parallel(const PlaneF & u, const PlaneF & v) {
    return sqrlen(xmult(pvec(u), pvec(v))) < EPS;
}

//判直线与平面平行
bool parallel(const Line3D & l, const Plane & s) {
    return zero(dmult(subt(l.a, l.b), pvec(s)));
}
bool parallel(const Point3D & l1, const Point3D & l2, const Point3D & s1, const Point3D & s2, const Point3D & s3) {
    return zero(dmult(subt(l1, l2), pvec(s1, s2, s3)));
}
bool parallel(const Line3D & l, const PlaneF & s) {
    return zero(dmult(subt(l.a, l.b), pvec(s)));
}

//判两直线垂直
bool perpendicular(const Line3D & u, const Line3D & v) {
    return zero(dmult(subt(u.a, u.b), subt(v.a, v.b)));
}
bool perpendicular(const Point3D & u1, const Point3D & u2, const Point3D & v1, const Point3D & v2) {
    return zero(dmult(subt(u1, u2), subt(v1, v2)));
}

//判两平面垂直
bool perpendicular(const Plane & u, const Plane & v) {
    return zero(dmult(pvec(u), pvec(v)));
}
bool perpendicular(const Point3D & u1, const Point3D & u2, const Point3D & u3, const Point3D & v1, const Point3D & v2, const Point3D & v3) {
    return zero(dmult(pvec(u1, u2, u3), pvec(v1, v2, v3)));
}
bool perpendicular(const PlaneF & u, const PlaneF & v) {
    return zero(dmult(pvec(u), pvec(v)));
}

//判直线与平面垂直
bool perpendicular(const Line3D & l, const Plane & s) {
    return sqrlen(xmult(subt(l.a, l.b), pvec(s))) < EPS;
}
bool perpendicular(const Point3D & l1, const Point3D & l2, const Point3D & s1, const Point3D & s2, const Point3D & s3) {
    return sqrlen(xmult(subt(l1, l2), pvec(s1, s2, s3))) < EPS;
}
bool perpendicular(const Line3D & l, const PlaneF & s) {
    return sqrlen(xmult(subt(l.a, l.b), pvec(s))) < EPS;
}

//判两线段相交, 不包括端点和部分重合
bool intersectEx(const Line3D & u, const Line3D & v) {
    return dotsOnplane(u.a, u.b, v.a, v.b) && oppositeSide(u.a, u.b, v) && oppositeSide(v.a, v.b, u);
}
bool intersectEx(const Point3D & u1, const Point3D & u2, const Point3D & v1, const Point3D & v2) {
    return dotsOnplane(u1, u2, v1, v2) && oppositeSide(u1, u2, v1, v2) && oppositeSide(v1, v2, u1, u2);
}

Point3D intersection(Point3D u1, Point3D u2, Point3D v1, Point3D v2) {
   double dxu = u2.x - u1.x;
   double dyu = u2.y - u1.y;
   double dzu = u2.z - u1.z;
   double dxv = v2.x - v1.x;
   double dyv = v2.y - v1.y;
   double dzv = v2.z - v1.z;
   double t;
   if (!zero(dxu * dyv - dyu * dxv)) {
      t = (dyv * (v1.x - u1.x) + dxv * (u1.y - v1.y)) / (dxu * dyv - dyu * dxv);
   } else if (!zero(dxu * dzv - dzu * dxv)) {
      t = (dzv * (v1.x - u1.x) + dxv * (u1.z - v1.z)) / (dxu * dzv - dzu * dxv);
   } else {
      t = (dzv * (v1.y - u1.y) + dyv * (u1.z - v1.z)) / (dyu * dzv - dzu * dyv);
   }
   Point3D ret;
   ret.x = u1.x + dxu * t;
   ret.y = u1.y + dyu * t;
   ret.z = u1.z + dzu * t;
   return ret;
}

int a[8], b[8], c[8];

void print()
{
	cout<<"YES"<<endl;
	for (int i = 0; i<8; i++)
		cout<<a[i]<<" "<<b[i]<<" "<<c[i]<<endl;
}

int work()
{
	Point3D p[8];
	for (int i = 0; i<8; i++){
		p[i].x = a[i];
		p[i].y = b[i];
		p[i].z = c[i];
	}
	int far[8];
	memset(far, -1, sizeof(far));
	for (int i = 0; i<8; i++){
		double dist = -1;
		for (int j = 0; j<8; j++){
			if (j==i) continue;
			if (dis(p[j],p[i])>dist){
				dist = dis(p[j],p[i]);
				far[i] = j;
			}
		}
	}
	for (int i = 0; i<8; i++){
		if (far[far[i]]!=i) return 0;
	}
	Line3D l[4];
	int cnt = 0;
	int v[8] = {0};
	for (int i = 0; i<8; i++){
		if (v[i]) continue;
		v[i] = v[far[i]] = 1;
		l[cnt].a = p[i];
		l[cnt].b = p[far[i]];
		cnt++;
	}
	for (int i = 1; i<4; i++){
		if (dis(l[i].a,l[i].b)!=dis(l[i-1].a,l[i-1].b)) return 0;
	}
	for (int i = 0; i<4; i++)
		for (int j = i+1; j<4; j++){
			if (!intersectEx(l[i],l[j])) return 0;
		}
	//Point3D P1 = intersection(l[0].a, l[0].b, l[1].a, l[1].b);
	//Point3D P2 = intersection(l[2].a, l[2].b, l[3].a, l[3].b);
	//if (fabs(dis(P1,P2))>1e-5) return 0;
	return 1;
}

int flag;

void dfs(int x)
{
	if (flag) return;
	if (x>=8){
		if (work()){
			flag = 1;
			print();
		}
		return;
	}	
	int A, B, C;

	A = a[x]; B = b[x]; C = c[x];
	dfs(x+1);
	a[x] = A; b[x] = C; c[x] = B;
	dfs(x+1);
	a[x] = B; b[x] = A; c[x] = C;
	dfs(x+1);
	a[x] = B; b[x] = C; c[x] = A;
	dfs(x+1);
	a[x] = C; b[x] = A; c[x] = B;
	dfs(x+1);
	a[x] = C; b[x] = B; c[x] = A;
	dfs(x+1);
	return;
}

int main()
{
	for (int i = 0; i<8; i++)
		cin>>a[i]>>b[i]>>c[i];
	flag = 0;
	dfs(0);
	if (!flag) cout<<"NO"<<endl;
}