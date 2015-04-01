#include <bits/stdc++.h>

using namespace std;

string team1, team2;
int cnt[2][100];

struct node{
    int times, number;
    char x, z;
};

node read[1000];

int cmp(const node &a, const node &b)
{
    if (a.times<b.times) return 1;
    else return 0;
}

int main()
{
    cin>>team1;
    cin>>team2;
    int n;
    cin>>n;
    for (int i = 1; i<=n; i++) {
        cin>>read[i].times>>read[i].x>>read[i].number>>read[i].z;
    }
    sort(read+1, read+n+1, cmp);
    for (int i = 1; i<=n; i++) {
        int times = read[i].times;
        char x = read[i].x;
        int number = read[i].number;
        char z = read[i].z;
        if (z=='r') {
            if (x=='h') {
                cnt[0][number] += 2;
                if (cnt[0][number]==2 || cnt[0][number]==3) {
                    cout<<team1<<" "<<number<<" "<<times<<endl;
                }
            }
            else {
                cnt[1][number] += 2;
                if (cnt[1][number]==2 || cnt[1][number]==3) {
                    cout<<team2<<" "<<number<<" "<<times<<endl;
                }
            }
        }
        else if (z=='y') {
            if (x=='h') {
                cnt[0][number]++;
                if (cnt[0][number]==2) {
                    cout<<team1<<" "<<number<<" "<<times<<endl;
                }
            }
            else {
                cnt[1][number]++;
                if (cnt[1][number]==2) {
                    cout<<team2<<" "<<number<<" "<<times<<endl;
                }
            }
        }
    }
}