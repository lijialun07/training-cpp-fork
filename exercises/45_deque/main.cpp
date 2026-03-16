#include "../exercise.h"
#include <deque>
#include <iostream>

// READ: std::deque <https://zh.cppreference.com/w/cpp/container/deque>
// READ: deque原理 <https://lb3fn675fh.feishu.cn/wiki/Hn66w7lDciYWLRkJIYfcuTQ5ncg>

int main(int argc, char **argv) {
    // TODO: 初始化一个空的 std::deque<int> deq
    std::deque<int> deq;
    ASSERT(deq.empty(), "deque should be empty initially");

    // TODO: 在 deq 前端添加 10
    deq.push_front(10);
    ASSERT(deq.front() == 10, "front element should be 10");

    // TODO: 在 deq 后端添加 20
    deq.push_back(20);
    ASSERT(deq.back() == 20, "back element should be 20");

    // TODO: 在 deq 前端添加 5
    deq.push_front(5);
    ASSERT(deq.front() == 5, "front element should be 5");
    ASSERT(deq.size() == 3, "deque size should be 3");
    ASSERT(deq[0] == 5, "element at index 0 should be 5");
    ASSERT(deq[1] == 10, "element at index 1 should be 10");
    ASSERT(deq[2] == 20, "element at index 2 should be 20");

    // TODO: 从 deq 前端移除一个元素
    deq.pop_front();
    ASSERT(deq.front() == 10, "front element should be 10 after pop_front");
    ASSERT(deq.size() == 2, "deque size should be 2 after pop_front");

    // TODO: 从 deq 后端移除一个元素
    deq.pop_back();
    ASSERT(deq.back() == 10, "back element should be 10 after pop_back");
    ASSERT(deq.size() == 1, "deque size should be 1 after pop_back");

    // TODO: 修改 deq 中索引为 0 的元素为 100
    deq[0] = 100;
    ASSERT(deq[0] == 100, "element at index 0 should be 100");

    // TODO: 清空 deq
    deq.clear();
    ASSERT(deq.empty(), "deque should be empty after clear");

    return 0;
}