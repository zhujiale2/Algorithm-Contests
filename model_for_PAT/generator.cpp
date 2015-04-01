#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000;

int main()
{
	srand(time(NULL));
	int n = MAXN;
	cout<<n<<endl;
	for (int i = 1; i<=n; i++) {
		double x = rand()*rand()/10000.0;
		double y = rand()*rand()/10000.0;
		cout<<x<<" "<<y<<endl;
	}
	int q = MAXN;
	cout<<q<<endl;
	for (int i = 1; i<=q; i++) {
		double x = rand()*rand()/10000.0;
		double y = rand()*rand()/10000.0;
		cout<<x<<" "<<y<<endl;
	}
}