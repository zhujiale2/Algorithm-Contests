#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000000;

struct point {
	double x, y;
};

int n;
point a[MAXN];
point res;

double dis(double x1, double y1, double x2, double y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void query(double x, double y, point &res)
{
	for (int i = 1; i<=n; i++) {
		if (dis(x,y,a[i].x,a[i].y)<dis(x,y,res.x,res.y)) {
			res = a[i];
		}
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i<=n; i++) {
		scanf("%lf%lf", &a[i].x,&a[i].y);
	}
	int q;
	scanf("%d", &q);
	for (int i = 1; i<=q; i++) {
		double x,y;
		scanf("%lf%lf", &x,&y);
		res.x = res.y = INT_MAX;
		query(x,y,res);
		printf("%f %f\n", res.x, res.y);
	}
}
