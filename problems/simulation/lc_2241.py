from typing import List


class ATM:

    def __init__(self):
        self.deno = [20, 50, 100, 200, 500]
        self.bank = [0] * 5

    def deposit(self, banknotesCount: List[int]) -> None:
        for i, cnt in enumerate(banknotesCount):
            self.bank[i] += cnt

    def withdraw(self, amount: int) -> List[int]:
        ans = [0] * 5
        for i in range(4, -1, -1):
            ans[i] += min(self.bank[i], amount // self.deno[i])
            amount -= ans[i] * self.deno[i]
        if amount != 0:
            return [-1]
        self.bank = [a - b for a, b in zip(self.bank, ans)]
        return ans


# Your ATM object will be instantiated and called as such:
obj = ATM()
obj.deposit([0, 0, 1, 2, 1])
assert [0, 0, 1, 0, 1] == obj.withdraw(600)
