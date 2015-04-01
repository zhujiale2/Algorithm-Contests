#include <bits/stdc++.h>

using namespace std;

//#define DEBUG

const int MAXN = 500;

int n;
int l[MAXN], c[MAXN];

int work(int x)
{
    if (l[x]==1) return c[x];
    unsigned int f[1<<10];
    for (int mask = 0; mask<1<<10; mask++) f[mask] = INT_MAX;
    vector <int> p;
    int tmp = l[x];
    for (int i = 2; i*i<=tmp; i++) {
        if (tmp%i==0) p.push_back(i);
        while (tmp%i==0) tmp /= i;
    }
    if (tmp!=1) p.push_back(tmp);
    int cnt = p.size();
    f[0] = c[x];
    for (int i = 1; i<=n; i++) {
        if (i==x) continue;
        int tmp = 0;
        for (int k = 0; k<cnt; k++) {
            if (l[i]%p[k]!=0) tmp += 1<<k;
        }
        for (int mask = (1<<cnt)-1; mask>=0; mask--) {
            f[mask|tmp] = min(f[mask|tmp],f[mask]+c[i]);
        }
    }
    return f[(1<<cnt)-1];
}