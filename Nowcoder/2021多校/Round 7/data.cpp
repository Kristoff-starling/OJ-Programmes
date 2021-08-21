#include <bits/stdc++.h>
using namespace std;

int n=3e5;

int main ()
{
    freopen ("a.in","w",stdout);
    int t=3;
    cout<<t<<endl;
    while (t--)
    {
        cout<<n<<endl;
        for (int i=2;i<=n;i++)
            cout<<i<<' '<<i-1<<endl;
        for (int i=2;i<=n;i++)
            cout<<i<<' '<<rand()*100%(i-1)+1<<endl;
    }
    return 0;
}