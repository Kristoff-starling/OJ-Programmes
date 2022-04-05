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
const LB eps=1e-10;
const LB pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

char s[1048];int len;

struct node
{
	int constant;
	int sign;
	int var;
	int lson,rson;
}tree[100048];int tot=0;
int root;

inline int CreateAlpha(int ind)
{
	++tot;tree[tot].var=ind;
	return tot;
}
inline int CreateSign(int pos)
{
	++tot;
	if (s[pos]=='A') tree[tot].sign=1;
	if (s[pos]=='O') tree[tot].sign=2;
	if (s[pos]=='N') tree[tot].sign=3;
	return tot;
}
inline int CreateConstant(int ind)
{
	++tot;tree[tot].constant=ind;
	return tot;
}

inline pair<string,int> getword(int pt)
{
	while (s[pt]==' ') pt++;string res="";
	while (s[pt]!=' ' && s[pt]!='(' && s[pt]!=')') res=res+string(1,s[pt++]);
	return mp(res,pt);
}

inline int construct(int left,int right)
{
	if (left==right) return CreateAlpha(s[left]-'A'+1);
	if (right-left+1==4 && s[left]=='T') return CreateConstant(1);
	if (right-left+1==5 && s[left]=='F') return CreateConstant(0);
	int i,pt=left,pt2;pair<string,int> res;int rt=0,rt1,tmp,bc=0,si=0;
	if (s[left]=='(' && s[right]==')')
	{
		for (i=left;i<=right;i++)
		{
			if (s[i]=='(') bc++;
			if (s[i]==')') bc--;
			if (!bc) break;
		}
		if (i==right) return construct(left+1,right-1);
	}
	while (pt<=right)
	{
		bc=0;pt2=pt;
		do
		{
			res=getword(pt2);
			if (res.x=="(") {bc++;pt2=res.y;continue;}
			if (res.x==")") {bc--;pt2=res.y;continue;}
			if ((res.x=="AND" || res.x=="OR") && !bc) break;
			pt2=res.y;
		}
		while (pt2<=right);
		rt1=construct(pt,pt2-1);
		if (rt) tmp=ConstructSign(si),tree[tmp].lson=rt,tree[tmp].rson=rt1;
		rt=rt1;
		if (pt2>right) return rt;
		res=getword(pt2);
		if (res.x=="AND")
	}
}

int main ()
{
	cin.getline(s+1);len=strlen(s+1);
	root=construct(1,len);
}
