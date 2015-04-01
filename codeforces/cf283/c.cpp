#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100100;

vector <pair<pair<int,int>,int>> P;
vector <pair<pair<int,int>,pair<int,int>>> A;
int n, m;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i<=n; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		P.push_back(make_pair(make_pair(a,b),i));
	}
	scanf("%d", &m);
	for (int i = 1; i<=m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		A.push_back(make_pair(make_pair(a,b),make_pair(c,i)));
	}
	sort(P.begin(),P.end());
	sort(A.begin(),A.end());
	int pointer = 0;
	multimap <int,pair<int,int>> M;
	vector <int> res(n+1);
	for (int i = 0; i<n; i++) {
		int l, r, idx;
		l = P[i].first.first;
		r = P[i].first.second;
		idx = P[i].second;
		while (pointer<m && A[pointer].first.first<=l) {
			M.insert(make_pair(A[pointer].first.second,
				make_pair(A[pointer].second.second,A[pointer].second.first)));
			pointer++;
		}
		//cerr<<i<<" "<<pointer<<endl;
		auto it = M.lower_bound(r);
		if (it==M.end()) {
			printf("NO\n");
			//while (1);
			return 0;
		}
		else {
			it->second.second--;
			res[idx] = it->second.first;
			if (it->second.second==0) {
				M.erase(it);
			}
		}
	}
	printf("YES\n");
	for (int i = 1; i<=n; i++) {
		if (i!=n) {
			printf("%d ", res[i]);
		}
		else {
			printf("%d\n", res[i]);
		}
	}
	//while (1);
}