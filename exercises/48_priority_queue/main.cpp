#include "../exercise.h"
#include <functional>
#include <queue>
#include <string>
#include <vector>

// READ: std::priority_queue <https://zh.cppreference.com/w/cpp/container/priority_queue>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 默认情况下，std::priority_queue 是一个最大堆（最大的元素在顶部）
    std::priority_queue<int> max_heap;

    ASSERT(max_heap.empty(), "优先队列初始应为空");
    ASSERT(max_heap.size() == 0, "优先队列初始大小应为 0");

    // 推入元素
    max_heap.push(10);
    max_heap.push(30);
    max_heap.push(20);

    ASSERT(!max_heap.empty(), "推入元素后不应为空");
    ASSERT(max_heap.size() == 3, "推入三个元素后的大小");

    // 查看顶部元素 (最大值)
    ASSERT(max_heap.top() == 30, "最大堆的顶部元素");

    // 弹出顶部元素
    max_heap.pop();
    ASSERT(max_heap.size() == 2, "弹出一个元素后的大小");
    ASSERT(max_heap.top() == 20, "弹出最大元素后的顶部元素");

    max_heap.pop();
    ASSERT(max_heap.top() == 10, "再弹出一个元素后的顶部元素");

    max_heap.pop();
    ASSERT(max_heap.empty(), "弹出所有元素后应为空");
    ASSERT(max_heap.size() == 0, "弹出所有元素后的大小");

    // 创建一个最小堆（最小的元素在顶部）
    // 需要提供底层容器类型 (std::vector<int>) 和比较函数类型 (std::greater<int>)
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

    min_heap.push(10);
    min_heap.push(30);
    min_heap.push(20);

    ASSERT(min_heap.size() == 3, "最小堆的大小");
    ASSERT(min_heap.top() == 10, "最小堆的顶部元素");

    min_heap.pop();
    ASSERT(min_heap.top() == 20, "弹出最小元素后的顶部元素");

    min_heap.pop();
    ASSERT(min_heap.top() == 30, "再弹出一个元素后的顶部元素");

    // 使用现有容器初始化优先队列
    std::vector<std::string> data = {"apple", "banana", "cherry"};
    std::priority_queue<std::string> fruit_heap(data.begin(), data.end());

    ASSERT(fruit_heap.size() == 3, "从 vector 初始化的优先队列大小");
    ASSERT(fruit_heap.top() == "cherry", "字符串最大堆的顶部元素 (字典序)");

    fruit_heap.pop();
    ASSERT(fruit_heap.top() == "banana", "弹出字典序最大元素后的顶部元素");

    return 0;
}