#include "../exercise.h"
#include <map>
#include <string>
#include <tuple>
#include <vector>

// READ: 结构化绑定 <https://zh.cppreference.com/w/cpp/language/structured_binding>

struct MyStruct {
    int id;
    std::string name;
    double value;
};

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 绑定到数组
    int arr[] = {1, 2, 3};
    auto [a, b, c] = arr;
    ASSERT(a == 1, "第一个元素");
    ASSERT(b == 2, "第二个元素");
    ASSERT(c == 3, "第三个元素");

    // 绑定到 std::pair
    std::pair<char, float> p = {'x', 3.14f};
    auto &[key, val] = p;// 使用引用绑定
    ASSERT(key == 'x', "pair 的第一个元素");
    ASSERT(val == 3.14f, "pair 的第二个元素");
    key = 'y';// 修改引用会影响原始 pair
    ASSERT(p.first == 'y', "修改后 pair 的第一个元素");

    // 绑定到 std::tuple
    std::tuple<bool, int, std::string> t = {true, 100, "Hello"};
    auto [flag, num, str] = t;
    ASSERT(flag == true, "tuple 的第一个元素");
    ASSERT(num == 100, "tuple 的第二个元素");
    ASSERT(str == "Hello", "tuple 的第三个元素");

    // 绑定到结构体 (C++17)
    MyStruct s = {1, "Test", 9.99};
    auto [s_id, s_name, s_value] = s;
    ASSERT(s_id == 1, "结构体的 id");
    ASSERT(s_name == "Test", "结构体的 name");
    ASSERT(s_value == 9.99, "结构体的 value");

    // 在 for 循环中使用结构化绑定 (C++17)
    std::map<std::string, int> scores = {{"Alice", 90}, {"Bob", 85}};
    int total_score = 0;
    for (const auto &[name, score] : scores) {
        ASSERT(name == "Alice" || name == "Bob", "遍历 map 的 key");
        ASSERT(score == 90 || score == 85, "遍历 map 的 value");
        total_score += score;
    }
    ASSERT(total_score == 175, "总分");

    // THINK: 结构化绑定声明的变量是副本还是引用？如何控制？
    // THINK: 结构化绑定可以用在哪些类型的对象上？

    return 0;
}