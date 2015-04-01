#include <bits/stdc++.h>

using namespace std;

class ThePermutationGameDiv2 {
public:
	long long findMin(int);
};

long long gcd(long long a, long long b)
{
	long long r = a%b;
	while (r!=0) {
		a = b;
		b = r;
		r = a%b;
	}
	return b;
}

long long work(long long a, long long b)
{
	return a*b/gcd(a,b);
}

long long ThePermutationGameDiv2::findMin(int N) {
	long long res = 1;
	long long t = 1;
	while (t<=N) {
		res = work(res,t);
		t++;
	}
	return res;
}


//Powered by [KawigiEdit] 2.0!