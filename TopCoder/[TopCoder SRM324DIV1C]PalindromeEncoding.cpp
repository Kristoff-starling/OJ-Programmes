#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
	bool f;char ch;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

char s[148];int len;

class PalindromeEncoding
{
	public:
		inline int getLength(string s)
		{
			len=int(s.size())-1;
			int pt=1;while (pt<=len && s[pt]==s[0]) pt++;
			if (pt>len) return 1;
			int ans=2;
			while (pt<=len-1 && s[pt]!=s[pt+1]) ans++,pt++;
			return ans;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	string ss;PalindromeEncoding A;
	while (cin>>ss) cout<<A.getLength(ss)<<endl;
	return 0;
}*/
