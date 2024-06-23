#include <bits/stdc++.h>

const int MAXN = 2e5 + 10;

int n;
int a[MAXN];

std::priority_queue<int> q1, q2;

int main ()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    int op, x;
    while (n--)
    {
        std::cin >> op;
        if (op == 1)
        {
            std::cin >> x;
            if (!q1.empty() && q1.top() > x)
            {
                q2.push(-q1.top());
                q1.pop();
                q1.push(x);
            }
            else
                q2.push(-x);
        }
        else
        {
            q1.push(-q2.top());
            q2.pop();
            std::cout << q1.top() << '\n';
        }
    }
    return 0;
}