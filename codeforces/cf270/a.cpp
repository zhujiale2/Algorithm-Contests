#include <bits/stdc++.h>

using namespace std;

bool isprime(int x)
{
	for (int i = 2; i<=(int)sqrt(x)+1; i++){
		if (x%i==0) return false;
	}
	return true;
}

int main()
{
	int n;
	cin>>n;
	int d = 4;
	for (int d = 4; d<=n; d++){
		if (isprime(d)) continue;
		if (isprime(n-d)) continue;
		cout<<d<<" "<<n-d<<endl;
		break;
	}
}