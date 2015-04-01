#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300000;

int top;
pair <int,int> s[MAXN];
vector <pair<int,int>> A;

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i<=n; i++) {
        pair <int,int> tmp;
        scanf("%d%d", &tmp.first, &tmp.second);
        A.push_back(tmp);
    }
    sort(A.begin(),A.end());
    for (int i = 0; i<n; i++) {
        pair <int,int> now = A[i];
        if (top==0) {
            s[top] = now;
            top++;
        } else {
            //cerr<<s[top-1].first+s[top-1].second<<" "<<now.first<<endl;
            if (s[top-1].first+s[top-1].second+now.second>now.first) {
                if (now.first+now.second<s[top-1].first+s[top-1].second) {
                    s[top-1] = now;
                }
            } else {
                s[top] = now;
                top++;
            }
        }
    }
    cout<<top<<endl;
}