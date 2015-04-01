#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000000;

struct node {
	double x,y;
	int index;
};

vector <node> point;

struct TreeNode {
	int Lchild, Rchild;
	int dimension,index;
	node data;
	double split;
};

int cnt;
TreeNode* kdT[MAXN];

bool cmpx(const node &a, const node &b)
{
	return a.x<b.x;
}

bool cmpy(const node &a, const node &b)
{
	return a.y<b.y;
}

int buildTree(int l, int r, int d)
{
	int index;
	TreeNode *T = new TreeNode;
	T->dimension = d;
	int mid = (l+r)/2;
	if (d==0) {
		nth_element(point.begin()+l, point.begin()+mid, point.begin()+r+1, cmpx);
		T->split = point[mid].x;
	} else {
		nth_element(point.begin()+l, point.begin()+mid, point.begin()+r+1, cmpy);
		T->split = point[mid].y;
	}
	T->data = point[mid];
	T->index = ++cnt;
	T->Lchild = T->Rchild = 0;
	kdT[cnt] = T;
	index = cnt;
	if (l<mid) T->Lchild = buildTree(l,mid-1,d&1);
	if (mid<r) T->Rchild = buildTree(mid+1,r,d&1);
	return index;
}

double dis(double x1, double y1, double x2, double y2)
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void query(TreeNode *T, double x, double y, node &res)
{
	if (dis(T->data.x,T->data.y,x,y)<dis(res.x,res.y,x,y)) {
		res = T->data;
	}
	if (T->dimension==0) {
		if (x<=T->data.x) {
			if (T->Lchild!=0) query(kdT[T->Lchild],x,y,res);
			if (fabs(T->split-x)<dis(res.x,res.y,x,y) && T->Rchild!=0) {
				query(kdT[T->Rchild],x,y,res);
			}
		}
		else if (x>T->data.x) {
			if (T->Rchild!=0) query(kdT[T->Rchild],x,y,res);
			if (fabs(T->split-x)<dis(res.x,res.y,x,y) && T->Lchild!=0) {
				query(kdT[T->Lchild],x,y,res);
			}
		}
	} else {
		if (y<=T->data.y) {
			if (T->Lchild!=0) query(kdT[T->Lchild],x,y,res);
			if (fabs(T->split-y)<dis(res.x,res.y,x,y) && T->Rchild!=0) {
				query(kdT[T->Rchild],x,y,res);
			}
		}
		else if (y>T->data.y) {
			if (T->Rchild!=0) query(kdT[T->Rchild],x,y,res);
			if (fabs(T->split-y)<dis(res.x,res.y,x,y) && T->Lchild!=0) {
				query(kdT[T->Lchild],x,y,res);
			}
		}
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i<=n; i++) {
		node tmp;
		scanf("%lf%lf", &tmp.x, &tmp.y);
		tmp.index = i;
		point.push_back(tmp);
	}
	buildTree(0,n-1,0);
	int q;
	scanf("%d", &q);
	for (int i = 1; i<=q; i++) {
		double a, b;
		scanf("%lf%lf", &a,&b);
		node res;
		res.x = INT_MAX;
		res.y = INT_MAX;
		query(kdT[1],a,b,res);
		printf("%f %f\n", res.x,res.y);
	}
}