#include <iostream>
#include <memory>
#include <stack>

class MinStack
{
public:
  MinStack() = default;

  void push(int val)
  {
    if (stack.empty()) {
      minStack.push(val);
    } else {
      minStack.push(std::min(minStack.top(), val));
    }
    stack.push(val);
  }

  void pop()
  {
    stack.pop();
    minStack.pop();
  }

  int top()
  {
    return stack.top();
  }

  int getMin()
  {
    return minStack.top();
  }

private:
  std::stack<int> minStack;
  std::stack<int> stack;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::unique_ptr<MinStack> obj = std::make_unique<MinStack>();
  obj->push(-2);
  obj->push(0);
  obj->push(-3);
  std::cout << obj->getMin() << std::endl;
  obj->pop();
  std::cout << obj->top() << std::endl;
  std::cout << obj->getMin() << std::endl;
  return 0;
}