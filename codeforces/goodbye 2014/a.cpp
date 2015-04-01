#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50000;

int q[MAXN];
int a[MAXN];
int n, t;
int v[MAXN];

int main()
{
  	scanf("%d%d", &n, &t);
  	for (int i = 1; i<n; i++) {
  		scanf("%d", a+i);
  	}
  	int now = 1;
  	int flag = 0;
  	while (now<=t) {
  		if (now==t){
  			flag = 1;
  			break;
  		}
  		now = now+a[now];
  	}
  	if (flag) {
  		cout<<"YES"<<endl;
  	} else {
  		cout<<"NO"<<endl;
  	}
}