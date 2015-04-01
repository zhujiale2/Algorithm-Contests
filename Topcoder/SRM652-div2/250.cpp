#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class ValueOfString {
public:
	int findValue(string);
};

int ValueOfString::findValue(string s) {
	int res = 0;
	for (int i = 0; i<s.size(); i++) {
		int cnt = 0;
		for (int j = 0; j<s.size(); j++) {
			if (s[i]>=s[j]) cnt++;
		}
		res += cnt*(s[i]-'a'+1);
	}
	return res;
}


//Powered by [KawigiEdit] 2.0!