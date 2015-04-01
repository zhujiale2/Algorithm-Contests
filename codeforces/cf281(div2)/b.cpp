#include <bits/stdc++.h>

using namespace std;

long long p1, p2;
vector <long long> s1, s2;
int last;

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i<=n; i++) {
        int tmp;
        scanf("%d", &tmp);
        if (tmp>0) {
            last = 1;
            p1 += tmp;
            s1.push_back(tmp);
        }
        else {
            last = 2;
            tmp = -tmp;
            p2 += tmp;
            s2.push_back(tmp);
        }
    }
    if (p1>p2) {
        cout<<"first"<<endl;
    }
    else if (p1<p2) {
        cout<<"second"<<endl;
    }
    else {
        if (s1>s2) {
            cout<<"first"<<endl;
        }
        else if (s1<s2) {
            cout<<"second"<<endl;
        }
        else {
            if (last==1) {
                cout<<"first"<<endl;
            }
            else {
                cout<<"second"<<endl;
            }
        }
    }
}