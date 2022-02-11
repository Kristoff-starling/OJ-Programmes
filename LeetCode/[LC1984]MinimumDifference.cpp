class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());int ans=1000000;
        for (int i=0;i+k-1<=int(nums.size())-1;i++) ans=min(ans,nums[i+k-1]-nums[i]);
        return ans;
    }
};