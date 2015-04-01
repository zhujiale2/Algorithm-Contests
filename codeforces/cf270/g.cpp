#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250000;
const int BLOCK = 10000;
const int BIT = 64;
typedef unsigned long long bitType;

const long double PI = acos(0.0) * 2.0;

typedef complex<double> CD;

inline void FFT(vector<CD> &a, bool inverse) {
	int n = a.size();
	for(int i = 0, j = 0; i < n; i++) {
    	if(j > i) swap(a[i], a[j]);
    	int k = n;
    	while(j & (k >>= 1)) j &= ~k;
    	j |= k;
  	}
  	double pi = inverse ? -PI : PI;
  	for(int step = 1; step < n; step <<= 1) {
    	double alpha = pi / step;
    	CD omegak = exp(CD(0,0));
    	CD omega = exp(CD(0, alpha));
        for(int k = 0; k < step; k++) {
	     	if (k!=0) omegak *= omega;
	      	for(int Ek = k; Ek < n; Ek += step << 1) { 
		        int Ok = Ek + step; 
	        	CD t = omegak * a[Ok];
	        	a[Ok] = a[Ek] - t;
	        	a[Ek] += t;       
      		}
    	}
  	}
  	if(inverse) for(int i = 0; i < n; i++) a[i] /= n;
}

inline vector<double> operator * (const vector<double>& v1, const vector<double>& v2) {
  	int s1 = v1.size(), s2 = v2.size(), S = 2;
  	while(S < s1 + s2) S <<= 1;
  	vector<CD> a(S,0), b(S,0); 
  	for(int i = 0; i < s1; i++) a[i] = v1[i];
  	FFT(a, false);
  	for(int i = 0; i < s2; i++) b[i] = v2[i];
  	FFT(b, false);
  	for(int i = 0; i < S; i++) a[i] *= b[i];
  	FFT(a, true);
  	vector<double> res(s1 + s2 - 1);
  	for(int i = 0; i < s1 + s2 - 1; i++) res[i] = a[i].real(); // Ðé²¿¾ùÎª0
  	return res;
}

char a[MAXN], b[MAXN];
vector <bitType> A[BIT], B[BIT];
int cnt[200][MAXN];
int lena, lenb;

double trans(int x)
{
	if (x==0) return -1;
	else return 1;
}

vector <double> X, Y, Z;

void work(int l, int r)
{
	X.clear();
	for (int i = l; i<=r; i++) X.push_back(trans(a[i]-'0'));
	Z = X*Y;
	int index = l/BLOCK;
	for (int i = BLOCK-1; i<lenb; i++){
		cnt[index][lenb-(i+1)] = (BLOCK-round(Z[i]))/2;
	}
}

int force(int l1, int r1, int l2, int r2)
{
	if (l1>r1 || l2>r2) return 0;
	int res = 0;
	int index1 = (l1-(l1%BIT))/BIT;
	int index2 = (l2-(l2%BIT))/BIT;
	int x1 = l1%BIT;
	int x2 = l2%BIT;
	for ( ; l1+BIT<=r1; l1 += BIT, l2+=BIT){
		res += __builtin_popcountll(A[x1][index1]^B[x2][index2]);
		index1++; index2++;
	}
	bitType q = BIT-r1+l1-1;
	res += __builtin_popcountll((A[x1][index1]>>q)^(B[x2][index2]>>q));
	return res;
}

int main()
{
	scanf("%s", a);
	scanf("%s", b);
	lena = strlen(a);
	lenb = strlen(b);
	for (int x = 0; x<BIT; x++){
		for (int i = x; i<lena; i+=BIT){
			bitType tmp = 0;
			for (int k = i; k<i+BIT && k<lena; k++){
				tmp |= (bitType)(a[k]-'0')<<(i+BIT-1-k);
			}
			A[x].push_back(tmp);
		}
	}
	for (int x = 0; x<BIT; x++){
		for (int i = x; i<lenb; i+=BIT){
			bitType tmp = 0;
			for (int k = i; k<i+BIT && k<lenb; k++){
				tmp |= (bitType)(b[k]-'0')<<(i+BIT-1-k);
			}
			B[x].push_back(tmp);
		}
	}
	for (int i = lenb-1; i>=0; i--) Y.push_back(trans(b[i]-'0'));
	int q, p1, p2, len;
	scanf("%d", &q);
	for (int i = BLOCK-1; i<lena; i+=BLOCK)	work(i-BLOCK+1, i);
	for (int i = 1; i<=q; i++){
		scanf("%d%d%d", &p1, &p2, &len);
		int e1 = p1+len-1;
		int e2 = p2+len-1;
		int ans = 0;
		int t1 = ((p1-1)/BLOCK+1)*BLOCK;
		int l = t1-p1;
		if (t1<=e1){
			ans += force(p1,p1+l-1,p2,p2+l-1);
			p1 += l; p2 += l;
		}
		else {
			ans += force(p1,e1,p2,e2);
			p1 = e1+1; p2 = e2+1;
		}
		int t2 = (e1+1)/BLOCK*BLOCK-1;
		l = e1-t2;
		if (t2>=p1){
			ans += force(t2+1,t2+l,e2-l+1,e2);
			e1 -= l; e2 -= l;
		}
		else{
			ans += force(p1,e1,p2,e2);
			e1 = p1-1; e2 = p2-1;	
		}
		/*
		while (p1<=e1 && p1%BLOCK!=0){
			if (a[p1]!=b[p2]) ans++;
			p1++; p2++;
		}
		while (e1>=p1 && (e1+1)%BLOCK!=0){
			if (a[e1]!=b[e2]) ans++;
			e1--; e2--;
		}
		*/
		if (e1>p1){
			int index = p1/BLOCK;
			int t = (e1+1-p1)/BLOCK;
			for (int k = index; k<index+t; k++){
				ans += cnt[k][p2+(k-index)*BLOCK];
			}
		}
		cout<<ans<<endl;
	}
}