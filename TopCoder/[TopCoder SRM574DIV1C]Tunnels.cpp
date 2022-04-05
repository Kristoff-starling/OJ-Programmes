#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define LB long double
#define ull unsigned long long
#define x first
#define y second
#define pb push_back
#define pf push_front
#define mp make_pair
#define Pair pair<int,int>
#define pLL pair<LL,LL>
#define pii pair<double,double>
// #define LOCAL true

const int INF=2e9;
const LL LINF=2e16;
const int magic=348;
const int MOD=1e9+7;
const double eps=1e-10;
const double pi=acos(-1);

struct fastio
{
	static const int S=1e7;
	char rbuf[S+48],wbuf[S+48];int rpos,wpos,len;
	fastio() {rpos=len=wpos=0;}
	inline char Getchar()
	{
		if (rpos==len) rpos=0,len=fread(rbuf,1,S,stdin);
		if (!len) return EOF;
		return rbuf[rpos++];
	}
	template <class T> inline void Get(T &x)
	{
		char ch;bool f;T res;
		while (!isdigit(ch=Getchar()) && ch!='-') {}
		if (ch=='-') f=false,res=0; else f=true,res=ch-'0';
		while (isdigit(ch=Getchar())) res=res*10+ch-'0';
		x=(f?res:-res);
	}
	inline void getstring(char *s)
	{
		char ch;
		while ((ch=Getchar())<=32) {}
		for (;ch>32;ch=Getchar()) *s++=ch;
		*s='\0';
	}
	inline void flush() {fwrite(wbuf,1,wpos,stdout);fflush(stdout);wpos=0;}
	inline void Writechar(char ch)
	{
		if (wpos==S) flush();
		wbuf[wpos++]=ch;
	}
	template <class T> inline void Print(T x,char ch)
	{
		char s[20];int pt=0;
		if (x==0) s[++pt]='0';
		else
		{
			if (x<0) Writechar('-'),x=-x;
			while (x) s[++pt]='0'+x%10,x/=10;
		}
		while (pt) Writechar(s[pt--]);
		Writechar(ch);
	}
	inline void printstring(char *s)
	{
		int pt=1;
		while (s[pt]!='\0') Writechar(s[pt++]);
	}
}io;

template <typename T> inline void check_min(T &x,T nv) {x=min(x,nv);}
template <typename T> inline void check_max(T &x,T nv) {x=max(x,nv);}
template <typename T> inline T myabs(T x) {return x>=0?x:-x;}

const int MAXN=50;

int n,m;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int Mp[MAXN+48][MAXN+48];
bool visited[MAXN+48][MAXN+48];
int lmark[MAXN+48],rmark[MAXN+48];

struct Fragment
{
	int depth[2];int type[2];
	inline void clear() {depth[0]=depth[1]=type[0]=type[1]=0;}
	inline void print() {cerr<<depth[0]<<' '<<type[0]<<' ';if (depth[1]) cerr<<depth[1]<<' '<<type[1];cerr<<endl;}
	inline bool operator < (const Fragment &other) const {return depth[0]<other.depth[0];}
}L[MAXN+48],R[MAXN+48],cross[MAXN+48];
int tol[MAXN+48],tor[MAXN+48];
int dp[MAXN+48][MAXN+48][MAXN+48];
int lnum,rnum,cnum;
//0: up; 1: down; 2: bidirectional

class Tunnels
{
	inline bool nox() {for (register int i=1;i<=n;i++) for (register int j=1;j<=n;j++) if (Mp[i][j]) return false; return true;}
	inline bool onborder(Pair pos) {return pos.x==1 || pos.y==1 || pos.y==m;}
	vector<Pair> Pt;
	inline bool ishead(int x,int y)
	{
		int cnt=0;
		for (register int dir=0;dir<4;dir++)
		{
			register int xx=x+dx[dir],yy=y+dy[dir];
			if (1<=xx && xx<=n && 1<=yy && yy<=m && Mp[xx][yy]) cnt++;
		}
		return (cnt==0 || cnt==1);
	}
	inline void flood(int x,int y)
	{
		visited[x][y]=true;int xx,yy;
		if (ishead(x,y)) Pt.pb(mp(x,y));
		for (register int dir=0;dir<4;dir++)
		{
			xx=x+dx[dir];yy=y+dy[dir];
			if (1<=xx && xx<=n && 1<=yy && yy<=m && !visited[xx][yy] && Mp[xx][yy]) flood(xx,yy);
		}
	}
	public:
		inline int minimumTunnels(vector<string> Map)
		{
			n=int(Map.size());m=int(Map[0].size());
			lnum=rnum=cnum=0;
			for (register int i=1;i<=MAXN;i++) L[i].clear(),R[i].clear(),cross[i].clear();
			for (register int i=1;i<=n;i++)
			{
				for (register int j=1;j<=m;j++)
					Mp[i][j]=(Map[i-1][j-1]=='X');
			}
			if (nox()) return 0;
			if (m==1) return 1;
			int ans=0;memset(visited,false,sizeof(visited));
			for (register int j=1;j<=m;j++)
				if (Mp[1][j] && !visited[1][j])
				{
					Pt.clear();flood(1,j);
					if (int(Pt.size())==1)
					{
						if (Pt[0].y==1)
						{
							lnum++;
							L[lnum].depth[0]=1;L[lnum].type[0]=0;
							L[lnum].depth[1]=1;L[lnum].type[1]=1;
						}
						else if (Pt[0].y==m)
						{
							rnum++;
							R[rnum].depth[0]=1;R[rnum].type[0]=0;
							R[rnum].depth[1]=1;R[rnum].type[1]=1;
						}
						else ans++;
						continue;
					}
					if (Pt[0].y>Pt[1].y) swap(Pt[0],Pt[1]);
					//dead
					if (Pt[0].y!=1 && Pt[0].y!=m && Pt[1].y!=1 && Pt[1].y!=m) {ans++;continue;}
					if (!onborder(Pt[0]) || !onborder(Pt[1])) {ans++;continue;}
					//cross
					if (Pt[0].y==1 && Pt[1].y==m)
					{
						cnum++;
						cross[cnum].depth[0]=Pt[0].x;cross[cnum].depth[1]=Pt[1].x;
						if (Pt[0].x==Pt[1].x)
							cross[cnum].type[0]=cross[cnum].type[1]=2;
						else if (Pt[0].x<Pt[1].x)
							cross[cnum].type[0]=0,cross[cnum].type[1]=1;
						else
							cross[cnum].type[0]=1,cross[cnum].type[1]=0;
						continue;
					}
					//left
					if (Pt[0].y==1)
					{
						lnum++;
						L[lnum].depth[0]=1;L[lnum].type[0]=0;
						L[lnum].depth[1]=Pt[0].x;L[lnum].type[1]=1;
					}
					else
					//right
					{
						rnum++;
						R[rnum].depth[0]=1;R[rnum].type[0]=0;
						R[rnum].depth[1]=Pt[1].x;R[rnum].type[1]=1;
					}
				}
			for (register int i=1;i<=n;i++)
				if (Mp[i][1] && !visited[i][1])
				{
					Pt.clear();flood(i,1);
					if (int(Pt.size())==1)
					{
						++lnum;
						L[lnum].depth[0]=Pt[0].x;L[lnum].type[0]=0;
						continue;
					}
					if (Pt[0].y>Pt[1].y) swap(Pt[0],Pt[1]);
					if (onborder(Pt[0])+onborder(Pt[1])<2)
					{
						lnum++;
						L[lnum].depth[0]=Pt[0].x;L[lnum].type[0]=0;
						continue;
					}
					//cross
					if (Pt[1].y==m)
					{
						cnum++;
						if (Pt[0].x==Pt[1].x) cross[cnum].depth[0]=cross[cnum].depth[1]=Pt[0].x,cross[cnum].type[0]=cross[cnum].type[1]=2;
						else cross[cnum].depth[0]=Pt[0].x,cross[cnum].depth[1]=Pt[1].x,cross[cnum].type[0]=(Pt[0].x>Pt[1].x),cross[cnum].type[1]=1-cross[cnum].type[0];
						continue;
					}
					if (myabs(Pt[0].x-Pt[1].x)+1>2)
					{
						lnum++;
						L[lnum].depth[0]=min(Pt[0].x,Pt[1].x);L[lnum].depth[1]=max(Pt[0].x,Pt[1].x);
						L[lnum].type[0]=0;L[lnum].type[1]=1;
					}
					else
					{
						lnum++;
						L[lnum].depth[0]=min(Pt[0].x,Pt[1].x);L[lnum].type[0]=0;
					}
				}
			for (register int i=1;i<=n;i++)
				if (Mp[i][m] && !visited[i][m])
				{
					Pt.clear();flood(i,m);
					if (int(Pt.size())==1)
					{
						++rnum;
						R[rnum].depth[0]=Pt[0].x;R[rnum].type[0]=0;
						continue;
					}
					if (Pt[0].y>Pt[1].y) swap(Pt[0],Pt[1]);
					if (onborder(Pt[0])+onborder(Pt[1])<2)
					{
						rnum++;
						R[rnum].depth[0]=Pt[1].x;R[rnum].type[0]=0;
					}
					else
					{
						if (myabs(Pt[0].x-Pt[1].x)+1>2)
						{
							rnum++;
							R[rnum].depth[0]=min(Pt[0].x,Pt[1].x);R[rnum].depth[1]=max(Pt[0].x,Pt[1].x);
							R[rnum].type[0]=0;R[rnum].type[1]=1;
						}
						else
						{
							rnum++;
							R[rnum].depth[0]=min(Pt[0].x,Pt[1].x);R[rnum].type[0]=0;
						}
					}
				}
			sort(L+1,L+lnum+1);sort(R+1,R+rnum+1);int pt1=0,pt2=0;
			for (register int i=1;i<=cnum;i++)
			{
				for (;pt1<lnum && L[pt1+1].depth[0]<cross[i].depth[0];pt1++);
				for (;pt2<rnum && max(R[pt2+1].depth[0],R[pt2+1].depth[1])<cross[i].depth[1];pt2++);
				tol[i]=pt1;tor[i]=pt2;
			}
			for (register int i=0;i<=MAXN+10;i++)
				for (register int j=0;j<=MAXN+10;j++)
					for (register int k=0;k<=MAXN+10;k++)
						dp[i][j][k]=INF;
			dp[0][0][0]=0;
			for (register int i=1;i<=cnum;i++)
				for (register int j=0;j<=n;j++)
					for (register int k=0;k<=n;k++)
						if (dp[i-1][j][k]<INF)
						{
							int Lleft=j,Rleft=k,val=dp[i-1][j][k];
							memset(lmark,0,sizeof(lmark));
							memset(rmark,0,sizeof(rmark));
							for (register int p=tol[i-1]+1;p<=tol[i];p++)
							{
								if (p>tol[i-1]+1) for (register int q=L[p-1].depth[0];q<=L[p].depth[0]-1;q++) Lleft+=lmark[q];
								if (Lleft) Lleft--; else val++;
								if (L[p].depth[1]) lmark[L[p].depth[1]]++;
							}
							for (register int q=L[tol[i]].depth[0];q<=cross[i].depth[0]-1;q++) Lleft+=lmark[q];
							for (register int p=tor[i-1]+1;p<=tor[i];p++)
							{
								if (p>tor[i-1]+1) for (register int q=R[p-1].depth[0];q<=R[p].depth[0]-1;q++) Rleft+=rmark[q];
								if (Rleft) Rleft--; else val++;
								if (R[p].depth[1]) rmark[R[p].depth[1]]++;
							}
							for (register int q=L[tor[i]].depth[0];q<=cross[i].depth[1]-1;q++) Rleft+=rmark[q];
							if (cross[i].type[0]==2)
							{
								//Left up and right down
								int curl=max(Lleft-1,0),curr=Rleft+1,curval=val+(Lleft==0);
								check_min(dp[i][curl][curr],curval);
								//Left down and right up
								curl=Lleft+1;curr=max(Rleft-1,0);curval=val+(Rleft==0);
								check_min(dp[i][curl][curr],curval);
							}
							else
							{
								if (cross[i].type[0]==0)
								{
									//Left up and right down
									int curl=max(Lleft-1,0),curr=Rleft+1,curval=val+(Lleft==0);
									check_min(dp[i][curl][curr],curval);
								}
								else
								{
									int curl=Lleft+1,curr=max(Rleft-1,0),curval=val+(Rleft==0);
									check_min(dp[i][curl][curr],curval);
								}
							}
						}
			int add=INF;
			for (register int j=0;j<=n;j++)
				for (register int k=0;k<=n;k++)
					if (dp[cnum][j][k]<INF)
					{
						int Lleft=j,Rleft=k,val=dp[cnum][j][k];
						memset(lmark,0,sizeof(lmark));
						memset(rmark,0,sizeof(rmark));
						for (register int p=tol[cnum]+1;p<=lnum;p++)
						{
							if (p>tol[cnum]+1) for (register int q=L[p-1].depth[0];q<=L[p].depth[0]-1;q++) Lleft+=lmark[q];
							if (Lleft) Lleft--; else val++;
							if (L[p].depth[1]) lmark[L[p].depth[1]]++;
						}
						for (register int p=tor[cnum]+1;p<=rnum;p++)
						{
							if (p>tor[cnum]+1) for (register int q=R[p-1].depth[0];q<=R[p].depth[0]-1;q++) Rleft+=rmark[q];
							if (Rleft) Rleft--; else val++;
							if (R[p].depth[1]) rmark[R[p].depth[1]]++;
						}
						add=min(add,val);
					}
			return ans+add;
		}
};

#ifdef LOCAL
int main ()
{
#ifdef LOCAL
	double t=clock();
	freopen ("aa.in","r",stdin);
	freopen ("aa.out","w",stdout);
	cerr<<"Running..."<<endl;
#endif
	int nn;vector<string> ss;string s;
	Tunnels A;
	while (cin>>nn)
	{
		ss.clear();
		for (register int i=1;i<=nn;i++) cin>>s,ss.pb(s);
		cout<<A.minimumTunnels(ss)<<endl;
	}
#ifdef LOCAL
	cerr<<"Exec Time: "<<(clock()-t)/CLOCKS_PER_SEC<<endl;
#endif
	return 0;
}
#endif