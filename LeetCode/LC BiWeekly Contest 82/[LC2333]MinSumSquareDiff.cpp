class Solution {
    priority_queue<pair<int,int> > q;
    int myabs(int x) {return x>=0 ? x : -x;}
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = int(nums1.size());
        for (int i = 0; i < n; i++) q.push(make_pair(myabs(nums1[i] - nums2[i]), 1));
        int k = k1 + k2;
        if (n == 1)
        {
            int val = myabs(nums1[0] - nums2[0]);
            if (val > k) return 1ll * (val - k) * (val - k); else return 0; 
        }
        for (;;)
        {
            int cur = q.top().first, cnt = q.top().second; q.pop();
            if (cur == 0) return 0;
            if (q.empty())
            {
                if (k >= 1ll * cur * cnt) return 0;
                int round = k / cnt, rem = k % cnt;
                long long ans = 0;
                for (int i = 1; i <= rem; i++) ans += 1ll * (cur - round - 1) * (cur - round - 1);
                for (int i = 1; i <= cnt - rem; i++) ans += 1ll * (cur - round) * (cur - round);
                return ans;
            }
            int nxt = q.top().first;
            long long step = 1ll * (cur - nxt) * cnt;
            if (k <= step)
            {
                int round = k / cnt, rem = k % cnt;
                long long ans = 0;
                for (int i = 1; i <= rem; i++) ans += 1ll * (cur - round - 1) * (cur - round - 1);
                for (int i = 1; i <= cnt - rem; i++) ans += 1ll * (cur - round) * (cur - round);
                while (!q.empty())
                {
                    cur = q.top().first; cnt = q.top().second; q.pop();
                    ans += 1ll * cur * cur * cnt;
                }
                return ans;
            }
            else
            {
                k -= step;
                int cnt2 = q.top().second;
                cnt += cnt2; cur = nxt;
                q.pop();
                q.push(make_pair(cur, cnt));
            }
        }
    }
};