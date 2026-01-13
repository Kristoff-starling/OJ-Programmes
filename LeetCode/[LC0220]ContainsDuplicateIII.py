# An O(nlogk) solution is trivial via maintaing a balanced search tree on the k-length sliding window.
# The O(n) solution utilizes the property that we don't need to find the "closest" value to nums[cur], but whether there exist a value that is close enough (<= valueDiff). Therefore, we maintain buckets instead of BST on the sliding window.
# For nums[cur], we assign it to the bucket with idx = nums[cur] // (valueDiff + 1). If there's another value in this bucket, there difference must be <= valueDiff and we can return. (This property guarantees that at any time during checking, there's at most one value in each bucket.) 
# Otherwise, we only need to check bucket with index (idx + 1) and (idx - 1). Values in other buckets are too large or small for nums[cur],

class Solution:
    def containsNearbyAlmostDuplicate(self, nums: List[int], indexDiff: int, valueDiff: int) -> bool:
        from collections import defaultdict
        nums = [n + 10 ** 9 + 1 for n in nums]
        n = len(nums)
        buckets = defaultdict(int)
        for i in range(n):
            if i - indexDiff - 1 >= 0:
                b = nums[i - indexDiff - 1] // (valueDiff + 1)
                buckets[b] = 0
            b = nums[i] // (valueDiff + 1)
            if buckets[b] > 0:
                return True
            elif buckets[b - 1] > 0 and abs(buckets[b - 1] - nums[i]) <= valueDiff:
                return True
            elif buckets[b + 1] > 0 and abs(buckets[b + 1] - nums[i]) <= valueDiff:
                return True
            buckets[b] = nums[i]
        return False