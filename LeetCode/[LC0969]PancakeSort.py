class Solution:
    def pancakeSort(self, arr: List[int]) -> List[int]:
        ans = []
        l = len(arr)
        for t in range(1, l):
            pos = arr.index(max(arr))
            ans.append(pos+1)
            ans.append(l-t+1)
            arr = (arr[pos::-1] + arr[pos+1::])[::-1]
            arr.pop()
        return ans