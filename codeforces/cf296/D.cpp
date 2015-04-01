#include <bits/stdc++.h>

using namespace std;

const int MAXN = 201000;
const char alpha[4] = {'A','T','C','G'};

const long double PI = acos(0.0) * 2.0;
vector <double> C[4];

typedef complex<double> CD;

//来自刘汝佳白书
// Cooley-Tukey的FFT算法，迭代实现。inverse = false时计算逆FFT
inline void FFT(vector<CD> &a, bool inverse) {
    int n = a.size();
    for(int i = 0, j = 0; i < n; i++) {
        if(j > i) swap(a[i], a[j]);
        int k = n;
        while(j & (k >>= 1)) j &= ~k;
        j |= k;
    }
    double pi = inverse ? -PI : PI;
    for(int step = 1; step < n; step <<= 1) {
        double alpha = pi / step;
        // 计算omega^k. 这个方法效率低，但如果用每次乘omega的方法递推会有精度问题。
        // 系数为整数运算时可以采用下面代码替换注释后面的两行进行加速
        
          CD omegak = exp(CD(0,0));
          CD omega = exp(CD(0, alpha));
          for(int k = 0; k < step; k++) {
            if (k!=0) omegak *= omega;
        
        //for(int k = 0; k < step; k++) {
              //CD omegak = exp(CD(0, alpha*k)); 
            for(int Ek = k; Ek < n; Ek += step << 1) { 
                int Ok = Ek + step; 
                CD t = omegak * a[Ok];
                a[Ok] = a[Ek] - t;
                a[Ek] += t;       
            }
        }
    }
    if(inverse) for(int i = 0; i < n; i++) a[i] /= n;
}

// 用Cooley-Tukey的FFT算法实现的快速多项式乘法
// 重载了两个vector<double>的乘法
// 若需要整数系数需要自行对double进行四舍五入
inline vector<double> operator * (const vector<double>& v1, const vector<double>& v2) {
    int s1 = v1.size(), s2 = v2.size(), S = 2;
    while(S < s1 + s2) S <<= 1;
    vector<CD> a(S,0), b(S,0); 
    // 把FFT的输入长度补成2的幂，不小于v1和v2的长度之和
    for(int i = 0; i < s1; i++) a[i] = v1[i];
    FFT(a, false);
    for(int i = 0; i < s2; i++) b[i] = v2[i];
    FFT(b, false);
    for(int i = 0; i < S; i++) a[i] *= b[i];
    FFT(a, true);
    vector<double> res(s1 + s2 - 1);
    for(int i = 0; i < s1 + s2 - 1; i++) res[i] = a[i].real(); // 虚部均为0
    return res;
}

int n,m,k;
string s1, s2;
bool v[4][MAXN];

void print(vector <double> x)
{
    for (int i = 0; i<x.size(); i++)
        cerr<<(int)(x[i]+1e-5);
    cerr<<endl;
}

void work(char x, int t)
{
    C[t].clear();
    vector <double> B(m);
    vector <double> A(n);
    for (int i = 0; i<m; i++) {
        if (s2[i]==x) B[i] = 1; 
    }
    int last = 0;
    for (int i = 0; i<n; i++) {
        if (s1[i]==x) {
            for (int j = max(last,i-k); j<=min(i+k,n-1); j++) {
                A[j] = 1;
            }
            last = i+k;
        }
    }
    reverse(A.begin(),A.end());
    //cerr<<"====="<<endl;
    //cerr<<"A:"<<endl;
    //print(A);
    //cerr<<"B:"<<endl;
    //print(B);
    
    C[t] = A*B;
    //cerr<<"C:"<<endl;
    //print(C[t]);
    //cerr<<"****"<<endl;
}

int main()
{
    scanf("%d%d%d", &n,&m,&k);
    cin>>s1>>s2;
    set <char> S;
    for (int i = 0; i<s2.size(); i++) S.insert(s2[i]);
    for (int i = 0; i<4; i++) work(alpha[i],i);
    vector <int> res(n,0);
    for (int i = 0; i<4; i++) {
        if (S.find(alpha[i])==S.end()) continue;
        for (int j = 0; j<n; j++)
            res[j] += (int)(C[i][j]+1e-5);
    }
    int cnt = 0;
    for (int i = 0; i<n; i++) if (res[i]==m) cnt++;
    cout<<cnt<<endl;
}