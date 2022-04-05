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

const int MOD=1e9+7;
const LL LINF=2e16;
const int INF=2e9;
const int magic=348;
const double eps=1e-10;
const double pi=acos(-1);

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

char s[5048];int len;
string s1,s2;

inline string solve(int left,int right)
{
	if (left>right) return "()";
	int i,lastpos=left,cnt=0;
	vector<string> son;son.clear();
	for (i=left;i<=right;i++)
	{
		if (s[i]=='1') cnt--; else cnt++;
		if (!cnt) son.pb(solve(lastpos+1,i-1)),lastpos=i+1;
	}
	sort(son.begin(),son.end());
	string res="(";
	for (i=0;i<int(son.size());i++) res+=son[i];
	res+=")";
	return res;
}

int main ()
{
	int ca;cin>>ca;
	while (ca--)
	{
		memset(s,'\0',sizeof(s));
		scanf("%s",s+1);len=strlen(s+1);
		s1=solve(1,len);
		memset(s,'\0',sizeof(s));
		scanf("%s",s+1);len=strlen(s+1);
		s2=solve(1,len);
		if (s1==s2) printf("same\n"); else printf("different\n");
	}
	return 0;
}
