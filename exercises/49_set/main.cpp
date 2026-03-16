#include "../exercise.h"
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// READ: std::set <https://zh.cppreference.com/w/cpp/container/set>
// READ: std::unordered_set <https://zh.cppreference.com/w/cpp/container/unordered_set>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // ---- std::set ----
    // std::set 是一个有序集合，元素按升序排序（默认使用 std::less）
    std::set<int> ordered_set;

    ASSERT(ordered_set.empty(), "集合初始应为空");
    ASSERT(ordered_set.size() == 0, "集合初始大小应为 0");

    // 插入元素
    ordered_set.insert(30);
    ordered_set.insert(10);
    ordered_set.insert(20);
    ordered_set.insert(10);// 重复元素不会被插入

    ASSERT(!ordered_set.empty(), "插入元素后不应为空");
    ASSERT(ordered_set.size() == 3, "插入不重复元素后的集合大小");

    // 查找元素
    ASSERT(ordered_set.count(10) == 1, "检查元素 10 是否存在");
    ASSERT(ordered_set.count(40) == 0, "检查元素 40 是否存在");
    auto it_10 = ordered_set.find(10);
    ASSERT(it_10 != ordered_set.end() && *it_10 == 10, "找到元素 10");
    auto it_40 = ordered_set.find(40);
    ASSERT(it_40 == ordered_set.end(), "未找到元素 40");

    // 遍历元素 (有序)
    std::vector<int> elements;
    for (int val : ordered_set) {
        elements.push_back(val);
    }
    ASSERT((elements == std::vector<int>{10, 20, 30}), "集合元素应按升序排列");

    // 删除元素
    size_t erased_count = ordered_set.erase(20);
    ASSERT(erased_count == 1, "成功删除元素 20");
    ASSERT(ordered_set.size() == 2, "删除一个元素后的大小");
    ASSERT(ordered_set.count(20) == 0, "元素 20 已被删除");

    erased_count = ordered_set.erase(50);// 删除不存在的元素
    ASSERT(erased_count == 0, "尝试删除不存在的元素 50");
    ASSERT(ordered_set.size() == 2, "删除不存在元素后的大小不变");

    // ---- std::unordered_set ----
    // std::unordered_set 是一个无序集合，基于哈希表实现
    std::unordered_set<std::string> unordered_set;

    unordered_set.insert("apple");
    unordered_set.insert("banana");
    unordered_set.insert("cherry");
    unordered_set.insert("apple");// 重复元素不会被插入

    ASSERT(unordered_set.size() == 3, "无序集合的大小");

    // 查找元素 (平均 O(1))
    ASSERT(unordered_set.count("banana") == 1, "检查元素 'banana' 是否存在");
    ASSERT(unordered_set.count("grape") == 0, "检查元素 'grape' 是否存在");

    // 删除元素
    erased_count = unordered_set.erase("banana");
    ASSERT(erased_count == 1, "成功删除元素 'banana'");
    ASSERT(unordered_set.size() == 2, "删除一个元素后的大小");
    ASSERT(unordered_set.count("banana") == 0, "元素 'banana' 已被删除");

    // 清空集合
    ordered_set.clear();
    unordered_set.clear();
    ASSERT(ordered_set.empty(), "清空后有序集合应为空");
    ASSERT(unordered_set.empty(), "清空后无序集合应为空");

    // THINK: `std::set` 和 `std::unordered_set` 的主要区别是什么？
    //        何时应优先选择 `std::set`？何时应优先选择 `std::unordered_set`？
    //        `std::set` 的查找、插入、删除的时间复杂度是多少？`std::unordered_set` 呢？

    return 0;
}