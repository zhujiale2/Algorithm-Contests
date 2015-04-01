#include <bits/stdc++.h>

using namespace std;

string s;

int main()
{
	cin>>s;
	int n = s.size();
	int pointer = n-1;
	while (s[pointer]!='#') {
		pointer--;
	}
	int cnt = 0;
	int tmp = 0;
	for (int i = 0; i<n; i++) {
		if (s[i]=='(') {
			cnt++;
		}
		else if (cnt==')') {
			cnt--;
		}
		else {
			cnt--;
		}
	}
	if (cnt<0) {
		cout<<-1<<endl;
		return 0;
	}
	tmp = 1+cnt;
	cnt = 0;
	for (int i = 0; i<n; i++) {
		if (s[i]=='(') {
			cnt++;
		}
		else if (cnt==')') {
			cnt--;
		}
		else {
			if (i==pointer) {
				cnt -= tmp;
			}
			else {
				cnt--;
			}
		}
		if (cnt<0) {
			cout<<-1<<endl;
			return 0;
		}
	}
	if (cnt!=0) {
		cout<<-1<<endl;
		return 0;
	}
	for (int i = 0; i<n; i++) {
		if (s[i]!='#') continue;
		if (i==pointer) {
			cout<<tmp<<endl;
		}
		else {
			cout<<1<<endl;
		}
	}
	//while (1);
}