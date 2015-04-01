#include <bits/stdc++.h>

#define M 1000000007LL
#define PI 3.14159265358
#define eps 1e-8;

using namespace std;

int main()
{
	int n, m;
	cin>>m>>n;
	double ans = 0;
	for (int i = m; i>=1; i--){
		double tmp = 0;
		tmp = (double)i * (pow(1.0-(double)(m-i)/m, n) - pow(1.0-(double)(m-i+1)/m, n));
	//	cout<<tmp<<endl;
		ans += tmp;
	}
	printf("%.8lf\n", ans);
}