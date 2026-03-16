#include "../exercise.h"
#include <iostream>
#include <string>
#include <utility>

// READ: std::pair <https://zh.cppreference.com/w/cpp/utility/pair>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 使用 std::make_pair 创建一个包含两个 int 的 pair
    std::pair<int, int> p1 = std::make_pair(10, 20);
    ASSERT(p1.first == 10, "第一个元素应为 10");
    ASSERT(p1.second == 20, "第二个元素应为 20");

    // 使用列表初始化创建包含 double 和 string 的 pair
    std::pair<double, std::string> p2 = {3.14, "pi"};
    ASSERT(p2.first == 3.14, "第一个元素应为 3.14");
    ASSERT(p2.second == "pi", "第二个元素应为 \"pi\"");

    std::pair<char, bool> p3('a', true);
    ASSERT(p3.first == 'a', "初始第一个元素");
    ASSERT(p3.second == true, "初始第二个元素");

    // 修改 pair 的成员
    p3.first = 'b';
    p3.second = false;
    ASSERT(p3.first == 'b', "修改后的第一个元素");
    ASSERT(p3.second == false, "修改后的第二个元素");

    auto get_coordinates = []() -> std::pair<int, int> {
        return {5, -2};
    };
    std::pair<int, int> coords = get_coordinates();
    ASSERT(coords.first == 5, "坐标的 x 值");
    ASSERT(coords.second == -2, "坐标的 y 值");

    std::pair<int, int> p4 = {1, 2};
    std::pair<int, int> p5 = {1, 3};
    std::pair<int, int> p6 = {1, 2};
    ASSERT(p4 < p5, "p4 应小于 p5");
    ASSERT(p4 == p6, "p4 应等于 p6");
    ASSERT(p5 > p6, "p5 应大于 p6");
    // THINK: std::pair 的比较是如何工作的？
    // HINT：首先比较 first 成员，如果相等，则比较 second 成员。

    return 0;
}