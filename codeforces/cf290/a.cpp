#include <bits/stdc++.h>

using namespace std;

//#define DEBUG

int n;
string s[200];
vector <int> E[26];
int ld[26];

int main() 
{
    cin>>n;
    for (int i = 1; i<=n; i++) cin>>s[i];
    for (int i = 1; i<=n; i++){
        //cerr<<i<<endl;
        for (int j = i+1; j<=n; j++) {
            int k;
            for (k = 0; k<min(s[i].size(),s[j].size()) && s[i][k]==s[j][k]; k++);
            if (k==min(s[i].size(),s[j].size())) {
                if (s[i].size()>s[j].size()) {
                    cout<<"Impossible"<<endl;
                    return 0;
                }
                else continue;
            }
            else {
                E[s[i][k]-'a'].push_back(s[j][k]-'a');
                ld[s[j][k]-'a']++;
            }
        }
    }
    
    queue <int> Q;
    for (int i = 0; i<26; i++) {
        if (ld[i]==0) Q.push(i);
    }
    string res = "";
    while (!Q.empty()) {
        int x = Q.front();
        //cout<<x<<endl;
        Q.pop();
        res.push_back(x+'a');
        for (int i = 0; i<E[x].size(); i++) {
            int y = E[x][i];
            ld[y]--;
            if (ld[y]==0) Q.push(y);
        }
    }
    if (res.size()==26) cout<<res<<endl;
    else cout<<"Impossible"<<endl;
    //while (1);
}