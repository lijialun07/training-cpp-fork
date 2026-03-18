#include "../exercise.h"
#include <any>
#include <string>
#include <vector>

// READ: std::any <https://zh.cppreference.com/w/cpp/utility/any>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 创建一个空的 any
    std::any a;
    ASSERT(!a.has_value(), "初始 any 不应包含值");

    // 存储一个 int
    a = 10;
    ASSERT(a.has_value(), "any 现在应该包含值");
    ASSERT(a.type() == typeid(int), "any 中值的类型应为 int");
    ASSERT(std::any_cast<int>(a) == 10, "any 中的 int 值应为 10");

    // 存储一个 std::string
    a = std::string("Hello");
    ASSERT(a.type() == typeid(std::string), "any 中值的类型应为 std::string");
    ASSERT(std::any_cast<std::string>(a) == "Hello", "any 中的 string 值应为 \"Hello\"");

    // 使用 reset() 清空 any
    a.reset();
    ASSERT(!a.has_value(), "reset() 后 any 不应包含值");

    // 存储一个 vector<double>
    a = std::vector<double>{3.14, 2.71};
    ASSERT(a.type() == typeid(std::vector<double>), "any 中值的类型应为 std::vector<double>");
    ASSERT(std::any_cast<std::vector<double>>(a).size() == 2, "vector 的大小应为 2");
    ASSERT(std::any_cast<std::vector<double>>(a)[0] == 3.14, "vector 的第一个元素应为 3.14");

    // 使用 emplace 原地构造
    a.emplace<std::pair<int, char>>(5, 'a');
    ASSERT(a.type() == typeid(std::pair<int, char>), "any 中值的类型应为 std::pair<int, char>");
    ASSERT((std::any_cast<std::pair<int, char>>(a).first == 5), "pair 的第一个元素应为 5");
    ASSERT((std::any_cast<std::pair<int, char>>(a).second == 'a'), "pair 的第二个元素应为 'a'");

    // 尝试获取错误的类型 (应该抛出异常)
    bool caught = false;
    try {
        std::any_cast<float>(a);
    } catch (const std::bad_any_cast &e) {
        caught = true;
    }
    ASSERT(caught, "尝试获取错误的类型应该抛出 std::bad_any_cast");

    return 0;
}