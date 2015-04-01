#include <bits/stdc++.h>
#define DEBUG

using namespace std;

const int MAXN = 1500;

int a[MAXN];
int mat[MAXN][MAXN];
int flow[MAXN][MAXN];

const int INF = 1000000000;

int maxFlow(int n, const int mat[][MAXN], int source, int sink, int flow[][MAXN]) {
    int pre[MAXN], que[MAXN], d[MAXN], p, q, t, i, j;
    if (source == sink) {
        return INF;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; flow[i][j++] = 0);
    }
    while (true) {
        for (i = 0; i < n; pre[i++] = 0);
        pre[t = source] = source + 1;
        d[t] = INF;
        for (p = q = 0; p <= q && !pre[sink]; t = que[p++]) {
            for (i = 0; i < n; i++) {
                if (!pre[i] && (j = mat[t][i] - flow[t][i])) {
                    pre[que[q++] = i] = t + 1;
                    d[i] = d[t] < j ? d[t] : j;
                } else if (!pre[i] && (j = flow[i][t])) {
                    pre[que[q++] = i] = -t - 1;
                    d[i] = d[t] < j ? d[t] : j;
                } 
            }
        }
        if (!pre[sink]) {
            break;
        }
        for (i = sink; i != source;) {
            if (pre[i] > 0) {
                flow[pre[i] - 1][i] += d[sink];
                i = pre[i] - 1;
            } else {
                flow[i][-pre[i] - 1] -= d[sink];
                i = -pre[i] - 1;
            } 
        }
    }
    for (j = i = 0; i < n; j += flow[source][i++]);
    return j;
}

map <int,int> p[MAXN];
pair <int,int> bound[MAXN];
int node[MAXN];

void work(int index)
{
    int x = a[index];
    if (x<2) return;
    int i = 2;
    while (x>1 && i<=min(int(sqrt(x)+1.5),x)) {
        if (x%i==0) {
            x /= i;
            p[index][i]++;
        }
        else i++;
    }
    if (x>1) p[index][x]++;
}

int main()
{
    int n, m;
    cin>>n>>m;
    int N = 0;
    for (int i = 1; i<=n; i++) {
        cin>>a[i];
        work(i);
        N += p[i].size();
    }
    int partA = 0, partB = 0;
    for (int i = 1; i<=n; i+=2) {
        bound[i].first = partA+1;
        for (auto it = p[i].begin(); it!=p[i].end(); it++) {
            mat[0][++partA] = it->second;
            node[partA] = it->first;
        }
        bound[i].second = partA;
    }
    for (int i = 2; i<=n; i+=2) {
        bound[i].first = partA+partB+1;
        for (auto it = p[i].begin(); it!=p[i].end(); it++) {
            mat[++partB+partA][N+1] = it->second;
            node[partA+partB] = it->first;
        }
        bound[i].second = partA+partB;
    }
    for (int i = 1; i<=m; i++) {
        int x, y;
        cin>>x>>y;
        if (x%2==0) swap(x,y);
        for (int j = bound[x].first; j<=bound[x].second; j++) {
            for (int k = bound[y].first; k<=bound[y].second; k++) {
                if (node[j]==node[k]) mat[j][k] = 1000000;
            }
        }
    }
    int res = maxFlow(N+2, mat, 0, N+1, flow);
    cout<<res<<endl;
    //while (1);
}