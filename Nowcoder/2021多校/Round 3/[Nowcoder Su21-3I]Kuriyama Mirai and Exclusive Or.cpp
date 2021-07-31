#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)
#define Pair pair<int,int>
#define mp make_pair
#define x first
#define y second
using namespace std;

const int MAXN=6e5;

int n,q;
int a[MAXN+48];

struct Query
{
    int op,l,r,x;
    void input() {scanf("%d%d%d%d",&op,&l,&r,&x);}
}b[MAXN+48];

int xsum[MAXN+48];
int pw[31];

int R,C;

int calc_num(int x,int y) {return x*C+y;}
Pair calc_pos(int num) {return mp(num/C,num%C);}

int mark[MAXN+48],sum[MAXN+48];

void modify(int x1,int y1,int x2,int y2)
{
    mark[calc_num(x1,y1)]^=1;
    if (x2!=R) mark[calc_num(x2+1,y1)]^=1;
    if (y2!=C-1) mark[calc_num(x1,y2+1)]^=1;
    if (y2!=C-1 && x2!=R && calc_num(x2+1,y2+1)<=n) mark[calc_num(x2+1,y2+1)]^=1;
}

void doit(int rnum,int l,int r,int ss,int ee)
{
    if (ss<=ee)
    {
        int L=max(l,ss),R=min(r,ee);
        if (L<=R) modify(rnum,L,rnum,R);
    }
    else
    {
        doit(rnum,l,r,0,ee);
        doit(rnum,l,r,ss,C-1);
    }
}

int main ()
{
    scanf("%d%d",&n,&q);rep(i,1,n) scanf("%d",a+i);
    rep(i,1,q)
    {
        b[i].input();
        if (!b[i].op) xsum[b[i].l]^=b[i].x,xsum[b[i].r+1]^=b[i].x;
    }
    rep(i,2,n) xsum[i]^=xsum[i-1];rep(i,1,n) a[i]^=xsum[i];
    C=1;pw[0]=1;rep(i,1,30) pw[i]=pw[i-1]+pw[i-1];
    rep(pos,0,29)
    {
        C<<=1;rep(i,1,n) mark[i]=0;
        R=calc_pos(n).x;
        rep(i,1,q) if (b[i].op==1)
        {
            Pair st=calc_pos(b[i].l),ed=calc_pos(b[i].r);
            int tmp=b[i].x+C-st.y;int ss,ee;
            if (pw[pos]>=tmp) ss=pw[pos]-tmp; else
            {
                ss=((tmp-pw[pos])/pw[pos+1]+(((tmp-pw[pos])%pw[pos+1]==0)?0:1))*pw[pos+1]+pw[pos];
                ss=ss-tmp;
            }
            ee=ss+pw[pos]-1;if (ee>=C) ee-=C;
            assert(ss<=C-1);
            if (st.x==ed.x)
            {
                doit(st.x,st.y,ed.y,ss,ee);
            }
            else
            {
                doit(st.x,st.y,C-1,ss,ee);doit(ed.x,0,ed.y,ss,ee);
                if (st.x+1<ed.x)
                {
                    if (ss<=ee) modify(st.x+1,ss,ed.x-1,ee);
                    else
                    {
                        modify(st.x+1,0,ed.x-1,ee);
                        modify(st.x+1,ss,ed.x-1,C-1);
                    }
                }
            }
        } 
        rep(i,0,n) if (i%C==0) sum[i]=mark[i]; else sum[i]=sum[i-1]^mark[i];
        rep(i,C,n) sum[i]^=sum[i-C];
        rep(i,1,n) if (sum[i]) a[i]^=(1<<pos);
    }
    rep(i,1,n) printf("%d ",a[i]);puts("");
    return 0;
}