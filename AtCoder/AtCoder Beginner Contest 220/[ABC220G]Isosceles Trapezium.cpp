#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL __int128
using namespace std;

struct frac
{
    template<typename T> T mygcd(T x,T y) {return y==0?x:mygcd(y,x%y);}
    template<typename T> T myabs(T x) {if (x>=0) return x; else return -x;}
    LL num,den;bool inf;
    frac (LL num=0,LL den=1,bool inf=false)
    {
        if (inf)
        {
            this->num=num;
            this->den=den;
            this->inf=inf;
            return;
        }
        if (den==1) {this->num=num;this->den=den;this->inf=inf;return;}
        if (den<0) num=-num,den=-den;
        assert(den!=0);
        LL g=mygcd(myabs(num),den);
        this->num=num/g;this->den=den/g;this->inf=inf;
    }
    frac operator + (const frac &other) const
    {
        if (den==1 && other.den==1) return frac(num+other.num,1);
        return frac(num*other.den+den*other.num,den*other.den,false);
    }
    frac operator - (const frac &other) const
    {
        if (den==1 && other.den==1) return frac(num-other.num,1);
        return frac(num*other.den-den*other.num,den*other.den,false);
    }
    frac operator * (const frac &other) const {return frac(num*other.num,den*other.den,false);}
    frac operator / (const frac &other) const {return frac(num*other.den,den*other.num,false);}
    bool operator <  (const frac &other) const
    {
        if (inf) return false;
        if (other.inf) return true;
        return num*other.den<den*other.num;
    }
    bool operator == (const frac &other) const
    {
        if (inf && other.inf) return true;
        if (inf || other.inf) return false;
        return num*other.den==den*other.num;
    }
    bool operator <= (const frac &other) const
    {
        if (inf && other.inf) return true;
        if (inf) return false;
        if (other.inf) return true;
        return num*other.den<=den*other.num;
    }
};

const int MAXN=1000;

int n,C[MAXN+48];frac X[MAXN+48],Y[MAXN+48];

struct line
{
    frac x,k,xx,yy;LL val;
    line () {}
    line (frac _x,frac _k,frac _xx,frac _yy,LL _v) {x=_x;k=_k;xx=_xx;yy=_yy;val=_v;}
    bool operator < (const line &other) const
    {
        if (!(x==other.x)) return x<other.x;
        if (!(k==other.k)) return k<other.k;
        if (!(xx==other.xx)) return xx<other.xx;
        if (!(yy==other.yy)) return yy<other.yy;
        return val<other.val;
    }
}a[1000048],b[1000048];int btot;

int main ()
{
    int tt,pp;
    scanf("%d",&n);rep(i,1,n) scanf("%d%d%d",&tt,&pp,C+i),X[i].num=tt,Y[i].num=pp,X[i].den=Y[i].den=1,X[i].inf=Y[i].inf=false;
    int tot=0;
    rep(i,1,n-1) rep(j,i+1,n)
    {
        frac xx=(X[i]+X[j])/frac(2,1,false),yy=(Y[i]+Y[j])/frac(2,1,false);
        __int128 dx=X[i].num-X[j].num,dy=Y[i].num-Y[j].num;
        swap(dx,dy);dy=-dy;
        if (dy==0)
        {
            a[++tot]=line(yy,frac(0,0,true),xx,yy,C[i]+C[j]);
        }
        else
        { 
            frac xxx=frac(dx,dy)*yy*frac(-1,1,false)+xx;
            a[++tot]=line(xxx,frac(dx,dy,false),xx,yy,C[i]+C[j]);
        }
    }
    sort(a+1,a+tot+1);
    LL ans=-1;
    rep(i,1,tot) if (i==tot || !(a[i].x==a[i+1].x && a[i].k==a[i+1].k && a[i].xx==a[i+1].xx && a[i].yy==a[i+1].yy)) b[++btot]=a[i],b[btot].xx=b[btot].yy=frac(1,1,false);
    sort(b+1,b+btot+1);
    rep(i,1,btot-1) if (b[i].x==b[i+1].x && b[i].k==b[i+1].k) ans=max(ans,b[i].val+b[i+1].val);
    long long tmp=ans;
    printf("%lld\n",tmp);return 0;
}