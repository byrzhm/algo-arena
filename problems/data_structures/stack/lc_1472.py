from typing import List


class BrowserHistory:

    def __init__(self, homepage: str):
        self.history: List[str] = [homepage]
        self.index: int = 0
        self.length: int = 1

    def visit(self, url: str) -> None:
        self.index += 1
        if len(self.history) == self.index:
            self.history.append(url)
        else:
            self.history[self.index] = url
        self.length = self.index + 1
        print("visit: ", self.history[:self.length])

    def back(self, steps: int) -> str:
        x = min(self.index, steps)
        self.index -= x
        print("back: ", self.history[:self.length])
        return self.history[self.index]

    def forward(self, steps: int) -> str:
        x = min(steps, self.length - self.index - 1)
        self.index += x
        print("forward: ", self.history[:self.length])
        return self.history[self.index]


# Your BrowserHistory object will be instantiated and called as such:
# obj = BrowserHistory(homepage)
# obj.visit(url)
# param_2 = obj.back(steps)
# param_3 = obj.forward(steps)
