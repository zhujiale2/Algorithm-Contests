#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

long long n, m;
int a[MAXN];
vector <int> S;

long long mypow(int x)
{
    if (x==0 || x==1) return 1;
    else return 1LL<<x-1;
}

int main()
{
    cin>>n>>m;
    int l = 0, r = n-1;
    for (int i = 1; i<=n; i++) {
        if (m<=mypow(n-i)) a[l++] = i;
        else {
            a[r--] = i;
            m -= mypow(n-i);
        }
    }
    for (int i = 0; i<n-1; i++) cout<<a[i]<<" ";
    cout<<a[n-1]<<endl;
}