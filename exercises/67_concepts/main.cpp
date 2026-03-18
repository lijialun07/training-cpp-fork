#include "../exercise.h"
#include <concepts>
#include <string>
#include <vector>

// READ: Concepts <https://zh.cppreference.com/w/cpp/language/constraints>

// TODO: 定义一个 Concept `Addable`，要求类型 T 支持 `+` 运算符
template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;// 要求 a + b 的结果类型与 T 相同
};

// TODO: 定义一个 Concept `Integral`，等价于 std::is_integral_v<T>
template<typename T>
concept Integral = std::is_integral_v<T>;

// TODO: 定义一个 Concept `Container`，要求类型 C 具有 begin(), end(), size() 成员函数
template<typename C>
concept Container = requires(C c) {
    { c.begin() } -> std::input_or_output_iterator;  // begin() 返回迭代器
    { c.end() } -> std::input_or_output_iterator;    // end() 返回迭代器
    { c.size() } -> std::convertible_to<std::size_t>;// size() 返回可转换为 size_t 的类型
};

// 使用 Concept 约束函数模板
template<Addable T>
T sum(T a, T b) {
    return a + b;
}

// 使用 Concept 约束类模板
template<Integral T>
struct OnlyInt {
    T value;
};

// 使用多个 Concept 约束
template<Container C>
    requires Integral<typename C::value_type>// 要求容器元素类型是整数
std::size_t count_integers(const C &container) {
    return container.size();
}

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 测试 Addable Concept
    ASSERT(sum(5, 3) == 8, "Addable: int + int");
    ASSERT(sum(std::string("Hello, "), std::string("World!")) == "Hello, World!", "Addable: string + string");
    // struct NotAddable {};
    // sum(NotAddable{}, NotAddable{}); // 这行代码应该无法编译

    // 测试 Integral Concept
    OnlyInt<int> oi = {10};
    ASSERT(oi.value == 10, "Integral: OnlyInt<int>");
    // OnlyInt<double> od = {3.14}; // 这行代码应该无法编译

    // 测试 Container Concept 和组合约束
    std::vector<int> v = {1, 2, 3, 4, 5};
    ASSERT(count_integers(v) == 5, "Container & Integral: std::vector<int>");

    std::vector<double> vd = {1.1, 2.2};
    // count_integers(vd); // 这行代码应该无法编译，因为 double 不是 Integral

    std::string s = "abc";
    // count_integers(s); // 这行代码应该无法编译，因为 string 没有 value_type 或不满足 Integral

    // THINK: Concept 如何提高模板代码的可读性和错误信息？
    // THINK: `requires` 关键字有哪几种用法？
    // THINK: 标准库提供了哪些常用的 Concept？

    return 0;
}