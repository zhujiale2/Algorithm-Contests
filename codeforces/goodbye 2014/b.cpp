#include <bits/stdc++.h>

using namespace std;

const int MAXN = 400;

int n;
int p[MAXN];
int res[MAXN];
int mat[MAXN][MAXN];

int main()
{
  	scanf("%d", &n);
  	for (int i = 1; i<=n; i++) {
  		scanf("%d", p+i);
  	}
  	char s[MAXN];
  	for (int i = 1; i<=n; i++) {
  		scanf("%s", s);
  		for (int k = 1; k<=n; k++) {
  			mat[i][k] = s[k-1]-'0';
  			if (i==k) mat[i][k] = 1;
  		}
  	}
  	for (int k = 1; k<=n; k++) {
  		for (int i = 1; i<=n; i++) {
  			for (int j = 1; j<=n; j++) {
  				if (mat[i][k]==1 && mat[k][j]==1) mat[i][j] = 1;
  			}
  		}
  	}
  	int v[MAXN] = {0};
  	for (int i = 1; i<=n; i++) {
  		int min = 10000;
  		int node = -1;
  		for (int k = 1; k<=n; k++) {
  			if (!v[k] && mat[i][k]==1) {
  				if (p[k]<min) {
  					min = p[k];
  					node = k;
  				}
  			}
  		}
  		res[i] = min;
  		v[node] = 1;
  	}
  	for (int i = 1; i<n; i++) {
  		cout<<res[i]<<" ";
  	}
  	cout<<res[n]<<endl;
  	//while (1);
}