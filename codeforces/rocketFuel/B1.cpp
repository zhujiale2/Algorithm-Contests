#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

int n, m;
vector <int> a;
vector <pair<int,int>> cnt;

bool cmp(const pair<int,int> &a, const pair<int,int> &b)
{
    if (a.first>b.first) return true;
    else if (a.first==b.first && a.second<b.second) return true;
    else return false;
}

int main()
{
    cin>>n>>m;
    a.push_back(0);
    for (int i = 1; i<=n; i++) a.push_back(i);
    int order = 0;
    do{
        int res = 0;
        for (int i = 1; i<=n; i++) {
            for (int j = i; j<=n; j++) {
                int tmp = INT_MAX;
                for (int k = i; k<=j; k++) {
                    tmp = min(tmp,a[k]);
                }
                res += tmp;
            }
        }
        
        cerr<<"res : "<<res<<"   ";
        for (int i = 1; i<n; i++) cout<<a[i]<<" ";
        cout<<a[n]<<endl; 
        
        cnt.push_back({res,order++});
    } while (next_permutation(a.begin()+1,a.end()));
    sort(cnt.begin(),cnt.end(),cmp);
/*
    int last = -1;
    int cnti = 0;
    for (int i = 0; i<cnt.size(); i++) {
        if (cnt[i].first!=last) {
            cout<<"cnt : "<<cnti<<endl;
            cnti = 0;
            cout<<cnt[i].first<<endl;
            last = cnt[i].first;
        }
        cnti++;
    }
    cout<<"cnt : "<<cnti<<endl;
*/
    int get = cnt[m-1].second;
    //cerr<<"get : "<<get<<endl;

    for (int i = 1; i<=n; i++) a[i] = i;
    while (get--){
        next_permutation(a.begin()+1,a.end());
    }
    for (int i = 1; i<n; i++) cout<<a[i]<<" ";
    cout<<a[n]<<endl;
    return 0;
}