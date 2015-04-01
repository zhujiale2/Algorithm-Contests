#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2010;
const long long INF = 100000000000000ll;

long long mat[MAXN][MAXN];
long long dis[MAXN][MAXN];
int v[MAXN];
int pre[MAXN];
vector <int> e[MAXN];

template <class elemType>
elemType prim(int n, const elemType mat[][MAXN], int * pre) {
    elemType mind[MAXN], ret = 0;
    int v[MAXN], i, j, k;
    for (i = 0; i<n; i++) {
        mind[i] = INF;
        v[i] = 0;
        pre[i] = -1;
    }
    for (mind[j = 0] = 0; j<n; j++) {
        for (k = -1, i = 0; i<n; i++) {
            if (!v[i] && (k == -1 || mind[i]<mind[k])) {
                k = i;
            }
        }
        v[k] = 1;
        ret += mind[k];
        for (i = 0; i < n; i++) {
            if (!v[i] && mat[k][i] < mind[i]) {
                mind[i] = mat[pre[i] = k][i];
            }
        }
    }
    return ret;
}

void dfs(int root, int x, long long len)
{
	dis[root][x] = len;
	v[x] = 1;
	for (int k = 0; k<e[x].size(); k++){
		int y = e[x][k];
		if (v[y]) continue;
		dfs(root,y,len+mat[x][y]);
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++){
			scanf("%d", &mat[i][j]);
			if (i==j && mat[i][i]!=0){
				cout<<"NO"<<endl;
				return 0;
			}
			else if (i!=j && mat[i][j]==0){
				cout<<"NO"<<endl;
				return 0;	
			}
		}
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++){
			if (mat[i][j]!=mat[j][i]){
				cout<<"NO"<<endl;
				return 0;
			}
		}
	prim(n, mat, pre);
	for (int i = 0; i<n; i++){
		if (pre[i]!=-1){
			e[pre[i]].push_back(i);
			e[i].push_back(pre[i]);
		}
	}
	for (int i = 0; i<n; i++){
		memset(v, 0, sizeof(v));
		dfs(i,i,0);
	}

	/*
	for (int i = 0; i<n; i++){
		for (int j = 0; j<n; j++) cout<<dis[i][j]<<" ";
		cout<<endl;
	}
	system("pause");
	*/
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++)
			if (mat[i][j]!=dis[i][j]){
				cout<<"NO"<<endl;
				return 0;
			}
	cout<<"YES"<<endl;
}