#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300000;

struct bound {
	int l,r;
};

int n, m;
long long d[MAXN], h[MAXN], hi[MAXN][19];
long long p[20];
long long sumd[MAXN];
pair <long long,long long> tree1[MAXN*2], tree2[MAXN*2];
bound match[MAXN*2];

void build()
{
	for (int i = 1; i<=2*n; i++) {
		sumd[i] = sumd[i-1]+d[i];
	}
	for (int i = 1; i<=2*n; i++) {
		hi[i][0] = h[i];
	}
	for (int k = 1; k<19; k++)
		for (int i = 1; i<=2*n-p[k]+1; i++) {
			hi[i][k] = max(hi[i][k-1],hi[i+p[k-1]][k-1]);
		}
}

void buildTree(pair <long long,long long> tree[], int node, int l, int r, long long sig)
{
	match[node].l = l;
	match[node].r = r;
	if (l==r) {
		tree[node].first = sig*sumd[l-1]+2*h[l];
		tree[node].second = -(1ll<<60);
	} else {
		int mid = (l+r)/2;
		buildTree(tree,node*2,l,mid,sig);
		buildTree(tree,node*2+1,mid+1,r,sig);
		long long t1 = tree[node*2].first;
		long long t2 = tree[node*2].second;
		long long u1 = tree[node*2+1].first;
		long long u2 = tree[node*2+1].second;
		tree[node].first = max(t1,u1);
		tree[node].second = t1>u1 ? max(t2,u1) : max(t1,u2);
	}
}

long long query(pair <long long,long long> tree[], int node, int l, int r, int type)
{
	int left = match[node].l;
	int right = match[node].r;
	if (left>r || right<l) return -(1ll<<60);
	if (left>=l && right<=r) {
		if (type==1) return tree[node].first;
		else return tree[node].second;
	}
	else {
		if (type==1) {
			long long t1 = query(tree,node*2,l,r,1);
			long long t2 = query(tree,node*2+1,l,r,1);
			return max(t1,t2);
		} else {
			long long t1 = query(tree,node*2,l,r,1);
			long long u1 = query(tree,node*2+1,l,r,1);
			if (t1>=u1) {
				long long t2 = query(tree,node*2,l,r,2);
				return max(t2,u1);
			} else {
				long long u2 = query(tree,node*2+1,l,r,2);
				return max(t1,u2);
			}
		}
	}
}

int main()
{
	p[0] = 1;
	for (int i = 1; i<20; i++) p[i] = 2ll*p[i-1];
	scanf("%d%d", &n, &m);
	for (int i = 1; i<=n; i++) {
		scanf("%d", d+i);
		d[i+n] = d[i];
	}
	for (int i = 1; i<=n; i++) {
		scanf("%d", h+i);
		h[i+n] = h[i];
	}
	build();
	buildTree(tree1,1,1,2*n,-1);
	buildTree(tree2,1,1,2*n,+1);
	for (int i = 1; i<=m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if (u>v) v += n;
		int left = v+1;
		int right = u+n-1;
		int len = right-left+1;
		int k = log(len)/log(2)-(1e-5);
		long long L1,L2,R1,R2;
		L1 = query(tree1,1,left,right,1);
		L2 = query(tree1,1,left,right,2);
		R1 = query(tree2,1,left,right,1);
		R2 = query(tree2,1,left,right,2);
		long long H = max(hi[left][k],hi[right-p[k]+1][k]);
		long long res;
		if (L1+R1==H*4ll) {
			//cerr<<"YES"<<endl;
			res = max(L2+R1,L1+R2);
		} else {
			res = L1+R1;
		}
		printf("%I64d\n", res);
	}
}