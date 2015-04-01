#include <bits/stdc++.h>

using namespace std;

int l[10], r[10];

double calc(int l, int r, int m)
{
	if (l>m) return 0;
	if (l<=m && r>=m) return m-l+1;
	if (r<=m) return r-l+1;
}

double calc2(int l, int r, int m)
{
	if (l>=m) return 0;
	if (l<m && r>=m) return m-l;
	if (r<m) return r-l+1;
}

int main()
{
	int n;
	cin>>n;
	double ans = 0;
	double fenmu = 1;
	int start = INT_MAX;
	int end = 0;
	for (int i = 1; i<=n; i++) {
		cin>>l[i]>>r[i];
		fenmu *= r[i]-l[i]+1;
		start = min(start,l[i]);
		end = max(end,r[i]);
	}
	for (int i = start; i<=end; i++) {
		double res = 0;
		for (int j = 1; j<=n; j++) {
			if (l[j]<=i && i<=r[j]) {
				int bid = j;
				for (int k = 1; k<=n; k++) {
					if (k==bid) continue;
					if (i<=r[k]) {
						int buyer = k;
						cerr<<"bid : "<<bid<<"   buyer : "<<buyer<<" = "<<i<<endl;
						double tmp = min(r[k]-i+1,r[k]-l[k]+1);
						for (int x = 1; x<=n; x++) {
							if (x==buyer || x==bid) continue;
							if (x>bid) tmp *= calc(l[x],r[x],i);
							else tmp *= calc2(l[x],r[x],i);
						}
						res += tmp;
						int sig = -1;
						for (int x = 2; x<=n-1; x++) {
							res += sig*;
							sig = -sig;
						}
						cerr<<"res : "<<res<<endl;
					}
				}
			}
		}	
		ans += res*i/fenmu;	
	}
	printf("%.10f\n", ans);
}