#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <sstream>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include <map>
#include <cctype>
#define LL long long
#define LB long double
#define mp make_pair
#define pb push_back
#define pf push_front 
#define Pair pair<int,int>
#define x first
#define y second
#define LOWBIT(X) x & (-x)
using namespace std;

const int MOD=1e6;
const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const double eps=1e-10;

inline int getint()
{
	char ch;bool f;int res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

inline LL getLL()
{
	char ch;bool f;LL res;
	while (!isdigit(ch=getchar()) && ch!='-') {}
	if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
	while (isdigit(ch=getchar())) res=res*10+ch-'0';
	return f?res:-res;
}

int n;
int cnt1,cnt2;

int main ()
{
	n=getint();
	int x;
	for (int i=1;i<=n;i++)
	{
		x=getint();
		if (x==1) cnt1++; else cnt2++;
	}
	int ans=0;
	if (cnt2<=cnt1)
	{
		ans+=cnt2;
		cnt1-=cnt2;
		ans+=cnt1/3;
		cout<<ans<<endl;
	}
	else
	{
		ans+=cnt1;
		cout<<ans<<endl;
	}
	return 0;
}
