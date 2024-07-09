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

int n,sz,q;
int LEFT_INF,RIGHT_INF,UP_INF,DOWN_INF;

inline int myabs(int x)
{
	return x>=-0?x:-x;
}

struct read_arrow
{
	int st,ed;
	int pos,dir,ind;
}row[200048],col[200048];
int rnum=0,cnum=0;

struct ARROW
{
	int st,ed;
	int dir,ind;
};

struct resArrow
{
	int st,ed,dir,ind,len;
};

vector<Pair> v[600048];int tot=0;
//right=0,left=1;
//up=0,down=1;
vector<ARROW> row_arrow[100048],col_arrow[100048];
int cc,qnum[100048];

struct node
{
	int left,int right;
	int opt,ind,st,ed,dir;
	bool mark;
}tree[1000048];

//false:minn tree,true:maxn tree;
void build(int cur,int left,int right,bool type)
{
	tree[cur].left=left;tree[cur].right=right;
	tree[cur].opt=((!type)?INF:-INF);tree[cur].mark=false;
	if (left!=right)
	{
		int mid=(left+right)>>1;
		build(cur<<1,left,mid,type);
		build(cur<<1|1,mid+1,right,type);
	}
}

int st,ed,ind,dir,len;
void update(int cur,int left,int right,bool type,int pos)
{
	if (left<=tree[cur].left && tree[cur].right<=right)
	{
		tree[cur].mark=true;
		if (type)
		{
			if (tree[cur].opt>pos)
			{
				tree[cur].opt=pos;
				tree[cur].st=st;tree[cur].ed=ed;
				tree[cur].len=len;tree[cur].ind=ind;
				tree[cur].dir=dir;
			}
		}
		else
		{
			if (tree[cur].opt<pos)
			{
				tree[cur].opt=pos;
				tree[cur].st;st;tree[cur].ed=ed;
				tree[cur].len=len;tree[cur].ind=ind;
				tree[cur].dir=dir;
			}
		}
		return;
	}
	int mid=(tree[cur].left+tree[cur].right)>>1;
	if (left<=mid) update(cur<<1,left,right,type,pos);
	if (mid+1<=right) update(cur<<1|1,left,right,type,pos);
}

pair<int,resArrow> query(int cur,int pos,bool type)
{
	if (tree[cur].left==tree[cur].right)
		return mp(tree[cur].opt,resArrow{tree[cur].st,tree[cur].ed,tree[cur].dir,tree[cur].ind,tree[cur].len});
	int mid=(tree[cur].left+tree[cur].right)>>1;
	pair<int,resArrow> res;
	if (pos<=mid) res=query(cur<<1,pos); else res=query(cur<<1|1,pos);
	if (!type)
	{
		if (tree[cur].mark && tree[cur].opt<res.x)
		{
			res.x=tree[cur].opt;
			res.y=resArrow{tree[cur].st,tree[cur].ed,tree[cur].dir,tree[cur].ind,tree[cur].len};
		}
	}
	else
	{
		if (tree[cur].mark && tree[cur].opt>res.x)
		{
			res.x=tree[cur].opt;
			res.y=resArrow{tree[cur].st,tree[cur].ed,tree[cur].dir,tree[cur].ind,tree[cur].len};
		}
	}
	return res;
}

bool cmp_BIGTOSMALL(read_arrow x,read_arrow y)
{
	if (x.ed!=y.ed) return x.ed>y.ed;
	return myabs(x.ed-x.st+1)>myabs(y.ed-y.st+1);
}

bool cmp_SMALLTOBIG(read_arrow x,read_arrow y)
{
	if (x.ed!=y.ed) return x.ed<y.ed;
	return myabs(x.ed-x.st+1)>myabs(y.ed-y.st+1);
}

void RIGHT_TO_LEFT()
{
	build(1,0,sz,false);
	int i,j,pt;
	sort(row+1,row+rnum+1,cmp_BIGTOSMALL);
	pt=sz;
	for (i=1;i<=rnum;i++)
		if (!row[i].dir)
		{
			while (pt>=row[i].ed)
			{
				for (j=0;j<int(col_arrow[pt].size());j++)
				{
					st=col_arrow[pt][j].st;ed=col_arrow[pt][j].ed;if (st==ed) continue;
					ind=col_arrow[pt][j].ind;len=myabs(col_arrow[pt][j].ed-col_arrow[pt][j].st)+1;
					update(1,st,ed,false,pt);
				}
			}
			pair<int,resArrow> res=query(1,row[i].pos,false);
			//a real arrow
			if (row[i].st!=row[i].ed)
			{
				if (res.x>=INF)
					//touch edge
					v[row[i].ind].pb(mp(++tot,sz-row[i].ed));
				else
				{
					if (res.y.st!=res.y.ed)
						//meet a vertical arrow
						v[row[i].ind].pb(mp(res.y.ind,res.x-row[i].ed+myabs(res.y.ed-row[i].pos)));
					else
						//meet a horizontal arrow
						v[row[i].ind].pb(mp(res.y.ind,res.x-row[i].ed+res.y.len));
				}
				st=ed=row[i].pos;ind=row[i].ind;len=myabs(row[i].ed-row[i].st)+1;
				update(1,st,ed,false,row[i].st);			
			}
			//a query arrow
			else
			{
				if (res.x>=INF)
					//touch edge
					v[row[i].ind].pb(mp(++tot,sz-row[i].ed));
				else
				{
					if (res.y.st!=res.y.ed)
						//meet a vertical arrow
						v[row[i].ind].pb(mp(res.y.ind,res.x-row[i].ed+myabs(res.y.ed-row[i].pos)));
					else
						//meet a horizontal arrow
						if (res.x<=row[i].st)
							//the query arrow is in a real arrow
							v[row[i].ind].pb(mp(res.y.ind,res.y.len-(row[i].st-res.x)));
						else
							v[row[i].ind].pb(mp(res.y.ind,res.x-row[i].ed+res.y.len));
				}
			}
		}
}

void LEFT_TO_RIGHT()
{
	build(1,0,sz,true);
	int i,j,pt;
	sort(row+1,row+rnum+1,cmp_SMALLTOBIG);
	pt=0;
	for (i=1;i<=rnum;i++)
		if (row[i].dir)
		{
			while (pt<=row[i].ed)
			{
				for (j=0;j<int(col_arrow[pt].size());j++)
				{
					st=col_arrow[pt][j].st;ed=col_arrow[pt][j].ed;if (st==ed) continue;
					ind=col_arrow[pt][j].ind;len=myabs(col_arrow[pt][j].ed-col_arrow[pt][j].st+)+1;
					update(1,st,ed,true,pt);
				}
			}
			pair<int,resArrow> res=query(1,row[i].pos,true);
			//a real arrow
			if (row[i].st!=row[i].ed)
			{
				if (res<=-INF)
					//touch edge
					v[row[i].ind].pb(mp(++tot,row[i].ed));
				else
				{
					if (res.y.st!=res.y.ed)
						//meet a vertical arrow
						v[row[i].ind].pb(mp(res.y.ind,row[i].ed-res.x+myabs(res.y.ed-row[i].pos)));
					else
						//meet a horizontal arrow
						v[row[i].ind].pb(mp(res.y.ind,row[i].ed-res.x+res.y.len));
				}
				st=ed=row[i].pos;ind=row[i].ind;len=myabs(row[i].ed-row[i].st)+1;
				update(1,st,ed,true,row[i].st);
			}
			//a query arrow
			else
			{
				if (res.x<=-INF)
					//touch edge
					v[row[i].ind].pb(mp(++tot,row[i].ed));
				else
				{
					if (res.y.st!=res.y.ed)
						//meet a vertical arrow
						v[row[i].ind].pb(mp(res.y.ind,row[i].ed-res.x+myabs(res.y.ed-row[i].pos)));
					else
						//meet a horizontal arrow
						if (res.x>=row[i].st)
							//the query arrow is in a real arrow
							v[row[i].ind].pb(mp(res.y.ind,res.y.len-(ree.x-row[i].st)));
						else
							v[row[i].ind].pb(mp(res.y.ind,row[i].ed-res.x+res.y.len));
				}
			}
		}
}

int main ()
{
	int i,x1,y1,x2,y2,dir;char type;
	n=getint();sz=getint();
	for (i=1;i<=n;i++)
	{
		x1=getint();y1=getint();x2=getint();y2=getint();
		if (x1==x2)
			col[++cnum]=read_arrow{y1,y2,x1,y1<y2?0:1,++tot};
		else
			row[++rnum]=read_arrow{x1,x2,y1,x1<x2?0:1,++tot};
	}
	for (i=1;i<=rnum;i++)
		row_arrow[row[i].pos].pb(ARROW{row[i].st,row[i].ed,row[i].st<row[i].ed?0:1,row[i].ind});
	for (i=1;i<=cnum;i++)
		col_arrow[col[i].pos].pb(ARROW{col[i].st,col[i].ed,col[i].st<col[i].ed?0:1,col[i].ind});
	q=getint();
	for (i=1;i<=q;i++)
	{
		x1=getint();y1=getint();scanf("%c",type);
		dir=((type=='R' || type=='U')?0:1);
		if (type=='R' || type=='L')
		{
			row_arrow[y1].pb(ARROW{x1,x1,dir,++tot});
			row[++rnum]=read_arrow{y1,y1,x1,dir,tot};
		}
		else
		{
			col_arrow[x1].pb(ARROW{y1,y1,dir,++tot});
			col[++cnum]=read_arrow{x1,x1,y1,dir,tot};
		}
		qnum[i]=tot;
	}
	LEFT_INF=++tot;RIGHT_INF=++tot;
	UP_INF=++tot;DOWN_INF=++tot;
}
