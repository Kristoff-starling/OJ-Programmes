class Solution:
    def smallestDistancePair(self, nums: List[int], k: int) -> int:
        def count(mid):
            cnt = 0
            for r, num in enumerate(nums):
                l = bisect_left(nums, num - mid, 0, r)
                cnt += r - l
            return cnt
        
        nums = sorted(nums)
        return bisect_left(range(nums[-1] - nums[0]), k, key=count)