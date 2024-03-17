class Solution:
    def isSubstringPresent(self, s: str) -> bool:
        n = len(s)
        visit = set()
        for i in range(n - 1):
            sub = s[i:i+2]
            visit.add(sub[:])
            sub = sub[::-1]
            if sub in visit:
                return True
            
        return False