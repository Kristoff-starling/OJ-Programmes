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

const int MOD=1e9;
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

int n,m;
char s[48][48];

inline int mod(int x) {while (x>=MOD) x-=MOD;while (x<0) x+=MOD;return x;}

const int p=199991;
struct Hash
{
	int head[200048],nxt[180048],val[180048],tot=1;LL to[180048];
	inline void clear()
	{
		memset(head,0,sizeof(head));
		tot=1;
	}
	inline void Insert(LL x,int add)
	{
		LL pos=x%p;int i;LL y;bool f=false;
		for (i=head[pos];i;i=nxt[i])
		{
			y=to[i];
			if (y==x) {val[i]=mod(val[i]+add);f=true;break;}
		}
		if (!f) {to[++tot]=x;nxt[tot]=head[pos];head[pos]=tot;val[tot]=add;}
	}
}hsh[2];

inline int getplug(LL Mask,int pos) {return (Mask>>((pos-1)*4))&15ll;}
inline LL setplug(LL Mask,int pos,LL plug) {Mask|=(15ll<<((pos-1)*4));Mask^=(plug<<((pos-1)*4));Mask^=(15ll<<((pos-1)*4));return Mask;}
inline LL modify(LL Mask,int p1,int p2)
{
	for (register int i=1;i<=m+1;i++)
		if (getplug(Mask,i)==p2) Mask=setplug(Mask,i,p1);
	return Mask;
}

int lx,ly;
inline bool check(int i,int j,LL Mask,int plug)
{
	if (i==lx && j==ly) return true;int cnt=0;
	for (register int i=1;i<=m+1;i++)
		if (getplug(Mask,i)==plug) cnt++;
	return cnt;
}

inline LL getMask(LL Mask)
{
	int i,ind=0,table[48],plug;LL res=0;
	memset(table,0,sizeof(table));
	res=Mask;
	for (i=1;i<=m+1;i++)
	{
		plug=getplug(Mask,i);
		if (plug)
		{
			if (!table[plug]) table[plug]=++ind;
			res=setplug(res,i,table[plug]);
		}
	}
	return res;
}

int main ()
{
	int i,j,k,r;n=getint();m=getint();
	for (i=1;i<=n;i++) scanf("%s",s[i]+1);
	hsh[0].clear();hsh[1].clear();hsh[0].Insert(0,1);
	int cur=0,nxt=1;LL Mask,toMask;int p1,p2,bel;
	int ans=0;
	lx=n;ly=m;
	while (s[lx][ly]=='*')
	{
		ly--;
		if (ly==0)
		{
			lx--;
			ly=m;
		}
		if (lx==0) break;
	}
	if (lx==0) {puts("0");return 0;}
	for (i=1;i<=n;i++)
	{
		for (j=1;j<=m;j++)
		{
			for (r=0;r<=p-1;r++)
				for (k=hsh[cur].head[r];k;k=hsh[cur].nxt[k])
				{
					Mask=hsh[cur].to[k];
					p1=getplug(Mask,j);p2=getplug(Mask,j+1);
					if (s[i][j]=='.')
					{
						if (p1 && p2)
						{
							if (p1==p2) continue;
							bel=min(p1,p2);Mask=modify(Mask,bel,max(p1,p2));
						}
						if (!p1 && !p2) bel=15;
						if ((p1 && !p2) || (!p1 && p2)) bel=max(p1,p2);
						Mask=setplug(Mask,j,0);Mask=setplug(Mask,j+1,0);
						if (check(i,j,Mask,bel))
						{
							toMask=Mask;toMask=setplug(toMask,j,0);toMask=setplug(toMask,j+1,0);
							toMask=getMask(toMask);
							hsh[nxt].Insert(toMask,hsh[cur].val[k]);
						}
						if (i!=n)
						{
							toMask=Mask;toMask=setplug(toMask,j,bel);toMask=setplug(toMask,j+1,0);
							toMask=getMask(toMask);
							hsh[nxt].Insert(toMask,hsh[cur].val[k]);
						}
						if (j!=m)
						{
							toMask=Mask;toMask=setplug(toMask,j+1,bel);toMask=setplug(toMask,j,0);
							toMask=getMask(toMask);
							hsh[nxt].Insert(toMask,hsh[cur].val[k]);
						}
						if (i!=n && j!=m)
						{
							toMask=Mask;toMask=setplug(toMask,j,bel);toMask=setplug(toMask,j+1,bel);
							toMask=getMask(toMask);
							hsh[nxt].Insert(toMask,hsh[cur].val[k]);
						}
					}
					else
					{
						if (p1 || p2) continue;
						hsh[nxt].Insert(Mask,hsh[cur].val[k]);
					}	
				}
			swap(cur,nxt);hsh[nxt].clear();
		}
		if (i!=n)
		{
			for (r=0;r<=p-1;r++)
				for (k=hsh[cur].head[r];k;k=hsh[cur].nxt[k])
				{
					Mask=hsh[cur].to[k];
					Mask=Mask<<4;Mask=setplug(Mask,1,0);
					hsh[nxt].Insert(Mask,hsh[cur].val[k]);
				}
			swap(cur,nxt);hsh[nxt].clear();
		}
	}
	for (k=hsh[cur].head[0];k;k=hsh[cur].nxt[k])
		if (hsh[cur].to[k]==0) {printf("%d\n",hsh[cur].val[k]);return 0;}
	printf("0\n");
	return 0;
}
