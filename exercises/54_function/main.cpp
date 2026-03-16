#include "../exercise.h"
#include <functional>
#include <string>

// READ: std::function <https://zh.cppreference.com/w/cpp/utility/functional/function>
// READ: lambda 表达式 <https://zh.cppreference.com/w/cpp/language/lambda>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    // 1. 简单的 lambda 表达式
    auto adder = [](int a, int b) {
        return a + b;
    };
    ASSERT(adder(5, 3) == 8, "adder(5, 3) should be 8");

    // 2. 使用 std::function 存储 lambda
    std::function<int(int, int)> func_adder = adder;
    ASSERT(func_adder(10, 5) == 15, "func_adder(10, 5) should be 15");

    // 3. 带捕获列表的 lambda (值捕获)
    int x = 10;
    auto multiplier_by_value = [x](int y) {
        return x * y;
    };
    ASSERT(multiplier_by_value(4) == 40, "multiplier_by_value(4) should be 40");
    x = 20;// 修改 x 的值
    // 值捕获，lambda 内部的 x 仍然是 10
    ASSERT(multiplier_by_value(4) == 40, "multiplier_by_value(4) should still be 40 after changing x");

    // 4. 带捕获列表的 lambda (引用捕获)
    int z = 5;
    auto multiplier_by_ref = [&z](int y) {
        return z * y;
    };
    ASSERT(multiplier_by_ref(6) == 30, "multiplier_by_ref(6) should be 30");
    z = 8;// 修改 z 的值
    // 引用捕获，lambda 内部的 z 会反映外部的变化
    ASSERT(multiplier_by_ref(6) == 48, "multiplier_by_ref(6) should be 48 after changing z");

    // 5. 将 std::function 作为参数传递
    auto execute = [](const std::function<std::string(int)> &f, int val) {
        return f(val);
    };
    std::function<std::string(int)> int_to_string = [](int i) {
        return std::to_string(i);
    };
    ASSERT(execute(int_to_string, 123) == "123", "execute(int_to_string, 123) should return \"123\"");

    // 6. 捕获所有变量 (隐式值捕获)
    int a = 1, b = 2;
    auto sum_all_value = [=]() {
        return a + b;
    };
    ASSERT(sum_all_value() == 3, "sum_all_value() should be 3");
    a = 10;
    ASSERT(sum_all_value() == 3, "sum_all_value() should still be 3 after changing a");

    // 7. 捕获所有变量 (隐式引用捕获)
    int c = 3, d = 4;
    auto sum_all_ref = [&]() {
        return c + d;
    };
    ASSERT(sum_all_ref() == 7, "sum_all_ref() should be 7");
    c = 5;
    ASSERT(sum_all_ref() == 9, "sum_all_ref() should be 9 after changing c");

    return 0;
}