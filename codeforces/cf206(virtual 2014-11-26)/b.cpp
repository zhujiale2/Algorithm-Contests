#include <bits/stdc++.h>

using namespace std;

const int MAXN = 42;

int f[MAXN][1<<20];
bool v[MAXN][1<<20];
int n;
string S[MAXN];
int mat[MAXN][MAXN];
int table[MAXN][30];

int dfs(int step, int mask)
{
    if (v[step][mask]) return f[step][mask];
    v[step][mask] = true;
    int tmp = 0;
    for (int i = 0; i<n; i++) {
        if (mask&(1<<i)) {
            if (mat[i+1+max(step-n,0)][min(step,n)-i]==0) tmp++;
            if (mat[i+1+max(step-n,0)][min(step,n)-i]==1) tmp--;
            break;
        }
    }
    if (step==2*n-1){
        f[step][mask] = tmp;
        return f[step][mask];
    }
    if ((step&1)==1) f[step][mask] = 10000000;
    else f[step][mask] = -10000000;
    for (int i = 0; i<26; i++){
        int nxtMask = (step<n) ? (mask|(mask<<1)) : ((mask|(mask>>1))&((1<<(2*n-step))-1));
        int newMask = table[step+1][i] & nxtMask;
        if (newMask==0) continue;
        if ((step&1)==1) {
            f[step][mask] = min(f[step][mask], dfs(step+1,newMask)+tmp);
        }
        else {
            f[step][mask] = max(f[step][mask], dfs(step+1,newMask)+tmp);
        }
    }
    return f[step][mask];
}

int main()
{
    cin>>n;
    for (int i = 1; i<=n; i++) {
        cin>>S[i];
        for (int j = 1; j<=n; j++) {
            mat[i][j] = S[i][j-1]-'a';
        }
    }
    for (int i = 1; i<n*2; i++) {
        for (int j = 0; j<min(i,2*n-i); j++) {
            table[i][mat[j+1+max(i-n,0)][min(i,n)-j]] |= 1<<j;
        }
    }
    dfs(1,1);
    int res = f[1][1];
    //cout<<res<<endl;
    if (res>0) cout<<"FIRST"<<endl;
    else if (res==0) cout<<"DRAW"<<endl;
    else cout<<"SECOND"<<endl;
    //system("pause");
}