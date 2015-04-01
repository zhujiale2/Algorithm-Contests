#include <bits/stdc++.h>

using namespace std;

int w,h,n;
multiset <long long> H, V;
set <long long> HL, VL;

int main()
{
	scanf("%d%d%d", &w,&h,&n);
	H.insert(h);
	V.insert(w);
	HL.insert(0); HL.insert(h);
	VL.insert(0); VL.insert(w);
	getchar();
	for (int i = 1; i<=n; i++) {
		char x, bak;
		int y;
		scanf("%c%d", &x,&y);
		getchar();
		//cerr<<x<<" "<<y<<endl;
		int l, r;
		if (x=='H') {
			auto it = HL.lower_bound(y);
			it--;
			l = *it;
			r = *HL.upper_bound(y);
			HL.insert(y);
			H.erase(H.find(r-l));
			H.insert(y-l); H.insert(r-y);
		} else {
			auto it = VL.lower_bound(y);
			it--;
			l = *it;
			r = *VL.upper_bound(y);
			VL.insert(y);
			V.erase(V.find(r-l));
			V.insert(y-l); V.insert(r-y);
		}
		printf("%lld\n", (*H.rbegin())*(*V.rbegin()));
	}
}