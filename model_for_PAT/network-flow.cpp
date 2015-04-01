#include <queue>
#include <cstdio>
#include <string>
#include <vector>
#include <climits>
#include <iostream>
#include <map>

using namespace std;

const int MAXN = 2000;

map <int,int> E[MAXN];

int maxflow(int s, int t)
{
    int res = 0;
    while (1) {
        queue <int> q;
        int pre[MAXN] = {0};
        int vis[MAXN] = {0};
        q.push(s);
        vis[s] = 1;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (map <int,int>::iterator it = E[now].begin(); it!=E[now].end(); it++) {
                int next = it->first;
                int cap = it->second;
                if (!vis[next] && cap>0) {
                    q.push(next);
                    vis[next] = 1;
                    pre[next] = now;
                }
            }
        }
        if (!vis[t]) break;
        int y = t;
        int delta = INT_MAX;
        while (pre[y]!=0) {
            int x = pre[y];
            delta = min(delta,E[x][y]);
            y = x;
        }
        y = t;
        while (pre[y]!=0) {
            int x = pre[y];
            E[x][y] -= delta;
            E[y][x] += delta;
            y = x;
        }
        res += delta;
    }
    return res;
}

int main()
{
    int m,n;
    while (scanf("%d%d", &m,&n)==2) {
        for (int i = 1; i<=n; i++) E[i].clear();
        for (int i = 1; i<=m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            E[a][b] += c;
        }
        cout<<maxflow(1,n)<<endl;
    }    
}