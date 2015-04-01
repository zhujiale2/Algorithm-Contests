#include <bits/stdc++.h>

using namespace std;

int a[1000];
int n, k;
double fenzi = 0;
double fenmu = 0;

int calc()
{
	int res = 0;
	for (int i = 1; i<=n; i++)
		for (int j = i+1; j<=n; j++) {
			if (a[i]>a[j]) res++;
		}
	return res;
}

void dfs(int x)
{
	if (x>k) {
		fenzi += calc();
		return;
	}
	for (int l = 1; l<=n; l++) {
		for (int r = l; r<=n; r++) {
			if (x==k) fenmu++;
			reverse(a+l,a+r+1);
			dfs(x+1);
			reverse(a+l,a+r+1);
		}
	}
}

int main()
{
	cin>>n>>k;
	for (int i = 1; i<=n; i++) cin>>a[i];
	dfs(1);
	printf("%.12f\n", fenzi/fenmu);
}