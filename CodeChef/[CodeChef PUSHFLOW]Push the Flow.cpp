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

int n,e,q;
vector<Pair> v[100048];
vector<Pair> vv[100048];
vector<int> tocycle[100048];
struct Edge
{
	int s,t,cap;
}edge[200048];
int bel[100048];bool visited[200048];
int depth[100048];Pair fa[100048];
vector<int> cedge[100048],clist[100048];int cnum;
int tot,Tnum;
int pos[100048];
int sz[100048],Fa[100048],Faedge[100048],top[100048],son[100048],sontocycle[100048];
bool type[100048];

inline void dfs(int cur,int father)
{
	int i,j,y;
	for (i=0;i<int(v[cur].size());i++)
	{
		y=v[cur][i].x;
		if (!depth[y])
		{
			depth[y]=depth[cur]+1;
			fa[y]=mp(cur,v[cur][i].y);
			dfs(y,cur);
		}
		else if (y!=father && depth[y]<depth[cur])
		{
			cnum++;++tot;type[tot]=true;
			for (j=cur;j;j=fa[j].x)
			{
				clist[cnum].pb(j);bel[j]=tot;
				if (j==y) break;
				cedge[cnum].pb(fa[j].y);
			}
			reverse(clist[cnum].begin(),clist[cnum].end());
			reverse(cedge[cnum].begin(),cedge[cnum].end());
			for (j=1;j<int(clist[cnum].size());j++) pos[clist[cnum][j]]=j;
			cedge[cnum].pb(v[cur][i].y);
		}
	}
}

vector<int> tmember[100048];
int faori[100048];
int anc[100048][21];

inline void dfs1(int cur,int father)
{
	int i,j,y;Fa[cur]=father;sz[cur]=1;son[cur]=0;tmember[Tnum].pb(cur);
	for (i=0;i<int(vv[cur].size());i++)
	{
		y=vv[cur][i].x;
		if (y!=father)
		{
			depth[y]=depth[cur]+1;Faedge[y]=vv[cur][i].y;
			faori[y]=tocycle[cur][i];
			anc[y][0]=cur;
			for (j=1;j<=20;j++) anc[y][j]=anc[anc[y][j-1]][j-1];
			dfs1(y,cur);sz[cur]+=sz[y];
			if (!son[cur] || sz[y]>sz[son[cur]])
			{
				son[cur]=y;
				sontocycle[cur]=tocycle[cur][i];
			}
		}
	}
}

int tbel[100048],tpos[100048];
vector<int> order[100048];
inline void dfs2(int cur,int tp)
{
	top[cur]=tp;order[Tnum].pb(cur);tbel[cur]=Tnum;tpos[cur]=int(order[Tnum].size());
	if (son[cur]) dfs2(son[cur],tp);
	int i,y;
	for (i=0;i<int(vv[cur].size());i++)
	{
		y=vv[cur][i].x;
		if (y!=Fa[cur] && y!=son[cur]) dfs2(y,y);
	}
}

int w[100048],ww[100048];
int minn[2400048],lson[2400048],rson[2400048];int Ttot;
int seq[100048];
int croot[100048],troot[100048];
struct SegmentTree
{
	inline void pushup(int cur) {minn[cur]=min(minn[lson[cur]],minn[rson[cur]]);}
	inline void build(int cur,int left,int right)
	{
		if (left!=right)
		{
			int mid=(left+right)>>1;
			lson[cur]=++Ttot;build(lson[cur],left,mid);
			rson[cur]=++Ttot;build(rson[cur],mid+1,right);
			pushup(cur);
		}
		else
			minn[cur]=seq[left];
	}
	inline void update(int cur,int pos,int newval,int l,int r)
	{
		if (l==r)
		{
			minn[cur]=newval;
			return;
		}
		int mid=(l+r)>>1;
		if (pos<=mid) update(lson[cur],pos,newval,l,mid); else update(rson[cur],pos,newval,mid+1,r);
		pushup(cur);
	}
	inline int query(int cur,int left,int right,int l,int r)
	{
		if (l>r || l>right || r<left) return 1e9+48;
		if (left<=l && r<=right) return minn[cur];
		int mid=(l+r)>>1;
		return min(query(lson[cur],left,right,l,mid),query(rson[cur],left,right,mid+1,r));
	}
}forcycle[100048],fortree[100048];

inline int getlca(int u,int v)
{
	if (depth[u]<depth[v]) swap(u,v);
	for (register int i=20;i>=0;i--) if (depth[anc[u][i]]>=depth[v]) u=anc[u][i];
	if (u==v) return u;
	for (register int i=20;i>=0;i--) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}

inline int getbelow(int u,int Anc)
{
	if (u==Anc) return -1;
	for (register int i=20;i>=0;i--)
		if (depth[anc[u][i]]>depth[Anc]) u=anc[u][i];
	return u;
}

int Pt[5];

inline int calc(int cur,int target,int ind)
{
	if (depth[cur]<depth[target]) return INF;
	int tp=top[cur];int res=INF;
	while (depth[tp]>depth[target])
	{
		res=min(res,fortree[tbel[cur]].query(troot[tbel[cur]],tpos[tp],tpos[Fa[cur]],1,int(tmember[tbel[cur]].size())));
		res=min(res,Faedge[tp]);cur=Fa[tp];
		if (type[cur] && faori[tp]!=clist[cur][0])
		{
			int cc=faori[tp],lim=int(clist[cur].size());
			res=min(res,forcycle[cur].query(croot[cur],1,pos[cc],1,lim)+forcycle[cur].query(croot[cur],pos[cc]+1,lim,1,lim));
		}
		tp=top[cur];
	}
	res=min(res,fortree[tbel[cur]].query(troot[tbel[cur]],tpos[target],tpos[Fa[cur]],1,int(tmember[tbel[cur]].size())));
	Pt[ind]=target;
	return res;
}

vector<int> rt;

int main ()
{
	int i,j;
	n=getint();e=getint();
	for (i=1;i<=e;i++)
	{
		edge[i].s=getint();edge[i].t=getint();edge[i].cap=getint();
		v[edge[i].s].pb(mp(edge[i].t,edge[i].cap));
		v[edge[i].t].pb(mp(edge[i].s,edge[i].cap));
	}
	tot=0;minn[0]=INF;
	for (i=1;i<=n;i++)
		if (!depth[i]) depth[i]=1,dfs(i,-1);
	for (i=1;i<=n;i++) if (!bel[i]) bel[i]=++tot;
	for (i=1;i<=e;i++)
	{
		int pt1=bel[edge[i].s],pt2=bel[edge[i].t];
		if (pt1!=pt2)
		{
			vv[pt1].pb(mp(pt2,edge[i].cap));
			vv[pt2].pb(mp(pt1,edge[i].cap));
			tocycle[pt1].pb(edge[i].s);tocycle[pt2].pb(edge[i].t);
		}
	}
	Ttot=0;
	for (i=1;i<=cnum;i++)
	{
		for (j=1;j<=int(cedge[i].size());j++) seq[j]=cedge[i][j-1];
		croot[i]=++Ttot;forcycle[i].build(croot[i],1,int(cedge[i].size()));
	}
	rt.clear();
	for (i=1;i<=n;i++) if (depth[i]==1) rt.pb(i);
	memset(depth,0,sizeof(depth));
	for (i=0;i<int(rt.size());i++)
	{
		depth[bel[rt[i]]]=1;Tnum++;
		dfs1(bel[rt[i]],0);dfs2(bel[rt[i]],bel[rt[i]]);
	}
	for (i=1;i<=tot;i++) w[i]=INF+48;
	for (i=1;i<=cnum;i++)
		if (son[i])
		{
			int lim=int(cedge[i].size());
			w[i]=forcycle[i].query(croot[i],1,pos[sontocycle[i]],1,lim)+forcycle[i].query(croot[i],pos[sontocycle[i]]+1,lim,1,lim);
		}
	for (i=1;i<=tot;i++) ww[i]=INF+48;
	for (i=1;i<=tot;i++)
		for (j=0;j<int(vv[i].size());j++)
		{
			int to=vv[i][j].x;
			if (to==son[i]) ww[i]=vv[i][j].y;
		}
	for (i=1;i<=Tnum;i++)
	{
		for (j=0;j<int(tmember[i].size());j++) seq[tpos[tmember[i][j]]]=min(w[tmember[i][j]],ww[tmember[i][j]]);
		int lim=int(tmember[i].size());
		troot[i]=++Ttot;fortree[i].build(troot[i],1,lim);
	}
	q=getint();int qtype,u,v,U,V,LCA,uu,vv,ans;
	while (q--)
	{
		qtype=getint();u=getint();v=getint();
		if (!qtype)
		{
			ans=INF;
			U=bel[u];V=bel[v];LCA=getlca(U,V);
			if (tbel[U]!=tbel[V]) {printf("0\n");continue;}
			uu=getbelow(U,LCA);vv=getbelow(V,LCA);
			Pt[1]=U;Pt[2]=V;
			if (uu!=-1)
			{
				if (U!=uu)
				{
					ans=min(ans,Faedge[U]);
					ans=min(ans,calc(U,uu,1));
				}
			}
			else
				Pt[1]=u;
			if (vv!=-1)
			{
				if (V!=vv)
				{
					ans=min(ans,Faedge[V]);
					ans=min(ans,calc(V,vv,2));
				}
			}
			else
				Pt[2]=v;
			if (type[U] && u!=clist[U][0] && uu!=-1)
			{
				int lim=int(clist[U].size());
				ans=min(ans,forcycle[U].query(croot[U],1,pos[u],1,lim)+forcycle[U].query(croot[U],pos[u]+1,lim,1,lim));
			}
			if (type[V] && v!=clist[V][0] && vv!=-1)
			{
				int lim=int(clist[V].size());
				ans=min(ans,forcycle[V].query(croot[V],1,pos[v],1,lim)+forcycle[V].query(croot[V],pos[v]+1,lim,1,lim));
			}
			if (uu!=-1)
			{
				ans=min(ans,Faedge[Pt[1]]);
				Pt[1]=faori[Pt[1]];
			}
			if (vv!=-1)
			{
				ans=min(ans,Faedge[Pt[2]]);
				Pt[2]=faori[Pt[2]];
			}
			if (type[LCA] && Pt[1]!=Pt[2])
			{
				if (pos[Pt[1]]>pos[Pt[2]]) swap(Pt[1],Pt[2]);
				int lim=int(clist[LCA].size());
				ans=min(ans,forcycle[LCA].query(croot[LCA],pos[Pt[1]]+1,pos[Pt[2]],1,lim)+min(forcycle[LCA].query(croot[LCA],1,pos[Pt[1]],1,lim),forcycle[LCA].query(croot[LCA],pos[Pt[2]]+1,lim,1,lim)));
			}
			printf("%d\n",ans);
		}
		else
		{
			Pt[1]=edge[u].s;Pt[2]=edge[u].t;
			U=bel[Pt[1]];V=bel[Pt[2]];
			if (U==V && type[U])
			{
				if (pos[Pt[1]]>pos[Pt[2]]) swap(Pt[1],Pt[2]);
				int lim=int(clist[U].size());
				if (pos[Pt[2]]-pos[Pt[1]]==1) forcycle[U].update(croot[U],pos[Pt[2]],v,1,lim); else forcycle[U].update(croot[U],lim,v,1,lim);
				if (son[U])
				{
					w[U]=forcycle[U].query(croot[U],1,pos[sontocycle[U]],1,lim)+forcycle[U].query(croot[U],pos[sontocycle[U]]+1,lim,1,lim);
					lim=int(tmember[tbel[U]].size());
					fortree[tbel[U]].update(troot[tbel[U]],tpos[U],min(w[U],ww[U]),1,lim);
				}
			}
			else
			{
				if (depth[U]>depth[V]) swap(U,V);
				if (son[U]==V)
				{
					int lim=int(tmember[tbel[U]].size());ww[U]=v;
					fortree[tbel[U]].update(troot[tbel[U]],tpos[U],min(w[U],ww[U]),1,lim);
				}
				Faedge[V]=v;
			}
		}
	}
	return 0;
}
