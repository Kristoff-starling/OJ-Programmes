#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#define LL long long
#define LB long double
#define x first
#define y second
#define Pair pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define LOWBIT(x) x & (-x)
using namespace std;

const int MOD=1e9+9;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

class IncreasingLists
{
	int len;
	string dp[148];
	const string inf=string(100,'9');
	inline bool smaller(string s1,string s2)
	{
		int len1=int(s1.size()),len2=int(s2.size());
		if (len1<len2)
			for (register int i=1;i<=len2-len1;i++) s1="0"+s1;
		else
			for (register int i=1;i<=len1-len2;i++) s2="0"+s2;
		return s1<s2;
	}
	inline string work(string lim,string s)
	{
		if (s[0]=='0') return inf;
		int len1=int(lim.size()),len2=int(s.size()),i,j;
		for (i=0;i<len2;i++) if (s[i]==',') return inf;
		if (len1>len2) return inf;
		for (i=1;i<=len2-len1;i++) lim="0"+lim;
		if (lim[0]=='0')
		{
			if (s[0]=='?') s[0]='1';
			for (i=1;i<len2;i++) if (s[i]=='?') s[i]='0';
			return s;
		}
		int pos;
		for (i=0,pos=0;i<len2;i++,pos++)
			if (s[i]!='?')
			{
				if (s[i]>lim[i]) break;
				if (s[i]<lim[i])
				{
					bool f=false;
					for (j=i-1;j>=0;j--)
						if (s[j]=='?' && lim[j]!='9') {s[j]=lim[j]+1;f=true;pos=j;break;}
					if (f) break; else return inf;
				}
			}
		if (pos==len2)
		{
			bool f=false;
			for (i=pos-1;i>=0;i--)
				if (s[i]=='?' && lim[i]!='9') {s[i]=lim[i]+1;f=true;pos=i;break;}
			if (!f) return inf;
		}
		for (i=0;i<pos;i++) if (s[i]=='?') s[i]=lim[i];
		for (i=pos+1;i<len2;i++) if (s[i]=='?') s[i]='0';
		return s;
	}
	inline bool check(string s)
	{
		s+=",";
		dp[0]="";int i,j,len=int(s.size());
		for (i=1;i<=len;i++) dp[i]=inf;
		for (i=1;i<=len;i++)
		{
			if (s[i-1]==',' || s[i-1]=='?')
				for (j=i-2;j>=0;j--)
				{
					string res=work(dp[j],s.substr(j,i-j-1));
					if (smaller(res,dp[i])) dp[i]=res;
					if (j && s[j-1]==',') break;
				}
		}
		if (!smaller(dp[len],inf)) return false; else return true;
	}
	public:
		inline string makeIncreasingList(string s)
		{
			len=int(s.size());int i,j;
			if (!check(s)) return "impossible";
			for (i=0;i<len;i++)
				if (s[i]=='?')
				{
					s[i]=',';if (check(s)) continue;
					for (j=0;j<=9;j++) {s[i]='0'+j;if (check(s)) break;}
				}
			return s;
		}
};

/*---Debug Part---*/
/*
int main ()
{
	string ss;IncreasingLists A;
	while (cin>>ss) cout<<A.makeIncreasingList(ss)<<endl;
	return 0;
}
*/
