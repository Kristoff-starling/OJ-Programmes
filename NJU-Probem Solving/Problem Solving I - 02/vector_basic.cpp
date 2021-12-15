#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define REP(i,a,b) for (int i=a;i>=b;i--)

struct Matrix
{
    vector<vector<int> > m;
    Matrix () {m.clear();}
    inline void Set(int N,int M)
    {
        vector<int> tmp;rep(i,1,M+1) tmp.pb(0);
        rep(i,1,N+1) m.pb(tmp);
    }
    inline void input(int N,int M)
    {
        rep(i,1,N) rep(j,1,M) scanf("%d",&m[i][j]);
    }
    inline void Print()
    {
        int N=int(m.size())-1,M=int(m[0].size())-1;
        rep(i,1,N)
        {
            rep(j,1,M-1) printf("%d ",m[i][j]);
            printf("%d\n",m[i][M]);
        }
    }
    inline Matrix operator + (const Matrix &other) const
    {
        Matrix res=(*this);int N=int(m.size())-1,M=int(m[0].size())-1;
        rep(i,1,N) rep(j,1,M) res.m[i][j]+=other.m[i][j];
        return res;
    }
    inline Matrix operator - (const Matrix &other) const
    {
        Matrix res=(*this);int N=int(m.size())-1,M=int(m[0].size())-1;
        rep(i,1,N) rep(j,1,M) res.m[i][j]-=other.m[i][j];
        return res;
    }
    inline Matrix operator * (const Matrix &other) const
    {
        Matrix res;int N=int(m.size())-1,M=int(other.m.size())-1,K=int(other.m[0].size())-1;res.Set(N,K);
        rep(i,1,N) rep(j,1,K) rep(k,1,M) res.m[i][j]+=m[i][k]*other.m[k][j];
        return res;
    }
    inline Matrix Transpose()
    {
        Matrix res;int N=int(m.size())-1,M=int(m[0].size())-1;
        vector<int> tmp;rep(i,1,N+1) tmp.pb(0);res.m.pb(tmp);
        rep(j,1,M)
        {
            tmp.clear();tmp.pb(0);
            rep(i,1,N) tmp.pb(m[i][j]);
            res.m.pb(tmp);
        }
        return res;
    }
}A,B;

int main ()
{
    int n,m;scanf("%d%d",&n,&m);
    A.Set(n,m);B.Set(n,m);A.input(n,m);B.input(n,m);
    (A+B).Print();puts("");(A-B).Print();puts("");(A*B.Transpose()).Print();
    return 0;
}