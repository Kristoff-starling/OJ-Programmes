#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define ull unsigned long long
using namespace std;

const int MOD=998244353;

int add(int x) {if (x>=MOD) x-=MOD;return x;}
int sub(int x) {if (x<0) x+=MOD;return x;}
void Add(int &x,int y) {x=add(x+y);}
void Sub(int &x,int y) {x=sub(x-y);}

int n,m,a[101][101],aa[101][101];
unordered_map<ull,int> pre,cur;

int A[48],B[48],col[48];

void Decompose(ull Mask,int A[])
{
    rep(i,0,m) A[i+1]=((Mask>>(i<<2))&15);
    rep(i,1,m+1) if (A[i]==0) col[i]=-1; else col[i]=(A[i]<=6?0:1);
}

bool Unique(int pos,int A[])
{
    rep(i,1,m+1) if (i!=pos && i!=pos-1 && A[i]==A[pos]) return false;
    return true;
}

ull Encode(int A[])
{
    ull res=0;
    rep(i,0,m) res|=(((ull)A[i+1])<<(i<<2));
    return res;
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d%d",&n,&m);rep(i,1,n) rep(j,1,m) scanf("%d",&a[i][j]);
        /*
        if (n<m)
        {
            rep(i,1,n) rep(j,1,m) aa[j][i]=a[i][j];
            swap(n,m);rep(i,1,n) rep(j,1,m) a[i][j]=aa[i][j];
        }
        */
        pre.clear();cur.clear();pre[0]=1;
        rep(i,1,n)
        {
            rep(j,1,m)
            {
                int cnt=0;
                for (unordered_map<ull,int>::iterator iter=pre.begin();iter!=pre.end();iter++)
                {
                    Decompose(iter->first,A);int col1,col2,col3,id1,id3;
                    if (i==3 && j==3)
                    {
                        rep(k,1,5) cerr<<A[k]<<' ';
                        cerr<<endl;
                        cerr<<iter->second<<"*"<<endl;
                        cnt+=iter->second;
                    }
                    if (j==1) col1=col[1],col2=-1,col3=col[2],id1=1,id3=2; else col1=col[j-1],col2=col[j],col3=col[j+1],id1=j-1,id3=j+1;
                    rep(c,0,1)
                    {
                        if (a[i][j]!=-1 && a[i][j]!=c) continue;
                        if (c==col1 && c==col2 && c==col3) continue;
                        if (col3!=-1 && c!=col3 && Unique(id3,A))
                        {
                            if (!(i==n && j>=m-1)) continue;
                            bool f=true;
                            rep(k,1,j-1) if (col[k]==col[id3]) {f=false;break;}
                            if (!f) continue;
                        }
                        if (i==n && j==m && c!=col[m-1] && c!=col[m+1] && col[m+1]!=-1) continue;
                        if (c==col1 && c==col3 && A[id1]==A[id3] && !(i==n && j==m)) continue;
                        memcpy(B+1,A+1,(m+1)*sizeof(int));
                        if (c==col1 && c!=col3) B[j]=A[id1];
                        else if (c!=col1 && c==col3) B[j]=A[id3];
                        else if (c==col1 && c==col3)
                        {
                            B[j]=A[id1];B[id3]=A[id1];
                            rep(k,id3+1,m+1)
                            {
                                if (col[k]==c && B[k]==A[id3]) B[k]=A[id1];
                                if (col[k]==c && B[k]>A[id3]) B[k]--;
                            }
                        }
                        else
                        {
                            assert(c!=col1 && c!=col3);int maxn;
                            if (c==0) maxn=0; else maxn=6;
                            rep(k,1,id1) if (col[k]==c) maxn=max(maxn,B[k]);
                            maxn++;B[j]=maxn;
                            rep(k,id3+1,m+1) if (col[k]==c && B[k]>=maxn) B[k]++;
                        }
                        ull sta=Encode(B);
                        Add(cur[sta],iter->second);
                        /*
                        if (i==3 && j==2)
                        {
                            rep(k,1,5) cerr<<A[k]<<' ';cerr<<endl;
                            cerr<<c<<endl;
                            rep(k,1,5) cerr<<B[k]<<' ';cerr<<endl;
                            cerr<<"---------"<<endl;
                        }
                        */
                    }
                }
                if (i==3 && j==3) cerr<<cnt<<"!"<<endl;
                pre=cur;cur.clear();
                
            }
            for (unordered_map<ull,int>::iterator iter=pre.begin();iter!=pre.end();iter++)
                cur[iter->first<<4]=iter->second;
            pre=cur;cur.clear();
        }
        int ans=0;
        for (unordered_map<ull,int>::iterator iter=pre.begin();iter!=pre.end();iter++)
        {
            Decompose(iter->first,A);bool f=true;
            rep(i,2,m+1) if (A[i]!=1 && A[i]!=7) {f=false;break;}
            if (f) Add(ans,iter->second);
        }
        printf("%d\n",ans);
    }
    return 0;
}