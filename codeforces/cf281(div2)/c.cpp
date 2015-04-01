#include <bits/stdc++.h>

using namespace std;

const int MAXN = 600000;

int s1[MAXN], s2[MAXN];


int main()
{
    int l1, l2;
    scanf("%d", &l1);
    for (int i = 1; i<=l1; i++) scanf("%d", s1+i);
    sort(s1+1, s1+l1+1);
    scanf("%d", &l2);
    for (int i = 1; i<=l2; i++) scanf("%d", s2+i);
    sort(s2+1, s2+l2+1);
    int ans1, ans2;
    ans1 = -1000000000;
    ans2 = 1000000000;
    int p1, p2 = 1;
    for (p1 = 1; p1<=l1; p1++) {
        while (s2[p2]<s1[p1] && p2<=l2) p2++;
        if (((p1-1)-(p2-1))*2 + ((l1-p1+1)-(l2-p2+1))*3 > ans1-ans2) {
            ans1 = (p1-1)*2 + (l1-p1+1)*3;
            ans2 = (p2-1)*2 + (l2-p2+1)*3;
        }
    }
    if (l1*2-l2*2>ans1-ans2) {
        ans1 = l1*2;
        ans2 = l2*2;
    }
    cout<<ans1<<":"<<ans2<<endl;
}