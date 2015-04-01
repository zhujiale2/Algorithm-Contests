#include <bits/stdc++.h>

using namespace std;

int v[100005];

int main()
{
	int n, k;
	cin>>n>>k;
	int cnt = 0;
	int now = 1;
	while (cnt<n){
		if (!v[now]){
			if (cnt!=0) printf(" ");
			printf("%d", now);
			cnt++;
			v[now]++;
		}
		if (k==1){
			now = max(1, now-k);
			while (v[now]) now++;
		}
		else{
			if (now-k>=1 && !v[now-k]) now -= k;
			else {
				now+=k;
			}
			k--;
		}
	}
	printf("\n");
}