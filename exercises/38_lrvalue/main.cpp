#include "../exercise.h"

#include <iostream>
#include <utility>

// READ：左值右值 <https://lb3fn675fh.feishu.cn/wiki/XdiOw2Wzqi7EFSkq0ZQcQkUAnVd>

// 辅助函数，用于判断是否为左值
template <typename T>
constexpr bool is_lvalue(T &) {
    return true;
}
// 辅助函数，用于判断是否为右值（通过排除左值）
template <typename T>
constexpr bool is_lvalue(T &&) {
    return false;
}

// 使用完美转发的包装函数
template<typename T>
constexpr bool wrapper_perfect_forward(T &&t) {
    // std::forward<T>(t) 会保持 t 的原始值类别
    // 如果 t 是左值引用，转发后仍是左值
    // 如果 t 是右值引用，转发后仍是右值
    return is_lvalue(std::forward<T>(t));
}

// 不使用完美转发的包装函数
template<typename T>
constexpr bool wrapper_no_forward(T &&t) {
    // 参数 t 本身在函数体内总是一个左值
    return is_lvalue(t);
}

int main(int argc, char **argv) {
    // 练习 1: 识别基本类型的左值和右值
    int x = 10;         // x 是一个具名的变量，是左值
    const int cx = 20;  // cx 是一个具名的常量，是左值
    int &rx = x;        // rx 是 x 的引用，是左值
    const int &crx = x; // crx 是 x 的常量引用，是左值

    ASSERT(is_lvalue(x) == true, "变量 x 应该是左值");
    ASSERT(is_lvalue(cx) == true, "常量 cx 应该是左值");
    ASSERT(is_lvalue(rx) == true, "引用 rx 应该是左值");
    ASSERT(is_lvalue(crx) == true, "常量引用 crx 应该是左值");
    ASSERT(is_lvalue(42) == false, "字面量 42 应该是右值");
    ASSERT(is_lvalue(x + 1) == false, "表达式 x + 1 的结果是临时值，应该是右值");
    ASSERT(is_lvalue(std::move(x)) == false, "std::move(x) 将 x 转换为右值引用（将亡值），应该是右值");

    // 练习 2: 理解万能引用和完美转发
    int i = 1;
    const int ci = 2;

    // 测试 wrapper_perfect_forward
    // 传入右值 (字面量 100)
    ASSERT(wrapper_perfect_forward(100) == false, "传递右值给完美转发包装器，转发后应为右值");
    // 传入左值 (变量 i)
    ASSERT(wrapper_perfect_forward(i) == true, "传递左值给完美转发包装器，转发后应为左值");
    // 传入常量左值 (变量 ci)
    ASSERT(wrapper_perfect_forward(ci) == true, "传递常量左值给完美转发包装器，转发后应为左值");
    // 传入将亡值 (std::move(i))
    ASSERT(wrapper_perfect_forward(std::move(i)) == false, "传递将亡值给完美转发包装器，转发后应为右值");

    // 测试 wrapper_no_forward
    int j = 3;
    // 传入右值 (字面量 200)
    ASSERT(wrapper_no_forward(200) == true, "传递右值给非完美转发包装器，参数本身在函数内是左值");
    // 传入左值 (变量 j)
    ASSERT(wrapper_no_forward(j) == true, "传递左值给非完美转发包装器，参数本身在函数内是左值");
    // 传入将亡值 (std::move(j))
    ASSERT(wrapper_no_forward(std::move(j)) == true, "传递将亡值给非完美转发包装器，参数本身在函数内是左值");

    // THINK:
    // 1. 为什么函数参数（即使是右值引用类型）在函数体内本身是左值？
    // 2. std::forward 的主要作用是什么？它如何根据模板参数 T 推断出的类型来决定是转换为左值引用还是右值引用？
    // 3. 在什么场景下必须使用完美转发？

    return 0;
}