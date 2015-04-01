#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100100;

int n, winner;
int a[MAXN], b[MAXN], sa[MAXN], sb[MAXN];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i<=n; i++) {
        int tmp;
        scanf("%d", &tmp);
        if (tmp==1) a[i] = 1;
        else b[i] = 1;
        if (i==n) {
            winner = tmp-1;
        }
    }
    for (int i = 1; i<=n; i++) {
        sa[i] = sa[i-1]+a[i];
        sb[i] = sb[i-1]+b[i];
    }
    vector < pair<int,int> > res;
    for (int t = 1; t<=(winner==0 ? sa[n] : sb[n]); t++) {
        int w[2] = {0};
        int pointer = 1;
        int flag = 0;
        int s = 0;
        while (pointer<=n) {
            int l = pointer, r = n, mid, ans = n+1;
            while (l<=r) {
                mid = (l+r)/2;
                if (sa[mid]-sa[pointer-1]>=t || sb[mid]-sb[pointer-1]>=t){
                    r = mid-1;
                    ans = min(ans,mid);
                }
                else {
                    l = mid+1;
                }
            }
            if (ans==n+1) {
                flag = 1;
                break;
            }
            else {
                if (sa[ans]-sa[pointer-1]==t) w[0]++;
                else w[1]++;
                pointer = ans+1;
            }
        }
        if (w[winner]>w[1-winner]) {
            s = w[winner];
        }
        else {
            flag = 1;
        }
        if (!flag) {
            res.push_back(make_pair(s,t));
        }
    }
    sort(res.begin(), res.end());
    cout<<res.size()<<endl;
    for (int i = 0; i<res.size(); i++) {
        cout<<res[i].first<<" "<<res[i].second<<endl;
    }
//  while (1);
}