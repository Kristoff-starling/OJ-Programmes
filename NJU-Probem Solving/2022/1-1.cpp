#include <bits/stdc++.h>
using namespace std;
 
int n, m;
 
int in[1000], out[1000];
 
int main ()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    string type, ph; int x;
    bool reachable = true;
    int current = 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> type;
        if (type == "BEGIN" || type == "INC" || type == "DEC" || type == "PRINT")
        {
            cin >> ph;
        }
        else if (type == "LABEL" || type == "END")
        {
            cin >> x;
            current = x;
            if (reachable) in[x]++, out[x - 1]++;
            reachable = true;
        }
        else if (type == "GOTO")
        {
            cin >> x;
            in[x]++;
            out[current]++;
            reachable = false;
        }
        else if (type == "IF")
        {
            cin >> ph;
            cin >> ph;
            cin >> ph;
            cin >> ph;
            cin >> x;
            in[x]++;
            out[current]++;
            if (x == current + 1) reachable = false;
        }
    }
    for (int i = 1; i <= m; i++) cout << in[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= m; i++) cout << out[i] << ' ';
    cout << '\n';
    return 0;
}