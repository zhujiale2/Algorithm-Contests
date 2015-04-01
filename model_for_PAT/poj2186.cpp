#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <cstring>

using namespace std;

const int MAXN = 10005;

int n, m;
vector <int> E[MAXN];
vector <int> R[MAXN];
vector <int> A[MAXN];
int cnt;
int scc[MAXN];
vector <int> q;
int visited[MAXN];

void dfs1(int x)
{
	visited[x] = 1;
	for (int i = 0; i<E[x].size(); i++) {
		int y = E[x][i];
		if (!visited[y]) {
			dfs1(y);
		}
	}
	q.push_back(x);
}

void dfs2(int x)
{
	visited[x] = 1;
	scc[x] = cnt;
	for (int i = 0; i<R[x].size(); i++) {
		int y = R[x][i];
		if (!visited[y]) dfs2(y);
	}
}

void SCC()
{
	memset(visited, 0, sizeof(visited));
	q.clear();
	cnt = 0;
	for (int i = 1; i<=n; i++) {
		if (!visited[i]) dfs1(i);
	}
	memset(visited, 0, sizeof(visited));
	for (int i = 1; i<=n; i++) {
		for (int j = 0; j<E[i].size(); j++) {
			R[E[i][j]].push_back(i);
		}
	}
	for (int i = q.size()-1; i>=0; i--) {
		if (!visited[q[i]]) {
			++cnt;
			dfs2(q[i]);
		}
	}
}

int main()
{
	while (scanf("%d%d", &n, &m)==2) {
		for (int i = 1; i<=n; i++) {
			E[i].clear(); R[i].clear(); A[i].clear();
		}
		for (int i = 1; i<=m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			E[a].push_back(b);
		}
		SCC();
		int res = 0;
		for (int i = 1; i<=n; i++) {
			for (int j = 0; j<E[i].size(); j++) {
				int x = scc[i];
				int y = scc[E[i][j]];
				if (x!=y) A[x].push_back(y);
			}
		}
		int node;
		for (int i = 1; i<=cnt; i++) {
			if (A[i].size()==0) {
				res++;
				node = i;
			}
		}
		if (res!=1) {
			printf("0\n");
		} else {
			int ans = 0;
			for (int i = 1; i<=n; i++) {
				if (scc[i]==node) ans++;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}