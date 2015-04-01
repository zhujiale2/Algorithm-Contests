#include <bits/stdc++.h>

using namespace std;

vector <int> q;

int main()
{
	int n, k;
	cin>>n>>k;
	for (int i = 1; i<=n; i++){
		int tmp;
		cin>>tmp;
		q.push_back(tmp);
	}
	sort(q.begin(), q.end());
	int cnt = 0;
	int ans = 0;
	int maxh = 0;
	for (int i = n-1; i>=0; i--){
		maxh = max(q[i],maxh);
		if (cnt<k && i!=0){
			cnt++;
		}
		if (cnt==k||i==0){
			ans += 2*(maxh-1);
			maxh = cnt = 0;
		}
		//cout<<i<<" "<<ans<<" "<<maxh<<endl;
	}
	cout<<ans<<endl;
}