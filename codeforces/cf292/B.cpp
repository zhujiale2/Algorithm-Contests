#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2015;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

char mat[MAXN][MAXN];
int deg[MAXN][MAXN];
vector <int> e[MAXN];
char res[MAXN][MAXN];
queue <pair<int,int>> Q;

void renew(int x, int y)
{
	for (int k = 0; k<4; k++) {
		int tx = x+dx[k];
		int ty = y+dy[k];
		if (res[tx][ty]==0 && mat[tx][ty]=='.') {
			deg[tx][ty]--;
			if (deg[tx][ty]==1) Q.push({tx,ty});
		} 
	}
}

void put(int x1, int y1, int x2, int y2)
{
	if (x1!=x2 && x1>x2 || y1!=y2 && y1>y2){
		swap(x1,x2); swap(y1,y2);
	}
	if (x1!=x2) {
		res[x1][y1] = '^'; res[x2][y2] = 'v';
	}
	else {
		res[x1][y1] = '<'; res[x2][y2] = '>';	
	}
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	getchar();
	memset(res, 0, sizeof(res));
	for (int i = 1; i<=n; i++) {
		gets(mat[i]+1);
	}
	for (int i = 1; i<=n; i++)
		for (int j = 1; j<=m; j++)
		{
			if (mat[i][j]=='.') {
				for (int k = 0; k<4; k++) {
					int nx = i+dx[k];
					int ny = j+dy[k];
					if (mat[nx][ny]=='.') deg[i][j]++;
				}
				if (deg[i][j]==1) Q.push({i,j});
			}
		}
	while (!Q.empty()) {
		int nx = Q.front().first;
		int ny = Q.front().second;
		Q.pop();
		//cerr<<nx<<"-"<<ny<<endl;
		if (res[nx][ny]!=0) continue;
		for (int k = 0; k<4; k++) {
			int tx = nx+dx[k];
			int ty = ny+dy[k];
			if (mat[tx][ty]=='.' && res[tx][ty]==0) {
				deg[tx][ty]--;
				put(nx,ny,tx,ty);
				renew(nx,ny);
				renew(tx,ty);
			}
		}
	}
	for (int i = 1; i<=n; i++)
		for (int j = 1; j<=m; j++)
			if (res[i][j]==0 && mat[i][j]=='.') {
				puts("Not unique");
				return 0;
			}
	for (int i = 1; i<=n; i++) {
		for (int j = 1; j<=m; j++) {
			if (mat[i][j]=='*') putchar('*');
			else putchar(res[i][j]);
		}
		puts("");
	}
}
