class Solution:
    def numberOfLines(self, widths: List[int], s: str) -> List[int]:
        lcnt, wcnt = 0, 100
        for ch in s:
            wcnt += widths[ord(ch) - 97]
            if wcnt > 100:
                lcnt += 1
                wcnt = widths[ord(ch) - 97]
        return [lcnt, wcnt]