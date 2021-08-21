#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define LL long long
#define ll long long
using namespace std;

const int MOD=998244353;
const int MAXN=3e5;

int n,a[MAXN+48],sum[MAXN+48];

template<typename T> T add(T x,int MO) {if (x>=MO) x-=MO;return x;}
template<typename T> T sub(T x,int MO) {if (x<0) x+=MO;return x;}

namespace mtt
{
    #define db double
    #define op com operator
    #define con const
    const int N = 300000;
    const db Pi = acos(-1.0);
    const int P=MOD-1;
    int lim = 1, L;
    int r[N];
    struct com {
        db x, y;
        com(db a = 0, db b = 0) : x(a) , y(b) {}
        op + (con com &w) con { return com(x + w.x, y + w.y); }
        op - (con com &w) con { return com(x - w.x, y - w.y); }
        op * (con com &w) con { return com(x * w.x - y * w.y, x * w.y + y * w.x); }
        op * (con double w) con { return com(x * w, y * w); }
        op - (void) con { return com(-x, -y); }
        com conj() con { return com(x, -y); }
        com mi() con { return com(-y, x); }
    }A[N], C[N], E[N];


    void dft(com *A) {
        for (int i = 1;i < lim; i++)
            if (r[i] > i) swap(A[i], A[r[i]]);
        if (lim >= 2) 
        for (int j = 0;j < lim; j += 2) {
            com x = A[j], y = A[j+1];
            A[j] = x + y, A[j+1] = x - y;
        }
        if (lim >= 4)
        for (int j = 0;j < lim; j += 4) {
            com x = A[j], y = A[j+2];
            A[j] = x + y, A[j+2] = x - y;
            x = A[j+1], y = A[j+3].mi();
            A[j+1] = x + y, A[j+3] = x - y;
        }
        if (lim >= 8)
        for (int j = 0;j < lim; j += 8) {
            com x = A[j], y = A[j+4];
            A[j] = x + y, A[j+4] = x - y;
            x = A[j+1], y = A[j+5] * E[5];
            A[j+1] = x + y, A[j+5] = x - y;
            x = A[j+2], y = A[j+6].mi();
            A[j+2] = x + y, A[j+6] = x - y;
            x = A[j+3], y = A[j+7] * E[7];
            A[j+3] = x + y, A[j+7] = x - y;
        }
        for (int i = 8;i < lim; i <<= 1) {
            for (int j = 0;j < lim; j += (i << 1)) {
                com *f = A + j, *g = f + i, *e = E + i;
                for (int k = 0;k < i; k++) {
                    com x = f[k], y = g[k] * e[k];
                    f[k] = x + y, g[k] = x - y;
                    k++;
                    x = f[k], y = g[k] * e[k];
                    f[k] = x + y, g[k] = x - y;
                }
            }
        }
    }

    void idft(com *A) { dft(A), reverse(A + 1, A + lim); }
    void poly_mtt(int p1[],int p2[],int nn,int mm)
    {
        nn--;mm--;L=0;
        lim=1;while (lim<=nn+mm) lim<<=1,L++;
        rep(i,0,lim) A[i].x=A[i].y=0,C[i].x=C[i].y=0,E[i].x=E[i].y=0;
        for (int i = 1;i < lim; i++)
		    r[i] = (r[i>>1]>>1) | ((i & 1) << (L - 1));
        E[1] = com(1, 0);
        for (int i = 2;i < lim; i <<= 1) {
            com *e0 = E + i / 2, *e1 = E + i;
            com w(cos(Pi / i), sin(Pi / i));
            for (int j = 0;j < i; j += 2) 
                e1[j] = e0[j>>1], e1[j+1] = e1[j] * w;
        }
        rep(i,0,nn) A[i]=com(p1[i]>>15,p1[i]&0x7fff);
        rep(i,0,mm) C[i]=com(p2[i]>>15,p2[i]&0x7fff);
        dft(A), dft(C);
        com a = (A[0] + A[0].conj()) * 0.5;
        com b = (A[0] - A[0].conj()) * com(0, -0.5);
        com c = (C[0] + C[0].conj()) * 0.5;
        com d = (C[0] - C[0].conj()) * com(0, -0.5);
        A[0] = a * c + (a * d + b * c) * com(0, 1), C[0] = b * d; 
        for (int i = 1;i <= (lim >> 1); i++) {
            int k = lim - i;
            a = (A[i] + A[k].conj()) * 0.5;
            b = (A[i] - A[k].conj()) * com(0, -0.5);
            c = (C[i] + C[k].conj()) * 0.5;
            d = (C[i] - C[k].conj()) * com(0, -0.5);
            com t1 = a * c + (a * d + b * c) * com(0, 1), t2 = b * d;
            swap(k, i);
            a = (A[i] + A[k].conj()) * 0.5;
            b = (A[i] - A[k].conj()) * com(0, -0.5);
            c = (C[i] + C[k].conj()) * 0.5;
            d = (C[i] - C[k].conj()) * com(0, -0.5);
            A[i] = a * c + (a * d + b * c) * com(0, 1), C[i] = b * d;
            A[i = k] = t1, C[i] = t2;
        }
        idft(A), idft(C);
        for (int i = 0;i <= nn + mm; i++) {
            ll ax = (ll)(A[i].x / lim + 0.5) % P;
            ll ay = (ll)(A[i].y / lim + 0.5);
            ll bx = (ll)(C[i].x/lim+0.5);
            
            ll ans = ax << 30;
            ans = (ans + (ay << 15));
            ans=(ans+bx)%P;
            p1[i]=ans;
        }
    }
}

int tmp[MAXN+48],A[MAXN+48],B[MAXN+48];
void solve(int l,int r)
{
    if (l==r) {rep(i,0,a[l]) tmp[i]=0;tmp[0]=1;tmp[a[l]]=1;return;}
    int mid=(l+r)>>1;
    int N=sum[mid]-sum[l-1]+1,M=sum[r]-sum[mid]+1;
    int len=1;while (len<=N+M) len<<=1;
    int Tmp[len+48];
    solve(l,mid);memcpy(Tmp,tmp,N*sizeof(int));
    solve(mid+1,r);
    memcpy(A,Tmp,N*sizeof(int));memcpy(B,tmp,M*sizeof(int));
    // poly::poly_mul(A,B,N,M);
    mtt::poly_mtt(A,B,N,M);
    memcpy(tmp,A,len*sizeof(int));
}

int quick_pow(int x,int y)
{
    int res=1;
    while (y)
    {
        if (y&1) res=1ll*res*x%MOD;
        x=1ll*x*x%MOD;y>>=1;
    }
    return res;
}

int main ()
{
    int ca;scanf("%d",&ca);
    while (ca--)
    {
        scanf("%d",&n);rep(i,1,n) scanf("%d",a+i);
        sum[0]=0;rep(i,1,n) sum[i]=sum[i-1]+a[i];
        bool f=false;
        rep(i,1,n) if (a[i]==0) {f=true;break;}
        if (f) {puts("0");continue;}
        solve(1,n);
        int ans=1;
        rep(i,1,sum[n]) ans=1ll*ans*quick_pow(i,tmp[i])%MOD;
        printf("%d\n",ans);
    }
    return 0;
}