class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n=int(nums.size()),l=0,r=n-1,mid,ll,rr;
        if (n==1) return nums[0];
        while (l<r)
        {
            mid=(l+r)>>1;
            if (nums[mid-1]!=nums[mid] && nums[mid]!=nums[mid+1]) return nums[mid];
            if (nums[mid-1]==nums[mid]) ll=mid-2,rr=mid+1; else ll=mid-1,rr=mid+2;
            if ((ll-l+1)&1) r=ll; else l=rr;
        }
        return nums[l];
    }
};