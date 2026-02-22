# We enumerate k1, k2 (k1 + k2 = k), choose k1 elements from nums1 and k2 elements from nums2, and merge them.
# To choose k1/k2 elements from nums1/nums2, we use a greedy algorithm: as long as the remaining elements is enough to form a number with k1/k2 digits, we choose the largest digit.
# To merge two arrays to form the largeest number, we always choose the digit from the side with larger lexicographical order.
class Solution:
    def maxNumber(self, nums1: List[int], nums2: List[int], k: int) -> List[int]:
        def choose(arr: List[int], k: int) -> List[int]:
            n = len(arr)
            nxt = [[n] * 10 for _ in range(n + 1)]
            for i in range(n - 1, -1, -1):
                for j in range(10):
                    nxt[i][j] = nxt[i + 1][j]
                nxt[i][arr[i]] = i
            ans = []
            pt = 0
            for _ in range(k):
                for digit in range(9, -1, -1):
                    pos = nxt[pt][digit]
                    if pos <= n - 1 and len(ans) + 1 + (n - 1 - pos) >= k:
                        ans.append(digit)
                        pt = pos + 1
                        break
            return ans
        def merge(arr1: List[int], arr2: List[int]) -> List[int]:
            ans = []
            n, m = len(arr1), len(arr2)
            arr1 += [-1]
            arr2 += [-1]
            pt1, pt2 = 0, 0
            while pt1 + pt2 < n + m:
                pp1, pp2 = pt1, pt2
                while pp1 < len(arr1) and pp2 < len(arr2) and arr1[pp1] == arr2[pp2]:
                    pp1 += 1
                    pp2 += 1
                if pp1 >= len(arr1) or arr1[pp1] > arr2[pp2]:
                    ans.append(arr1[pt1])
                    pt1 += 1
                else:
                    ans.append(arr2[pt2])
                    pt2 += 1
            return ans
        def update(arr1: List[int], arr2: List[int]) -> List[int]:
            if len(arr1) != len(arr2):
                print(arr1, arr2)
            assert len(arr1) == len(arr2)
            for i in range(len(arr1)):
                if arr1[i] > arr2[i]:
                    return arr1
                elif arr1[i] < arr2[i]:
                    return arr2
            return arr1
        ans = [0] * k
        for i in range(k + 1):
            if i <= len(nums1) and k - i <= len(nums2):
                ans1 = choose(nums1, i)
                ans2 = choose(nums2, k - i)
                candidate = merge(ans1, ans2)
                ans = update(ans, candidate)
        return ans