class Solution:
    def minMutation(self, start: str, end: str, bank: List[str]) -> int:
        bank = set(bank)
        if not end in bank: return -1
        q = [(start, 0)]
        gene = 'ATCG'
        while q:
            cur, cnt = q.pop(0)
            if cur == end: return cnt
            for i, v in enumerate(cur):
                for ch in gene:
                    if ch != v:
                        nxt = cur[:i] + ch + cur[i+1:]
                        if nxt in bank:
                            q.append((nxt, cnt+1))
                            bank.remove(nxt)
        return -1