#include "../exercise.h"
#include <queue>
#include <string>

// READ: std::queue <https://zh.cppreference.com/w/cpp/container/queue>

// TODO：自己实现一个队列类
// TIPS:
// 1. 队列是一种先进先出 (FIFO) 的数据结构
// 2. 队列应该支持以下操作：
//    - 入队 (push)：将元素添加到队列尾部
//    - 出队 (pop)：移除队列头部的元素
//    - 获取队首元素 (front)：返回队列头部的元素，但不移除它
//    - 获取队尾元素 (back)：返回队列尾部的元素，但不移除它
//    - 判断队列是否为空 (empty)：检查队列是否不包含任何元素
//    - 获取队列的大小 (size)：返回队列中元素的数量
//    - 清空队列 (clear)：移除队列中的所有元素
template <typename T>
class MyQueue {
private:
    //?
    std::deque<T> dq;
public:
    //?
    void push(T t) {
        dq.push_back(t);
    }
    void pop() {
        dq.pop_front();
    }
    T front() {
        return dq.front();
    }
    T back() {
        return dq.back();
    }
    bool empty() {
        return dq.empty();
    }
    auto size() -> decltype(dq.size()) {
        return dq.size();
    }
    void clear() {
        dq.clear();
    }
};


int main(int argc, char **argv) {
    // std::queue<std::string> q;
    // TODO：使用自己实现的队列类进行测试
    MyQueue<std::string> q;
    ASSERT(q.empty(), "queue should be empty initially");
    ASSERT(q.size() == 0, "queue size should be 0 initially");

    // TODO: 入队 "Hello"
    q.push("Hello");
    ASSERT(!q.empty(), "queue should not be empty after push");
    ASSERT(q.size() == 1, "queue size should be 1 after push");
    ASSERT(q.front() == "Hello", "front element should be \"Hello\"");
    ASSERT(q.back() == "Hello", "back element should be \"Hello\"");

    // TODO: 入队 "World"
    q.push("World");
    ASSERT(q.size() == 2, "queue size should be 2 after second push");
    ASSERT(q.front() == "Hello", "front element should still be \"Hello\"");
    ASSERT(q.back() == "World", "back element should be \"World\"");

    // TODO:  入队 "!"
    q.push("!");
    ASSERT(q.size() == 3, "queue size should be 3 after third push");
    ASSERT(q.front() == "Hello", "front element should still be \"Hello\"");
    ASSERT(q.back() == "!", "back element should be \"!\"");

    // TODO: 出队
    q.pop();
    ASSERT(q.size() == 2, "queue size should be 2 after pop");
    ASSERT(q.front() == "World", "front element should be \"World\" after pop");
    ASSERT(q.back() == "!", "back element should still be \"!\"");

    // 修改队首元素（NOTICE：queue 不直接支持修改，需要先出队再入队）
    // 实际应用中，如果需要修改，可能需要其他数据结构或操作方式
    // 这里我们模拟修改队首：先出队，再入队新元素
    q.pop(); // 出队 "World"
    q.push("C++"); // 入队 "C++"
    ASSERT(q.size() == 2, "queue size should be 2 after pop and push");
    ASSERT(q.front() == "!", "front element should be \"!\" now");
    ASSERT(q.back() == "C++", "back element should be \"C++\" now");

    // 继续出队
    q.pop(); // 出队 "!"
    ASSERT(q.size() == 1, "queue size should be 1 after second pop");
    ASSERT(q.front() == "C++", "front element should be \"C++\"");
    ASSERT(q.back() == "C++", "back element should be \"C++\"");

    //TODO: 出队 "C++"
    q.pop();
    ASSERT(q.empty(), "queue should be empty after final pop");
    ASSERT(q.size() == 0, "queue size should be 0 after final pop");

    return 0;
}