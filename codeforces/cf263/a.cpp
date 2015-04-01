#include <bits/stdc++.h>

using namespace std;

vector <long long> a;

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i<=n; i++){
        long long tmp;
        scanf("%I64d", &tmp);
        a.push_back(tmp);
    }
    sort(a.begin(), a.end());
    long long res = 0;
    //a[a.size()-1] = 0;
    for (int i = a.size()-2; i>=0; i--){
        a[i] += a[i+1];
        //cout<<a[i]<<endl;
    }
    for (int i = max(0,(int)a.size()-2); i>=0; i--){
        //cout<<"00"<<a[i]<<endl;
        if (i==0) res += a[i]*2;
        else res += a[i];
        //cout<<res<<endl;
    }
    if (a.size()==1) res -= a[0];
    cout<<res<<endl;
}