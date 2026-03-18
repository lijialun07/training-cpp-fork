#include "../exercise.h"
#include <optional>
#include <string>

// READ: std::optional <https://zh.cppreference.com/w/cpp/utility/optional>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 创建一个空的 optional<int>
    std::optional<int> opt_int;
    ASSERT(!opt_int.has_value(), "初始 optional<int> 不应包含值");

    // 设置 optional<int> 的值
    opt_int = 42;
    ASSERT(opt_int.has_value(), "optional<int> 现在应该包含值");
    ASSERT(*opt_int == 42, "optional<int> 的值应为 42");
    ASSERT(opt_int.value() == 42, "使用 value() 获取值");

    // 使用 reset() 清空 optional
    opt_int.reset();
    ASSERT(!opt_int.has_value(), "reset() 后 optional<int> 不应包含值");

    // 使用 value_or 提供默认值
    ASSERT(opt_int.value_or(100) == 100, "当 optional 为空时，value_or 应返回默认值");
    opt_int = 7;
    ASSERT(opt_int.value_or(100) == 7, "当 optional 有值时，value_or 应返回其值");

    // 创建一个包含字符串的 optional
    std::optional<std::string> opt_str = "Hello";
    ASSERT(opt_str.has_value(), "optional<std::string> 应该包含值");
    ASSERT(*opt_str == "Hello", "optional<std::string> 的值应为 \"Hello\"");

    // 使用 emplace 原地构造值
    opt_str.emplace("World");
    ASSERT(*opt_str == "World", "emplace 后 optional<std::string> 的值应为 \"World\"");

    // 访问空 optional 的 value() (应该抛出异常)
    opt_str.reset();
    bool caught = false;
    try {
        opt_str.value();
    } catch (const std::bad_optional_access &e) {
        caught = true;
    }
    ASSERT(caught, "访问空 optional 的 value() 应该抛出 std::bad_optional_access");

    // optional 的比较
    std::optional<int> opt1 = 10;
    std::optional<int> opt2 = 20;
    std::optional<int> opt3 = 10;
    std::optional<int> opt_empty;

    ASSERT(opt1 < opt2, "opt1 应小于 opt2");
    ASSERT(opt1 == opt3, "opt1 应等于 opt3");
    ASSERT(opt2 > opt1, "opt2 应大于 opt1");
    ASSERT(opt_empty < opt1, "空 optional 应小于有值的 optional");
    ASSERT(opt_empty == opt_empty, "两个空 optional 应相等");

    return 0;
}