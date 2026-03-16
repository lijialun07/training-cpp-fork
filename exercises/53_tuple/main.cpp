#include "../exercise.h"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

// READ: std::tuple <https://zh.cppreference.com/w/cpp/utility/tuple>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 使用 std::make_tuple 创建一个包含 int, double, std::string 的元组
    auto t1 = std::make_tuple(10, 3.14, "Hello");
    ASSERT(std::get<0>(t1) == 10, "第一个元素应为 10");
    ASSERT(std::get<1>(t1) == 3.14, "第二个元素应为 3.14");
    ASSERT(std::get<2>(t1) == "Hello", "第三个元素应为 \"Hello\"");

    // 使用列表初始化创建包含 char, bool, int 的元组
    std::tuple<char, bool, int> t2 = {'a', true, 100};
    ASSERT(std::get<0>(t2) == 'a', "第一个元素应为 'a'");
    ASSERT(std::get<1>(t2) == true, "第二个元素应为 true");
    ASSERT(std::get<2>(t2) == 100, "第三个元素应为 100");

    std::tuple<std::string, int, double> t3 = {"World", 42, 2.71};
    // 使用 std::get<index> 访问
    ASSERT(std::get<0>(t3) == "World", "使用索引访问第一个元素");
    ASSERT(std::get<1>(t3) == 42, "使用索引访问第二个元素");
    ASSERT(std::get<2>(t3) == 2.71, "使用索引访问第三个元素");

    // 修改元组元素
    std::get<1>(t3) = 99;
    ASSERT(std::get<1>(t3) == 99, "修改后的第二个元素");

    auto [s, i, d] = t3;// 将 t3 解包到变量 s, i, d
    ASSERT(s == "World", "结构化绑定 - 字符串");
    ASSERT(i == 99, "结构化绑定 - 整数");
    ASSERT(d == 2.71, "结构化绑定 - 浮点数");

    std::tuple<int, char> t4 = {1, 'a'};
    std::tuple<int, char> t5 = {1, 'b'};
    std::tuple<int, char> t6 = {2, 'a'};
    std::tuple<int, char> t7 = {1, 'a'};

    ASSERT(t4 < t5, "t4 应小于 t5");
    ASSERT(t5 < t6, "t5 应小于 t6");
    ASSERT(t4 < t6, "t4 应不等于 t6");
    ASSERT(t4 == t7, "t4 应等于 t7");
    // THINK: std::tuple 的比较是如何工作的？
    // HINT：按字典序逐个比较元素。

    int myInt = 0;
    char myChar = 'x';
    std::string myStr = "";
    std::tuple<int &, char &, std::string &> t8 = std::tie(myInt, myChar, myStr);
    std::get<0>(t8) = 50;
    std::get<2>(t8) = "Tied";
    ASSERT(myInt == 50, "通过 tie 修改 myInt");
    ASSERT(myChar == 'x', "通过 tie 访问 myChar");
    ASSERT(myStr == "Tied", "通过 tie 修改 myStr");

    // 结合 std::tie 和结构化绑定 (常用于忽略某些返回值)
    auto get_status = []() -> std::tuple<int, std::string, bool> {
        return {200, "OK", true};
    };
    int statusCode;
    bool success;
    std::tie(statusCode, std::ignore, success) = get_status();// 忽略中间的字符串
    ASSERT(statusCode == 200, "忽略中间值的状态码");
    ASSERT(success == true, "忽略中间值的成功标志");

    return 0;
}
