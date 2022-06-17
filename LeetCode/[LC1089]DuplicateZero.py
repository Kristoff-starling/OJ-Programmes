class Solution:
    def duplicateZeros(self, arr: List[int]) -> None:
        pt1, pt2, n = -1, 0, len(arr)
        while pt2 < n:
            pt1 += 1
            if arr[pt1] == 0: pt2 += 2
            else: pt2 += 1
        while pt1 >= 0:
            pt2 -= 1
            if pt2 < n: arr[pt2] = arr[pt1]
            if arr[pt1] == 0:
                pt2 -= 1
                if pt2 < n: arr[pt2] = arr[pt1]
            pt1 -= 1