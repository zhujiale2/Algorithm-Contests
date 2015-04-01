#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200000;

char f[MAXN][60], s[MAXN][60];
int rank[MAXN];
char* q[MAXN];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i<=n; i++){
		scanf("%s %s", f+i, s+i);
		if (strcmp(f[i],s[i])>0) swap(f[i],s[i]);
	}
	for (int i = 1; i<=n; i++) scanf("%d", rank+i);
	int flag = 1;
	q[0] = f[0];
	for (int i = 1; i<=n; i++){
		int node = rank[i];
		if (strcmp(f[node],q[i-1])>0)q[i] = f[node];
		else if (strcmp(s[node],q[i-1])>0) q[i] = s[node];
		else{
			flag = 0;
			break;
		}
	}
	if (!flag) cout<<"NO"<<endl;
	else cout<<"YES"<<endl;
}