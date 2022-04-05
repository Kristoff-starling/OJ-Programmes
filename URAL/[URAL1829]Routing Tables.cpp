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
#include <cassert>
using namespace std;

const int MOD=1e9+7;
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

struct node
{
	LL num;
	int next[2];
	bool issame;LL Num;
}trie[2][1600048];int tot[5];

inline void Insert(int ind,LL x,int valid,LL num)
{
	int i,to,cur=1;
	for (i=31;i>=31-valid+1;i--)
	{
		to=(x&(1ll<<i)?1:0);
		if (!trie[ind][cur].next[to])
		{
			trie[ind][cur].next[to]=++tot[ind];
			trie[ind][tot[ind]].num=-1;
			trie[ind][tot[ind]].next[0]=trie[ind][tot[ind]].next[1]=0;
		}
		cur=trie[ind][cur].next[to];
		if (i==31-valid+1) trie[ind][cur].num=num;
	}
}

int n,m;

inline int STRING_TO_NUM(string s)
{
	int res=0,i;
	for (i=0;i<int(s.size());i++)
		res=res*10+s[i]-'0';
	return res;
}

inline LL STRING_TO_INT(string s)
{
	LL p[10],pos=0,pos1,i;
	s+=".";
	for (i=1;i<=4;i++)
	{
		pos1=s.find('.',pos);
		p[i]=STRING_TO_NUM(s.substr(pos,pos1-pos));
		pos=pos1+1;
	}
	return p[1]*(1ll<<24)+p[2]*(1ll<<16)+p[3]*(1ll<<8)+p[4];
}

inline int count(LL x)
{
	int res=32,pt=0;
	while (!(x&(1ll<<pt)) && res) res--,pt++;
	return res;
}

inline void dfs(int ind,int cur,LL hsh)
{
	int i,to;LL tohsh;
	for (i=0;i<=1;i++)
		if (trie[ind][cur].next[i])
		{
			to=trie[ind][cur].next[i];
			tohsh=(trie[ind][to].num==-1?hsh:trie[ind][to].num);
			dfs(ind,to,tohsh);
		}
	if (!trie[ind][cur].next[0] && !trie[ind][cur].next[1])
	{
		trie[ind][cur].issame=true;
		trie[ind][cur].Num=hsh;
		return;
	}
	if (trie[ind][cur].next[0] && trie[ind][cur].next[1])
	{
		int to1=trie[ind][cur].next[0],to2=trie[ind][cur].next[1];
		if (!trie[ind][to1].issame || !trie[ind][to2].issame || trie[ind][to1].Num!=trie[ind][to2].Num)
			trie[ind][cur].issame=false;
		else
			trie[ind][cur].issame=true,trie[ind][cur].Num=trie[ind][to1].Num;
		return;
	}
	to=(trie[ind][cur].next[0]?trie[ind][cur].next[0]:trie[ind][cur].next[1]);
	if (!trie[ind][to].issame || trie[ind][to].Num!=hsh)
		trie[ind][cur].issame=false;
	else
		trie[ind][cur].issame=true,trie[ind][cur].Num=hsh;
}

inline bool check(int cur1,LL hsh1,int cur2,LL hsh2,bool isend)
{
	if (trie[0][cur1].next[0] && trie[0][cur1].next[1]) return true;
	if (!trie[0][cur1].next[0])
	{
		if (isend)
			{if (hsh1!=hsh2) return false;}
		else
		{
			LL tohsh;int to;
			if (!trie[1][cur2].next[0]) 
				{tohsh=hsh2;}
			else
			{
				to=trie[1][cur2].next[0];
				if (!trie[1][to].issame) tohsh=-2; else tohsh=trie[1][to].Num;
			}
			if (tohsh!=hsh1) return false;
		}
	}
	if (!trie[0][cur1].next[1])
	{
		if (isend)
			{if (hsh1!=hsh2) return false;}
		else
		{
			LL tohsh;int to;
			if (!trie[1][cur2].next[1]) 
				{tohsh=hsh2;}
			else
			{
				to=trie[1][cur2].next[1];
				if (!trie[1][to].issame) tohsh=-2; else tohsh=trie[1][to].Num;
			}
			if (tohsh!=hsh1) return false;
		}
	}
	return true;
}

inline bool compare_trie(int cur1,LL hsh1,int cur2,LL hsh2,bool isend)
{
	if (!check(cur1,hsh1,cur2,hsh2,isend)) return false;
	int i,to1,to2;bool tostatus;LL tohsh1,tohsh2;
	for (i=0;i<=1;i++)
		if (trie[0][cur1].next[i])
		{
			to1=trie[0][cur1].next[i];
			tohsh1=(trie[0][to1].num==-1?hsh1:trie[0][to1].num);
			if (isend || (!isend && !trie[1][cur2].next[i]))
				to2=cur2,tohsh2=hsh2,tostatus=true;
			else
				to2=trie[1][cur2].next[i],tohsh2=(trie[1][to2].num==-1?hsh2:trie[1][to2].num),tostatus=false;
			if (!compare_trie(to1,tohsh1,to2,tohsh2,tostatus)) return false;
		}
	return true;
}

int main ()
{
	ios::sync_with_stdio(false);
	int i;LL x,Mask,hsh;string s;
	cin>>n;
	tot[0]=1;trie[0][1].num=-1;trie[0][1].next[0]=trie[0][1].next[1]=0;
	for (i=1;i<=n;i++)
	{
		cin>>s;x=STRING_TO_INT(s);
		cin>>s;Mask=STRING_TO_INT(s);
		cin>>s;hsh=STRING_TO_INT(s);
		int valid=count(Mask);
		Insert(0,x&Mask,valid,hsh);
	}
	cin>>m;
	tot[1]=1;trie[1][1].num=-1;trie[1][1].next[0]=trie[1][1].next[1]=0;
	for (i=1;i<=m;i++)
	{
		cin>>s;x=STRING_TO_INT(s);
		cin>>s;Mask=STRING_TO_INT(s);
		cin>>s;hsh=STRING_TO_INT(s);
		int valid=count(Mask);
		Insert(1,x&Mask,valid,hsh);
	}
	dfs(0,1,-1);dfs(1,1,-1);
	if (!compare_trie(1,-1,1,-1,false)) {printf("NO\n");return 0;}
	printf("YES\n");
	return 0;
}
/*
4
192.168.0.0 255.255.255.0 192.168.14.1
192.168.1.0 255.255.255.0 192.168.14.1
192.168.2.0 255.255.255.0 192.168.14.2
192.168.3.0 255.255.255.0 192.168.14.2
2
192.168.0.0 255.255.252.0 192.168.14.1
192.168.2.0 255.255.254.0 192.168.14.2
*/
