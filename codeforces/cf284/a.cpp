#include <bits/stdc++.h>
#define DEBUG

using namespace std;

long long sig(long long x)
{
    if (x>0) return 1;
    else return -1;
}

int main()
{
    long long X1, Y1, X2, Y2;
    cin>>X1>>Y1>>X2>>Y2;
    int n;
    cin>>n;
    int res = 0;
    for (int i = 1; i<=n; i++) {
        long long a, b, c;
        cin>>a>>b>>c;
        if (sig(a*X1+b*Y1+c)*sig(a*X2+b*Y2+c)==-1) res++;
    }
    cout<<res<<endl;
    //while (1);
}