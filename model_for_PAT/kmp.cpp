#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 2000000;

char a[MAXN], b[MAXN];
int p[MAXN];
int n,m;

int kmp()
{
	int res = 0;
	int match = 0;
	for (int i = 1; i<=n; i++) {
		while (match!=0 && b[i]!=a[match+1]) match = p[match];
		if (b[i]==a[match+1]) match++;
		if (match==m) res++;
	}
	return res;
}

void init()
{
	memset(p,0,sizeof(p));
	int match = 0;
	for (int i = 2; i<=m; i++) {
		while (match!=0 && a[i]!=a[match+1]) match = p[match];
		if (a[i]==a[match+1]) match++;
		p[i] = match;
	}
}

//0 1 2 3 4 5
//a b a a b a
//0 0 1 1 2 3

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s", a+1);
		scanf("%s", b+1);
		m = strlen(a+1);
		n = strlen(b+1);
		init();
		printf("%d\n", kmp());
	}
}
