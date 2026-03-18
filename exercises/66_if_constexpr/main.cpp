#include "../exercise.h"
#include <iostream>
#include <string>
#include <type_traits>// for std::is_integral, std::is_floating_point

// READ: if constexpr <https://en.cppreference.com/w/cpp/language/if>

template<typename T>
std::string process(T value) {
    if constexpr (std::is_integral_v<T>) {
        // 如果 T 是整数类型
        return "Integral: " + std::to_string(value);
    } else if constexpr (std::is_floating_point_v<T>) {
        // 如果 T 是浮点类型
        return "Floating point: " + std::to_string(value);
    } else if constexpr (std::is_same_v<T, std::string>) {
        // 如果 T 是 std::string 类型
        return "String: " + value;
    } else {
        // 其他类型
        return "Unknown type";
    }
}

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    ASSERT(process(10) == "Integral: 10", "处理 int");
    ASSERT(process(3.14) == "Floating point: 3.140000", "处理 double");
    ASSERT(process(std::string("Hello")) == "String: Hello", "处理 std::string");
    ASSERT(process('a') == "Integral: 97", "处理 char (也是整数类型)");
    ASSERT(process(true) == "Integral: 1", "处理 bool (也是整数类型)");

    struct Unknown {};
    ASSERT(process(Unknown{}) == "Unknown type", "处理未知类型");

    // THINK: `if constexpr` 和普通的 `if` 语句有什么主要区别？
    // THINK: `if constexpr` 在模板元编程中有什么作用？
    // THINK: 为什么 `if constexpr` 的分支必须在编译时就能确定？

    return 0;
}