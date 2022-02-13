class Solution {
    #define LL long long
    priority_queue<LL> q;
    set<LL> s;
    void push(LL x) {if (s.find(x)==s.end()) s.insert(x),q.push(-x);}
public:
    int nthUglyNumber(int n) {
        q.push(-1);s.insert(1);
        for (int cnt=1;;cnt++)
        {
            LL x=-q.top();q.pop();
            s.erase(x);
            if (cnt==n) return x;
            push(x*2);push(x*3);push(x*5);
        }
        return 0;
    }
};