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
const double pi=3.14159265;

inline int getint()
{
    char ch;int res;bool f;
    while (!isdigit(ch=getchar()) && ch!='-') {}
    if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
    while (isdigit(ch=getchar())) res=res*10+ch-'0';
    return f?res:-res;
}

int n,m,k;
Pair stone[800048];

const int base=150048;
set<Pair> pos[800048],neg[800048];
bool has[800048][5];
int from[800048][5];
LL ans=0;int rev=0;
bool superf,revf,goodstart;

inline int myabs(int x)
{
	return x>=0?x:-x;
}

void doit(int x,int y,int dir)
{
	//cout<<x<<' '<<y<<' '<<dir<<endl;
	int tox,toy,toind;
	if (dir==1 || dir==3)
	{
		set<Pair>::iterator iter;
		iter=neg[x+y].lower_bound(mp(x,-1));
		//cout<<iter->x<<' '<<iter->y<<endl;
		if (dir==1)
		{
			iter--;
			tox=iter->x;toy=x+y-tox;
			tox++;toy--;toind=iter->y;
			if (from[toind][dir])
			{
				superf=true;
				ans+=myabs(from[toind][dir]-x);
				//if (from[toind][dir]!=x)
				return;
			}
			ans+=myabs(tox-x)+1;from[toind][dir]=x;
			if ((has[toind][3] && has[toind][4]) || (!has[toind][3] && !has[toind][4]))
			{
				rev++;revf=true;
				return;
			}
			if (has[toind][3])
			{
				doit(tox-1,toy,4);
				if (superf || revf) return;
			}
			else
			{
				doit(tox,toy+1,2);
				if (superf || revf) return;
			}
		}
		else
		{
			tox=iter->x;toy=x+y-tox;
			//cout<<tox<<' '<<toy<<endl;
			tox--;toy++;toind=iter->y;
			//cout<<toind<<' '<<dir<<endl;
			if (from[toind][dir])
			{
				//cout<<"*"<<endl;
				superf=true;
				ans+=myabs(from[toind][dir]-x);
				//if (from[toind][dir]!=x)
				return;
			}
			//cout<<"*"<<endl;
			ans+=myabs(tox-x)+1;from[toind][dir]=x;
			//cout<<"*"<<endl;
			if ((has[toind][1] && has[toind][2]) || (!has[toind][1] && !has[toind][2]))
			{
				rev++;revf=true;
				return;
			}
			if (has[toind][1])
			{
				doit(tox+1,toy,2);
				if (superf || revf) return;
			}
			else
			{
				doit(tox,toy-1,4);
				if (superf || revf) return;
			}
		}
	}
	else
	{
		set<Pair>::iterator iter;
		iter=pos[base+x-y].lower_bound(mp(x,-1));
		if (dir==4)
		{
			iter--;
			tox=iter->x;toy=tox-(x-y);
			tox++;toy++;toind=iter->y;
			if (from[toind][dir])
			{
				superf=true;
				ans+=myabs(from[toind][dir]-x);
				//if (from[toind][dir]!=x)
				return;
			}
			ans+=myabs(tox-x)+1;from[toind][dir]=x;
			if ((has[toind][2] && has[toind][3]) || (!has[toind][2] && !has[toind][3]))
			{
				rev++;revf=true;
				return;
			}
			if (has[toind][2])
			{
				doit(tox,toy-1,3);
				if (superf || revf) return;
			}
			else
			{
				doit(tox-1,toy,1);
				if (superf || revf) return;
			}
		}
		else
		{
			tox=iter->x;toy=tox-(x-y);
			tox--;toy--;toind=iter->y;
			if (from[toind][dir])
			{
				superf=true;
				ans+=myabs(from[toind][dir]-x);
				//if (from[toind][dir]!=x)
				return;
			}
			ans+=myabs(tox-x)+1;from[toind][dir]=x;
			if ((has[toind][1] && has[toind][4]) || (!has[toind][1] && !has[toind][4]))
			{
				rev++;revf=true;
				return;
			}
			if (has[toind][1])
			{
				doit(tox+1,toy,3);
				if (superf || revf) return;
			}
			else
			{
				doit(tox,toy+1,1);
				if (superf || revf) return;
			}
		}
	}
}



int main ()
{
	int i,cc=0;
	n=getint();m=getint();k=getint();
	for (i=1;i<=k;i++)
	{
		stone[i].x=getint();stone[i].y=getint();
		pos[base+stone[i].x-stone[i].y].insert(mp(stone[i].x,i));
		neg[stone[i].x+stone[i].y].insert(mp(stone[i].x,i));
	}
	cc=k;
	for (i=1;i<=m;i++)
	{
		stone[++cc]=mp(0,i);
		pos[base+stone[cc].x-stone[cc].y].insert(mp(stone[cc].x,cc));
		neg[stone[cc].x+stone[cc].y].insert(mp(stone[cc].x,cc));
		stone[++cc]=mp(n+1,i);
		pos[base+stone[cc].x-stone[cc].y].insert(mp(stone[cc].x,cc));
		neg[stone[cc].x+stone[cc].y].insert(mp(stone[cc].x,cc));
	}
	for (i=1;i<=n;i++)
	{
		stone[++cc]=mp(i,0);
		pos[base+stone[cc].x-stone[cc].y].insert(mp(stone[cc].x,cc));
		neg[stone[cc].x+stone[cc].y].insert(mp(stone[cc].x,cc));
		stone[++cc]=mp(i,m+1);
		pos[base+stone[cc].x-stone[cc].y].insert(mp(stone[cc].x,cc));
		neg[stone[cc].x+stone[cc].y].insert(mp(stone[cc].x,cc));
	}
	stone[++cc]=mp(0,0);
	pos[base+stone[cc].x-stone[cc].y].insert(mp(stone[cc].x,cc));
	neg[stone[cc].x+stone[cc].y].insert(mp(stone[cc].x,cc));
	stone[++cc]=mp(0,m+1);
	pos[base+stone[cc].x-stone[cc].y].insert(mp(stone[cc].x,cc));
	neg[stone[cc].x+stone[cc].y].insert(mp(stone[cc].x,cc));
	stone[++cc]=mp(n+1,0);
	pos[base+stone[cc].x-stone[cc].y].insert(mp(stone[cc].x,cc));
	neg[stone[cc].x+stone[cc].y].insert(mp(stone[cc].x,cc));
	stone[++cc]=mp(n+1,m+1);
	pos[base+stone[cc].x-stone[cc].y].insert(mp(stone[cc].x,cc));
	neg[stone[cc].x+stone[cc].y].insert(mp(stone[cc].x,cc));
	set<Pair>::iterator iter,iter2;
	for (i=1;i<=n+m+2;i++)
		for (iter=neg[i].begin();iter!=neg[i].end();iter++)
		{
			if (iter->x!=1)
			{
				iter2=neg[i-1].lower_bound(mp(iter->x-1,-1));
				if (iter2!=neg[i-1].end() && iter2->x==iter->x-1) has[iter->y][1]=true;
			}
			if (iter->x!=n)
			{
				iter2=neg[i+1].lower_bound(mp(iter->x+1,-1));
				if (iter2!=neg[i+1].end() && iter2->x==iter->x+1) has[iter->y][3]=true;
			}
			if (stone[iter->y].y!=1)
			{
				iter2=neg[i-1].lower_bound(mp(iter->x,-1));
				if (iter2!=neg[i-1].end() && iter2->x==iter->x) has[iter->y][4]=true;
			}
			if (stone[iter->y].y!=m)
			{
				iter2=neg[i+1].lower_bound(mp(iter->x,-1));
				if (iter2!=neg[i+1].end() && iter2->x==iter->x) has[iter->y][2]=true;
			}
		}
	int sx,sy,sdir;string type;
	sx=getint();sy=getint();cin>>type;
	if (type=="NE") sdir=1;
	if (type=="SE") sdir=2;
	if (type=="SW") sdir=3;
	if (type=="NW") sdir=4;
	doit(sx,sy,sdir);
	if (superf)
	{
		cout<<ans<<endl;
		//printf("%lld\n",ans);
		return 0;
	}
	else
	{
		superf=revf=false;
		if (sdir==1) doit(sx,sy,3);
		if (sdir==2) doit(sx,sy,4);
		if (sdir==3) doit(sx,sy,1);
		if (sdir==4) doit(sx,sy,2);
		cout<<ans-1<<endl;
		//printf("%lld\n",ans-1);
		return 0;
	}
}