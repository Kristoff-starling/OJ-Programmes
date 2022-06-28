class Solution:
    def wiggleSort(self, nums: List[int]) -> None:
        arr = sorted(nums)
        l, r = (len(nums) + 1) // 2 - 1, len(nums) - 1
        for i in range(len(nums)):
            if i % 2 == 0:
                nums[i], l = arr[l], l - 1
            else:
                nums[i], r = arr[r], r - 1