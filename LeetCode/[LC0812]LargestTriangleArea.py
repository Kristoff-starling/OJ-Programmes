class Solution:
    def largestTriangleArea(self, points: List[List[int]]) -> float:
        ans = 0
        for p1 in points:
            for p2 in points:
                for p3 in points:
                    x1, y1 = p2[0] - p1[0], p2[1] - p1[1]
                    x2, y2 = p3[0] - p1[0], p3[1] - p1[1]
                    ans = max(ans, abs(x1 * y2 - x2 * y1) / 2)
        return ans