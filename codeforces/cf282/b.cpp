#include <bits/stdc++.h>

using namespace std;

void extKMP(int n, const char str[], int m, const char pat[], int A[], int B[]) {
   A[0] = m;
   int ind = 0, k = 1;
   while (ind + 1 < m && pat[ind + 1] == pat[ind]) ind++;
   A[1] = ind;
   for (int i = 2; i < m; i++) {
      if (i <= k + A[k] - 1 && A[i - k] + i < k + A[k]) {
         A[i] = A[i - k];
      } else {
         ind = max(0, k + A[k] - i);
         while (ind + i < m && pat[ind + i] == pat[ind]) ind++;
         A[i] = ind, k = i;
      }
   }
   ind = 0, k = 0;
   while (ind < n && str[ind] == pat[ind]) ind++;
   B[0] = ind;
   for (int i = 1; i < n; i++) {
      if (i <= k + B[k] - 1 && A[i - k] + i < k + B[k]) {
         B[i] = A[i - k];
      } else {
         ind = max(0, k + B[k] - i);
         while (ind + i < n && ind < m && str[ind + i] == pat[ind]) ind++;
         B[i] = ind, k = i;
      }
   }
}

const int MAXN = 100100;
const long long M = 1e9+7;

char s[MAXN], t[MAXN];
int A[MAXN], B[MAXN], C[MAXN];
long long f[MAXN], S[MAXN], SS[MAXN];

int main()
{
	scanf("%s", s);
	scanf("%s", t);
	int n = strlen(s);
	int m = strlen(t);
	extKMP(n,s,m,t,A,B);
	for (int i = 0; i<n; i++) {
		if (B[i]==m) {
			C[i] = 1;
		}
	}
	for (int i = 1; i<n; i++) {
		C[i] += C[i-1];
	}
	for (int i = n-1; i>=0; i--) {
		int l = i, r = n-m, mid;
		int start = i>0 ? C[i-1] : 0;
		int ans = n;
		while (l<=r) {
			mid = (l+r)/2;
			if (C[mid]-start>0) {
				r = mid-1;
				ans = min(ans,mid);
			} else {
				l = mid+1;
			}
		}
		if (ans==n) {
			S[i] = (f[i]+S[i+1])%M;
			SS[i] = (S[i]+SS[i+1])%M;
			continue;
		} else {
			ans += m;
			f[i] = (n-ans+1+SS[ans])%M;
			S[i] = (f[i]+S[i+1])%M;
			SS[i] = (S[i]+SS[i+1])%M;
		}
		//cerr<<"f"<<i<<" "<<f[i]<<endl;
		//cerr<<"S"<<i<<" "<<S[i]<<endl;
	}
	cout<<S[0]<<endl;
	//while (1);
}