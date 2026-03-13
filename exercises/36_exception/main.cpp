#include "../exercise.h"
#include <stdexcept> // 引入标准异常类
#include <string>
#include <vector>

// READ: exception <https://en.cppreference.com/w/cpp/error/exception>
// READ: 异常处理 <https://lb3fn675fh.feishu.cn/wiki/E34zwfOw5ijmWyk6JT6cjP5hnRh>
// READ 常见的异常 <https://lb3fn675fh.feishu.cn/wiki/Egr5ww4ngifspGkQzSEczJPAnGu>

// 定义一个可能抛出异常的函数
int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Division by zero"); // 抛出运行时错误
    }
    return a / b;
}

// 定义一个访问 vector 元素的函数，可能抛出越界异常
char get_element(const std::vector<char>& vec, size_t index) {
    if (index >= vec.size()) {
        throw std::out_of_range("Index out of range"); // 抛出越界错误
    }
    return vec[index];
}

// 定义一个自定义异常类
struct MyException : public std::exception {
    const char* what() const noexcept override {
        return "This is my custom exception!";
    }
};

// 声明一个保证不抛出异常的函数
void no_throw_function() noexcept {
    // 这个函数保证不会抛出任何异常
    // THINK: 如果这个函数真的抛出了异常，程序会发生什么？
}

int main(int argc, char **argv) {
    // ---- 练习 1: 基本的 try-catch ----
    std::string error_msg;
    try {
        int result = divide(10, 0); // 尝试进行除零操作
        ASSERT(false, "This line should not be reached.");
    } catch (const std::runtime_error& e) {
        // 捕获 std::runtime_error 类型的异常
        error_msg = e.what();
    }
    ASSERT(error_msg == "Division by zero", "捕获到的错误信息应该是什么？");

    // ---- 练习 2: 捕获 std::out_of_range ----
    std::vector<char> my_vec = {'a', 'b', 'c'};
    char element = '\0';
    std::string out_of_range_msg;
    try {
        element = get_element(my_vec, 5); // 尝试访问越界索引
        ASSERT(false, "This line should not be reached.");
    } catch (const std::out_of_range& e) {
        // 捕获 std::out_of_range 类型的异常
        out_of_range_msg = e.what();
    }
    ASSERT(element == '\0', "访问失败，element 应该保持初始值");
    ASSERT(out_of_range_msg == "Index out of range", "捕获到的越界错误信息应该是什么？");

    // ---- 练习 3: 抛出和捕获自定义异常 ----
    std::string custom_exception_msg;
    try {
        throw MyException(); // 抛出自定义异常
        ASSERT(false, "This line should not be reached.");
    } catch (const MyException& e) {
        // 捕获 MyException 类型的异常
        custom_exception_msg = e.what();
    } catch (const std::exception& e) {
        // 也可以捕获基类 std::exception
        ASSERT(false, "Should have caught MyException specifically.");
    }
    ASSERT(custom_exception_msg == "This is my custom exception!", "捕获到的自定义异常信息应该是什么？");

    // ---- 练习 4: noexcept 说明符 ----
    // noexcept 告诉编译器和调用者这个函数不会抛出异常
    // 如果标记为 noexcept 的函数真的抛出了异常，程序会调用 std::terminate
    bool noexcept_works = true;
    try {
        no_throw_function(); // 调用保证不抛出异常的函数
    } catch (...) {
        // 这个 catch 块不应该被执行
        noexcept_works = false;
    }
    ASSERT(noexcept_works == true, "noexcept 函数是否按预期工作？ (true/false)");

    // THINK：什么时候应该使用异常？什么时候不应该？异常处理的成本是什么？

    return 0;
}