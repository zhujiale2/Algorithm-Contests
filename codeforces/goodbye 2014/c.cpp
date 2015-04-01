#include <bits/stdc++.h>

using namespace std;

const int MAXN = 400;

int n, m;
int w[600], b[1500], a[600];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i<=n; i++) scanf("%d", w+i);
    int cnt = 1;
    int v[600] = {0};
    for (int i = 1; i<=m; i++) {
        scanf("%d", b+i);
        int x = b[i];
        if (!v[x]) {
            a[cnt] = x;
            v[x] = 1;
            cnt++;
        }
    }
    int res = 0;
    for (int i = 1; i<=m; i++) {
        int x = b[i];
        int index = 0;
        for (int k = 1; k<=n; k++) {
            if (a[k]==x) {
                index = k;
                break;
            }
        }
        for (int k = index; k>=2; k--) {
            a[k] = a[k-1];
            res += w[a[k]];
        }
        a[1] = x;
    }
    cout<<res<<endl;
    //while (1);
}