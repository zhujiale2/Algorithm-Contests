#include <bits/stdc++.h>

//#define DEBUG

using namespace std;

const int MAXN = 1000000;

int n;
int v[MAXN], s[MAXN];
queue <int> Q;
vector <pair <int,int>> E;

int main()
{
    scanf("%d", &n);
    for (int i = 0; i<n; i++) {
        scanf("%d%d", v+i, s+i);
    }
    for (int i = 0; i<n; i++) {
        if (v[i]==1) {
            Q.push(i);
        }
    }
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        if (v[x]==0) continue;
        int y = s[x];
        v[y]--;
        s[y] ^= x;
        E.push_back({x,y});
        if (v[y]==1) Q.push(y);
    }
    printf("%d\n", E.size());
    for (int i = 0; i<E.size(); i++) {
        printf("%d %d\n", E[i].first, E[i].second);
    }
#ifdef DEBUG
    while (1);
#endif
}