#include <bits/stdc++.h>

using namespace std;

class CountryGroupHard {
public:
	string solve(vector <int>);
};

string CountryGroupHard::solve(vector <int> a) 
{
	int n = a.size();
	vector <int> f(n+1);
	f[0] = 1;
	for (int i = 0; i<=n; i++)
		for (int j = 0; j<i; j++) {
			int flag = 0;
			for (int k = j; k<i; k++) {
				if (a[k]!=0 && a[k]!=i-j) {
					flag++;
					break;
				}
			}
			if (!flag) f[i] += f[j];
		}
	if (f[n]==1) return "Sufficient";
	else return "Insufficient";
}


//Powered by [KawigiEdit] 2.0!