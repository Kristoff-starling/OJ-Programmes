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

struct STATE
{
	int p1,p2,p3,cap,e1,e2,e3;
	inline void print()
	{
		cout<<p1<<' '<<p2<<' '<<p3<<' '<<cap<<' '<<e1<<' '<<e2<<' '<<e3<<endl;
	}
};


inline int ToState(int p1,int p2,int p3,int cap,int e1,int e2,int e3)
{
	return (e1*4+e2*2+e3)*2000+cap*1000+p1*100+p2*10+p3;
}

inline STATE ToNUM(int cur)
{
	STATE res={0,0,0,0,0,0,0};
	int pt1=cur/2000,pt2=cur%2000;
	res.cap=pt2/1000;res.p1=pt2/100%10;res.p2=pt2/10%10;res.p3=pt2%10;
	res.e1=pt1/4;res.e2=pt1/2%2;res.e3=pt1%2;
	return res;
}

int dist[20048],num[4][20],len[4];Pair from[20048];
string s;

int head[500048],nxt[1000048],to[1000048],f[1000048],method[1000048],tot=1;
inline void add_edge(int s,int t,int c,int way)
{
	//STATE res1=ToNUM(s);STATE res2=ToNUM(t);
	//if (res1.p1==1 && res1.p2==1 && res1.p3==1 && res1.cap==0 && res1.e1==0 && res1.e2==1 && res1.e3==0 && res2.p1==2 && res2.p2==1 && res2.p3==2 && res2.cap==0 && res2.e1 && res2.e2 && res2.e3) {res1.print();res2.print();cout<<"------------------"<<endl;}
	to[++tot]=t;nxt[tot]=head[s];head[s]=tot;f[tot]=c;method[tot]=way;
}

inline void STRING_TO_NUM(string s,int ind)
{
	int i,pt=0;
	for (i=int(s.size())-1;i>=0;i--) num[ind][++pt]=s[i]-'0';
	len[ind]=pt;
}

inline pair<bool,int> check(int p1,int p2,int p3,int cap,int add1,int add2,int add3,int tocap,int e1,int e2,int e3,int le1,int le2,int le3)
{
	//if (p1==0 && p2==0 && p3==0 && cap==0 && add1==1 && add2==1 && add3==1 && tocap==0 && e1 && e2 && e3 && !le1 && !le2 && !le3) cout<<"*"<<endl;
	int i,j,k,n1,n2,n3;
	for ((e1 && !le1)?i=1:i=0;le1?i<=0:i<=9;i++)
		for ((e2 && !le2)?j=1:j=0;le2?j<=0:j<=9;j++)
			for ((e3 && !le3)?k=1:k=0;le3?k<=0:k<=9;k++)
			{
				if (tocap && e3) continue;
				//if (p1==0 && p2==0 && p3==0 && cap==0 && add1==1 && add2==1 && add3==1 && tocap==0 && e1 && e2 && e3 && !le1 && !le2 && !le3) cout<<i<<' '<<j<<' '<<k<<endl;
				n1=(add1?num[1][p1+1]:i);n2=(add2?num[2][p2+1]:j);n3=(add3?num[3][p3+1]:k);
				if (n1+n2+cap==tocap*10+n3) return mp(true,n1*100+n2*10+n3);
			}
	return mp(false,-1);
}

inline int count_num(int e1,int e2,int e3)
{
	return 3-e1-e2-e3;
}

void addedge(int p1,int p2,int p3,int cap,int e1,int e2,int e3)
{
	if ((p1<len[1] && e1) || (p2<len[2] && e2) || (p3<len[3] && e3)) return;
	int cur=ToState(p1,p2,p3,cap,e1,e2,e3),i,j,k,tocap,toe1,toe2,toe3;
	for (i=0;i<=1;i++)
		for (j=0;j<=1;j++)
			for (k=0;k<=1;k++)
				for (tocap=0;tocap<=1;tocap++)
					for (toe1=0;toe1<=1;toe1++)
						for (toe2=0;toe2<=1;toe2++)
							for (toe3=0;toe3<=1;toe3++)
							{
								if ((p1==len[1] && i) || (p2==len[2] && j) || (p3==len[3] && k)) continue;
								if ((p1+i<len[1] && toe1) || (p2+j<len[2] && toe2) || (p3+k<len[3] && toe3)) continue;
								if ((e1 && !toe1) || (e2 && !toe2) || (e3 && !toe3)) continue;
								//if (p1==0 && p2==0 && p3==0 && cap==0 && i==1 && j==1 && k==1 && tocap==0 && toe1 && toe2 && toe3) cout<<"("<<endl;
								pair<bool,int> res=check(p1,p2,p3,cap,i,j,k,tocap,toe1,toe2,toe3,e1,e2,e3);
								if (!res.x) continue;
								//if (p1==0 && p2==0 && p3==0 && i==1 && j==1 && k==1) cout<<"("<<endl;
								add_edge(cur,ToState(p1+i,p2+j,p3+k,tocap,toe1,toe2,toe3),count_num(e1,e2,e3),res.y);
							}
}

priority_queue<Pair> q;
void dijkstra()
{
	int i,y,dd,cur,starter=ToState(0,0,0,0,0,0,0);
	q.push(mp(0,starter));
	for (i=0;i<=20000;i++) dist[i]=INF;
	dist[starter]=0;from[starter]=mp(-1,-1);
	while (!q.empty())
	{
		dd=-q.top().x;cur=q.top().y;q.pop();
		if (dd>dist[cur]) continue;
		//cout<<cur<<"__"<<endl;
		for (i=head[cur];i;i=nxt[i])
		{
			y=to[i];
			if (dist[cur]+f[i]<dist[y])
			{
				dist[y]=dist[cur]+f[i];
				from[y]=mp(cur,method[i]);
				q.push(mp(-dist[y],y));
			}
		}
	}
}

int ans1,ans2,ans3;

void construct_ans(int ed)
{
	ans1=ans2=ans3=0;
	int cur=ed;
	while (cur!=-1)
	{
		//cout<<cur<<"&&"<<endl;
		//ToNUM(cur).print();
		if (from[cur].x==-1) break;
		ans1=ans1*10+from[cur].y/100;
		ans2=ans2*10+from[cur].y/10%10;
		ans3=ans3*10+from[cur].y%10;
		cur=from[cur].x;
	}
}

int main ()
{
	cin>>s;
	int pos=s.find('+'),pos1;STRING_TO_NUM(s.substr(0,pos),1);
	pos1=pos+1;pos=s.find('=',pos1);STRING_TO_NUM(s.substr(pos1,pos-pos1),2);
	STRING_TO_NUM(s.substr(pos+1,int(s.size())-1-(pos+1)+1),3);
	int i,j,k,cap,e1,e2,e3;
	//cout<<len[1]<<' '<<len[2]<<' '<<len[3]<<endl;
	//cout<<num[1][1]<<' '<<num[2][1]<<' '<<num[3][1]<<endl;
	for (i=0;i<=len[1];i++)
		for (j=0;j<=len[2];j++)
			for (k=0;k<=len[3];k++)
				for (cap=0;cap<=1;cap++)
					for (e1=0;e1<=1;e1++)
						for (e2=0;e2<=1;e2++)
							for (e3=0;e3<=1;e3++)
								addedge(i,j,k,cap,e1,e2,e3);
	dijkstra();
	int ed;
	if (dist[ToState(len[1],len[2],len[3],0,1,1,1)]<dist[ToState(len[1],len[2],len[3],1,1,1,1)])
		ed=ToState(len[1],len[2],len[3],0,1,1,1);
	else
		ed=ToState(len[1],len[2],len[3],1,1,1,1);
	//cout<<dist[ed]<<'^'<<endl;
	//cout<<ed<<endl;
	//cout<<ToState(len[1],len[2],len[3],1,1,1,1)<<endl;
	construct_ans(ed);
	printf("%d+%d=%d\n",ans1,ans2,ans3);
	//cout<<tot<<endl;
	return 0;
}