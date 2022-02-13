class Solution {
public:
    int jump(vector<int>& nums) {
        int n=int(nums.size()),cur=0,pt=0,maxn,maxpos;
        if (n==1) return 0;
        for (int cnt=1;;cnt++)
        {
            if (cur+nums[cur]>=n-1) return cnt;
            for (maxn=0;pt<=cur+nums[cur];pt++)
                if (pt+nums[pt]>maxn) maxn=pt+nums[pt],maxpos=pt;
            cur=maxpos;
        }
        return 0;
    }
};