#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000;

int n, m;
vector <int> E[MAXN];
int a[MAXN*3];
int first[MAXN];
int depth[MAXN];
int cnt = 0;
int dp[MAXN*3][30];
int pow2[30];

void dfs(int x, int fa, int d)
{
	a[++cnt] = x;
	first[x] = cnt;
	depth[x] = d;
	for (int i = 0; i<E[x].size(); i++) {
		int y = E[x][i];
		if (y==fa) continue;
		dfs(y,x,d+1);
		a[++cnt] = x;
	}
}

void init()
{
	pow2[0] = 1;
	for (int i = 1; i<30; i++) {
		pow2[i] = 2*pow2[i-1];
	}
}

void st()
{
	for (int i = 1; i<=cnt; i++) {
		dp[i][0] = a[i];
	}
	for (int j = 1; pow2[j]<=cnt; j++) {
		for (int i = 1; i<=cnt-pow2[j]+1; i++) {
			if (depth[dp[i][j-1]]<depth[dp[i+pow2[j-1]][j-1]]) {
				dp[i][j] = dp[i][j-1];
			} else {
				dp[i][j] = dp[i+pow2[j-1]][j-1];
			}
		}
	}
}

int main()
{
	init();
	scanf("%d%d", &n,&m);
	for (int i = 1; i<=m; i++) {
		int a, b;
		scanf("%d%d", &a,&b);
		E[a].push_back(b);
		E[b].push_back(a);
	}
	dfs(1,-1,1);
	st();
	int q;
	scanf("%d", &q);
	for (int i = 1; i<=q; i++) {
		int a, b;
		scanf("%d%d", &a,&b);
		a = first[a];
		b = first[b];
		if (a>b) swap(a,b);
		int k = log(b-a+1)/log(2);
		int res;
		if (depth[dp[a][k]]<depth[dp[b-pow2[k]+1][k]]) {
			res = dp[a][k];
		} else {
			res = dp[b-pow2[k]+1][k];
		}
		printf("%d\n", res);
	}
}
