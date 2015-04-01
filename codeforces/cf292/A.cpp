#include <bits/stdc++.h>

using namespace std;

long long fact[10];
int a[15];
vector <int> res;

int main()
{
	fact[0] = 1;
	fact[1] = 1;
	for (int i = 2; i<10; i++) {
		fact[i] = i*fact[i-1];
	}
	int n;
	cin>>n;
	string s;
	cin>>s;
	int t = 0;
	for (int i = 0; i<s.size(); i++) {
		if (s[i]>='2' && s[i]<='9') {
			a[t] = s[i]-'0';
			t++;
		}
	}
	for (int i = 0; i<t; i++) {
		if (a[i]==4) {
			res.push_back(3);
			res.push_back(2);
			res.push_back(2);
		}
		else if (a[i]==6) {
			res.push_back(5);
			res.push_back(3);
		}
		else if (a[i]==8) {
			res.push_back(7);
			res.push_back(2);
			res.push_back(2);
			res.push_back(2);
		}
		else if (a[i]==9) {
			res.push_back(7);
			res.push_back(2);
			res.push_back(3);
			res.push_back(3);
		}
		else res.push_back(a[i]);
	}
	sort(res.begin(),res.end());
	for (int i = res.size()-1; i>=0; i--) {
		cout<<res[i];
	}
	cout<<endl;
}