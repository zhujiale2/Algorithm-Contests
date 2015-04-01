#include <bits/stdc++.h>

using namespace std;

bool check[60][1<<20];
unsigned long long a[1<<20];
double f[1<<20];
char s[60][25];
int n, len;
int cnt[1<<20];

int main()
{
    for (int mask = 0; mask<1<<20; mask++) 
        cnt[mask] = __builtin_popcount(mask);
    cin>>n;
    for (int i = 1; i<=n; i++) scanf("%s", s[i]);
    len = strlen(s[1]);
    if (n==1){
        cout<<0<<endl;
        return 0;
    }
    for (int i = 1; i<=n; i++){
        for (int j = i+1; j<=n; j++){
            int mask = 0;
            for (int k = 0; k<len; k++){
                if (s[i][k]==s[j][k]) mask |= 1<<k;
                a[mask] |= (1ULL<<i)+(1ULL<<j);
            }
        }
    }
    for (int mask = (1<<len)-1; mask>=0; mask--)
        for (int j = 0; j<len; j++) 
            if (mask&(1<<j)) a[mask^(1<<j)] |= a[mask];
    f[0] = 1;
    for (int mask = 0; mask<1<<len; mask++){
        double dominator = len-cnt[mask];
        for (int x = 1; x<1<<len; x<<=1){
            if (mask&x) continue;
            f[mask|x] += f[mask]/dominator;
        }
    }
    double res = 0;
    for (int mask = 0; mask<1<<len; mask++){
        res += f[mask]*__builtin_popcountll(a[mask])/n;
    }
    printf("%.12f\n", res);
    //system("pause");
}