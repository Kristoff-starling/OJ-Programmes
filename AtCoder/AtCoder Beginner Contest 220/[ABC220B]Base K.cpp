#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=a;i<=b;i++)
using namespace std;

int k;string a,b;

int main ()
{
    cin>>k>>a>>b;
    long long A=0,B=0;
    for (int i=0;i<int(a.size());i++) A=A*k+a[i]-'0';
    for (int i=0;i<int(b.size());i++) B=B*k+b[i]-'0';
    cout<<A*B<<endl;
    return 0;
}