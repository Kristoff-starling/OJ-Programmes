class Solution:
    def duplicateZeros(self, arr: List[int]) -> None:
        tmp, n = [], len(arr)
        for num in arr:
            if num != 0: tmp.append(num)
            else: tmp.append(num); tmp.append(num)
        for i in range(n): arr[i] = tmp[i]