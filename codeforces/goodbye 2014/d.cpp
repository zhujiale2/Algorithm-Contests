#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150000;

int n;
pair <int,int> edge[MAXN];
double E[MAXN];
double w[MAXN];
vector <int> tree[MAXN];
double size[MAXN];

double dfs(int x, int fa)
{
	double res = 1;
	for (int k = 0; k<tree[x].size(); k++) {
		int y = tree[x][k];
		if (y==fa) continue;
		res += dfs(y,x);
	}
	size[x] = res;
	return res;
}

int main()
{
  	scanf("%d", &n);
  	for (int i = 1; i<n; i++) {
  		int a, b, c; 
  		scanf("%d%d%d", &a, &b, &c);
  		edge[i].first = a;
  		edge[i].second = b;
  		w[i] = c;
  		tree[a].push_back(b);
  		tree[b].push_back(a);
  	}
  	dfs(1,-1);
  	for (int i = 1; i<n; i++) {
  		double a = min(size[edge[i].first], size[edge[i].second]);
  		double b = (double)n-a;
  		E[i] += (double)a*b*(a-1)*3.0;
  		E[i] += (double)a*b*(b-1)*3.0;
  		//cerr<<i<<" : "<<E[i]<<endl;
  	}
  	int q;
  	double tot = 0;
  	double res;
  	double fenmu = (double)n*(n-1)*(n-2);
  	for (int i = 1; i<n; i++) {
  		tot += 2.0*(double)w[i]*E[i];
  	}
  	//cerr<<"tot : "<<tot<<endl;
  	scanf("%d", &q);
  	for (int i = 1; i<=q; i++) {
  		int x, c;
  		scanf("%d%d", &x, &c);
  		tot -= 2.0*(double)w[x]*E[x];
  		w[x] = (double)c;
  		tot += 2.0*(double)w[x]*E[x];
  		//cerr<<"tot : "<<tot<<endl;
  		res = (double)tot/fenmu;
  		printf("%.10f\n", res);
  	}
//  	while (1);
}