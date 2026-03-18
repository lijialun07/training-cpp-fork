#include "../exercise.h"
#include <string>
#include <variant>

// READ: std::variant <https://zh.cppreference.com/w/cpp/utility/variant>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 创建一个可以持有 int 或 std::string 的 variant
    std::variant<int, std::string> v = 10;
    ASSERT(std::holds_alternative<int>(v), "v 应该持有 int");
    ASSERT(std::get<int>(v) == 10, "v 中的 int 值应为 10");

    v = "Hello";
    ASSERT(std::holds_alternative<std::string>(v), "v 现在应该持有 std::string");
    ASSERT(std::get<std::string>(v) == "Hello", "v 中的 string 值应为 \"Hello\"");

    // 使用 std::visit 访问 variant
    std::visit([](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            ASSERT(arg == 10, "访问 int 值");
        } else if constexpr (std::is_same_v<T, std::string>) {
            ASSERT(arg == "Hello", "访问 string 值");
        } else {
            ASSERT(false, "不应到达这里");
        }
    }, v);

    // 获取 variant 的索引
    ASSERT(v.index() == 1, "当前活动成员的索引");

    // 尝试获取错误的类型 (应该抛出异常)
    bool caught = false;
    try {
        std::get<int>(v);
    } catch (const std::bad_variant_access &e) {
        caught = true;
    }
    ASSERT(caught, "尝试获取错误的类型应该抛出 std::bad_variant_access");

    return 0;
}