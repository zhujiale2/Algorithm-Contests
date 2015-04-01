#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 5050;

int n, T, t[MAXN];
double dp[2][MAXN], p[MAXN];
int P[MAXN];
double factor[101][MAXN];
double *f[2];

int main()
{
    scanf("%d%d", &n, &T);
    for(int i = 1; i<=n; i++){
        scanf("%d%d", &P[i], &t[i]);
        p[i] = P[i]/100.0;
    }
    double res = 0; 
    f[0] = dp[0];
    f[1] = dp[1];
    for (int k = 0; k<=T; k++) f[0][k] = 1;
    for (int i = 0; i<=100; i++){
        factor[i][0] = 1;
        double K = 1.0-i/100.0;
        for (int k = 1; k<=T; k++) {
            factor[i][k] = factor[i][k-1]*K;
        }
    }
    for (int i = 1; i<=n; i++) {
        double delta = 0;
        double K = 1-p[i];
        f[1][0] = 0;
        for (int j = 1; j<t[i]; j++) {
            delta = delta*K + f[0][j-1]*p[i];
            f[1][j] = delta;
        }
        for (int j = t[i]; j<=T; j++) {
            double L = factor[P[i]][t[i]-1]*f[0][j-t[i]];
            delta = delta*K + (f[0][j-1]-L)*p[i];
            f[1][j] = delta + L;
        }
        res += (i-1)*(f[0][T]-f[1][T]);
        swap(f[0],f[1]);
    }
    res += n*f[0][T];
    printf("%.6f\n", res);
}