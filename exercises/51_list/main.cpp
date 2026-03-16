#include "../exercise.h"
#include <list>
#include <string>
#include <vector>

// READ: std::list <https://zh.cppreference.com/w/cpp/container/list>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 创建一个空的 std::list
    std::list<int> my_list;
    ASSERT(my_list.empty(), "列表初始应为空");
    ASSERT(my_list.size() == 0, "列表初始大小应为 0");

    // 在列表前端添加元素
    my_list.push_front(10);
    my_list.push_front(5);
    ASSERT(!my_list.empty(), "添加元素后列表不应为空");
    ASSERT(my_list.size() == 2, "添加两个元素后的大小");
    ASSERT(my_list.front() == 5, "前端添加后的第一个元素");
    ASSERT(my_list.back() == 10, "前端添加后的最后一个元素");

    // 在列表后端添加元素
    my_list.push_back(20);
    my_list.push_back(25);
    ASSERT(my_list.size() == 4, "后端添加两个元素后的大小");
    ASSERT(my_list.front() == 5, "后端添加后的第一个元素");
    ASSERT(my_list.back() == 25, "后端添加后的最后一个元素"); // 应该是 {5, 10, 20, 25}

    // 移除列表前端元素
    my_list.pop_front();
    ASSERT(my_list.size() == 3, "移除前端元素后的大小");
    ASSERT(my_list.front() == 10, "移除前端元素后的第一个元素"); // 应该是 {10, 20, 25}

    // 移除列表后端元素
    my_list.pop_back();
    ASSERT(my_list.size() == 2, "移除后端元素后的大小");
    ASSERT(my_list.back() == 20, "移除后端元素后的最后一个元素"); // 应该是 {10, 20}

    // 在指定位置插入元素
    auto it = my_list.begin(); // 获取指向第一个元素的迭代器
    ++it; // 移动迭代器到第二个位置 (指向 20)
    my_list.insert(it, 15); // 在 20 前插入 15
    ASSERT(my_list.size() == 3, "插入元素后的大小");
    // 检查插入后的元素顺序 {10, 15, 20}
    auto current = my_list.begin();
    ASSERT(*current == 10, "插入后的第一个元素");
    ++current;
    ASSERT(*current == 15, "插入后的第二个元素");
    ++current;
    ASSERT(*current == 20, "插入后的第三个元素");

    // 移除指定位置的元素
    it = my_list.begin(); // 指向 10
    ++it; // 指向 15
    my_list.erase(it); // 移除 15
    ASSERT(my_list.size() == 2, "移除元素后的大小");
    ASSERT(my_list.front() == 10, "移除元素后的第一个元素");
    ASSERT(my_list.back() == 20, "移除元素后的最后一个元素"); // 应该是 {10, 20}

    // 使用迭代器遍历列表并计算总和
    int sum = 0;
    for (int val : my_list) {
        sum += val;
    }
    ASSERT(sum == 30, "列表中所有元素的总和");

    // 使用初始化列表创建列表
    std::list<std::string> words = {"Hello", "World", "!"};
    ASSERT(words.size() == 3, "使用初始化列表创建的列表大小");
    ASSERT(words.front() == "Hello", "初始化列表的第一个元素");
    ASSERT(words.back() == "!", "初始化列表的最后一个元素");

    return 0;
}