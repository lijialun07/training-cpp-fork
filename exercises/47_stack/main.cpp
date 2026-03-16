#include "../exercise.h"
#include <stack>
#include <string>
#include <vector>

// READ: std::stack <https://zh.cppreference.com/w/cpp/container/stack>

// TODO: 实现一个 std::stack 类模板，支持以下操作：
// - push: 将元素压入栈顶
// - pop: 弹出栈顶元素
// - top: 返回栈顶元素的引用
// - empty: 判断栈是否为空
// - size: 返回栈中元素的个数
// - NOTICE：不允许使用 std::stack 等标准库容器
template <typename T>
class MyStack {
private:
    std::vector<T> data;

public:
    // TODO: 实现 push、pop、top、empty 和 size 等方法
    void push(const T &value) {
        data.push_back(value);
    }

    void pop() {
        data.pop_back();
    }

    T &top() {
        return data.back();
    }

    bool empty() {
        return data.size() == 0;
    }

    std::size_t size() {
        return data.size();
    }
};

int main(int argc, char **argv) {
    // std::stack<std::string> s;
    // TODO: 替换自己的MyStack
    MyStack<std::string> s;
    ASSERT(s.empty(), "stack should be empty initially");
    ASSERT(s.size() == 0, "stack size should be 0 initially");

    // TODO: 入栈 "Hello"
    s.push("Hello");
    ASSERT(!s.empty(), "stack should not be empty after push");
    ASSERT(s.size() == 1, "stack size should be 1 after push");
    ASSERT(s.top() == "Hello", "top element should be \"Hello\"");

    // TODO: 入栈 "World"
    s.push("World");
    ASSERT(s.size() == 2, "stack size should be 2 after second push");
    ASSERT(s.top() == "World", "top element should be \"World\"");

    // TODO: 入栈 "!"
    s.push("!");
    ASSERT(s.size() == 3, "stack size should be 3 after third push");
    ASSERT(s.top() == "!", "top element should be \"!\"");

    // TODO: 出栈
    s.pop();
    ASSERT(s.size() == 2, "stack size should be 2 after pop");
    ASSERT(s.top() == "World", "top element should be \"World\" after pop");

    // 继续出栈
    s.pop();
    ASSERT(s.size() == 1, "stack size should be 1 after second pop");
    ASSERT(s.top() == "Hello", "top element should be \"Hello\" after second pop");

    s.pop();
    ASSERT(s.empty(), "stack should be empty after final pop");
    ASSERT(s.size() == 0, "stack size should be 0 after final pop");

    // NOTICE:
    // 尝试访问空栈的栈顶元素（会导致未定义行为，通常是程序崩溃）
    // 在实际代码中应避免这种情况，总是在访问 top() 前检查 empty()

    return 0;
}