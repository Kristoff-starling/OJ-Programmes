#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define pb push_back
using namespace std;

const int MAXN=1e5;

template<typename T> void check_min(T &x,T y) {if (y<x) x=y;}

int n;
int X[MAXN+48],Y[MAXN+48];

int judge(int x1,int y1,int x2,int y2)
{
    if (x2>x1 && y2>y1) return 0;
    if (x2<x1 && y2>y1) return 1;
    if (x2<x1 && y2<y1) return 2;
    if (x2>x1 && y2<y1) return 3;
}

int tc[4][4];string otc[4][4];

void p(int cnt) {while (cnt--) cout<<"f";}

int main ()
{
    ios::sync_with_stdio(false);
    int ca;cin>>ca;int sx,sy,d;
    tc[0][0]=0;tc[0][1]=1;tc[0][2]=2;tc[0][3]=1;
    tc[1][0]=1;tc[1][1]=0;tc[1][2]=1;tc[1][3]=2;
    tc[2][0]=2;tc[2][1]=1;tc[2][2]=0;tc[2][3]=1;
    tc[3][0]=1;tc[3][1]=2;tc[3][2]=1;tc[3][3]=0;
    otc[0][0]="";otc[0][1]="c";otc[0][2]="cc";otc[0][3]="u";
    otc[1][0]="u";otc[1][1]="";otc[1][2]="c";otc[1][3]="cc";
    otc[2][0]="cc";otc[2][1]="u";otc[2][2]="";otc[2][3]="c";
    otc[3][0]="c";otc[3][1]="cc";otc[3][2]="u";otc[3][3]="";
    while (ca--)
    {
        cin>>sx>>sy>>d;
        X[0]=sx;Y[0]=sy;
        cin>>n;rep(i,1,n) cin>>X[i]>>Y[i];
        int dir=d;
        rep(i,0,n-1)
        {
            int type=judge(X[i],Y[i],X[i+1],Y[i+1]);
            vector<int> avail;avail.clear();
            if (type==0 || type==1) avail.pb(0);
            if (type==0 || type==3) avail.pb(1);
            if (type==2 || type==3) avail.pb(2);
            if (type==1 || type==2) avail.pb(3);
            int tmp=1e9,dis,oo;
            for (auto nxt : avail)
                if (tc[dir][nxt]<tmp) tmp=tc[dir][nxt],dis=nxt;
            cout<<otc[dir][dis];dir=dis;oo=((dis==avail[0])?avail[1]:avail[0]);
            int cnt1=abs(X[i+1]-X[i]),cnt2=abs(Y[i+1]-Y[i]);
            if (type==0)
            {
                if (oo==0) p(cnt1),cout<<"u",p(cnt2);
                else p(cnt2),cout<<"c",p(cnt1);
            }
            else if (type==1)
            {
                if (oo==0) p(cnt1),cout<<"c",p(cnt2);
                else p(cnt2),cout<<"u",p(cnt1);
            }
            else if (type==2)
            {
                if (oo==2) p(cnt1),cout<<"u",p(cnt2);
                else p(cnt2),cout<<"c",p(cnt1);
            }
            else if (type==3)
            {
                if (oo==2) p(cnt1),cout<<"c",p(cnt2);
                else p(cnt2),cout<<"u",p(cnt1);
            }
            dir=oo;
        }
        cout<<endl;
    }
    return 0;
}